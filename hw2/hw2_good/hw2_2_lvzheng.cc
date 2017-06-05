#include <array>
#include <deque>
#include <exception>
#include <functional>
#include <iostream>
#include <stdexcept>
#include <string>

#include <cstdint>
#include <cstdlib>

using digit_t = std::int16_t;

constexpr digit_t NUM_SCALE = 10;

using mul_table_t = std::array<std::array<digit_t, NUM_SCALE>, NUM_SCALE>;

mul_table_t get_mul_table()
{
	mul_table_t rv;
	for (int i = 0; i < NUM_SCALE; ++i)
		for (int j = 0; j < NUM_SCALE; ++j)
			rv[i][j] = i * j;
	return rv;
}

inline digit_t multiply(digit_t a, digit_t b)
{
	static mul_table_t table = get_mul_table();
	return table[a][b];
}


template<typename DIt, typename SIt, typename F>
void add_it(DIt dfirst, SIt sfirst, SIt slast, F f)
{
	while (sfirst != slast) {
		f(*dfirst++, *sfirst++);
	}
}

template<typename Cont, typename F>
void remove_trailing_if(Cont& cont, F f)
{
	while (cont.size()) {
		if (f(cont.back()))
			cont.pop_back();
		else
			break;
	}
}

digit_t char2digit(char ch)
{
	if (ch >= '0' && ch <= '9')
		return ch - '0';
	// TODO: NUM_SCALE may be greater than 10
	return INT8_MAX;
}

char digit2char(digit_t digit)
{
	if (digit <= 9)
		return '0' + digit;
	// TODO: NUM_SCALE may be greater than 10
	return '\0';
}

// 543210.012345
// int <-.-> frac
struct number {
	using container = std::deque<digit_t>;
	using size_type = container::size_type;
	using ssize_type = long;
	container integral, fractional;

	struct bad_input : public std::exception {
	};

	number() = default;

	number(container i, container f)
		: integral(i), fractional(f)
	{ }

	number(const number &) = default;
	number(number &&) = default;
	number& operator = (const number& rhs) = default;
	number& operator = (number&& rhs) = default;
	~number() = default;

	template<typename InputIt>
	void from_string(InputIt first, InputIt last)
	{
		enum { INTEGRAL, FRACTIONAL } status = INTEGRAL;
		while (first != last) {
			digit_t digit = char2digit(*first);
			if (digit != INT8_MAX) {
				if (status == INTEGRAL)
					integral.push_front(digit);
				else
					fractional.push_back(digit);
			} else if ('.' == *first) {
				if (status == FRACTIONAL)
					throw bad_input();
				status = FRACTIONAL;
			} else {
				throw bad_input();
			}
			++first;
		}
		bcd_shrink();
	}

	void clear()
	{
		integral.clear();
		fractional.clear();
	}

	void bcd_shrink()
	{
		auto is_zero = [](digit_t a){return 0 == a;};
		remove_trailing_if(integral, is_zero);
		remove_trailing_if(fractional, is_zero);
	}

	void bcd_carry()
	{
		int carry = 0;
		auto forward_carry = [](int& carry, digit_t& curr) {
			curr += carry;
			carry = 0;
			if (curr < 0) {
				curr += NUM_SCALE;
				carry = -1;
			}
			carry += curr / NUM_SCALE;
			curr %= NUM_SCALE;
		};

		for (auto it = fractional.rbegin(); it != fractional.rend(); ++it)
			forward_carry(carry, *it);

		for (auto it = integral.begin(); it != integral.end(); ++it)
			forward_carry(carry, *it);

		if (carry < 0)
			throw std::underflow_error("integer underflow");

		if (carry)
			integral.push_back(carry);
	}

	void bcd_refresh()
	{
		bcd_carry();
		bcd_shrink();
	}

	void expand_to(size_type isize, size_type fsize)
	{
		if (isize > integral.size())
			integral.resize(isize);
		if (fsize > fractional.size())
			fractional.resize(fsize);
	}

	void expand_as(const number& rhs)
	{
		expand_to(rhs.integral.size(), rhs.fractional.size());
	}

	template<typename F>
	void add_from(const number& rhs, F f)
	{
		expand_as(rhs);
		add_it(integral.begin(), rhs.integral.begin(), rhs.integral.end(), f);
		add_it(fractional.begin(), rhs.fractional.begin(), rhs.fractional.end(), f);
		bcd_refresh();
	}

	// 3  2  1  0  . -1 -2 -3
	digit_t get_digit(ssize_type offset) const
	{
		if (offset < 0)
			return fractional[-1 - offset];
		else
			return integral[offset];
	}

	void add_to_digit(digit_t digit, ssize_type offset)
	{
		if (offset < 0)
			fractional[-1 - offset] += digit;
		else
			integral[offset] += digit;
	}

	number& operator += (const number& rhs)
	{
		auto add_lambda = [](digit_t& lhs, const digit_t& rhs) {
			lhs += rhs;
		};
		add_from(rhs, add_lambda);
		return *this;
	}

	number& operator -= (const number& rhs)
	{
		auto sub_lambda = [](digit_t& lhs, const digit_t& rhs) {
			lhs -= rhs;
		};
		add_from(rhs, sub_lambda);
		return *this;
	}

	number& operator *= (const number& rhs)
	{
		return *this = *this * rhs;
	}

	number operator + (const number& rhs) const
	{
		number rv(*this);
		return rv += rhs;
	}

	number operator - (const number& rhs) const
	{
		number rv(*this);
		return rv -= rhs;
	}

	number operator * (const number& rhs) const
	{
		ssize_type n0m = fractional.size(), n0M = integral.size();
		ssize_type n1m = rhs.fractional.size(), n1M = rhs.integral.size();

		number rv;
		rv.expand_to(n0M + n1M, n0m + n1m);

		for (ssize_type i = -n0m; i < n0M; ++i) {
			digit_t digit = get_digit(i);
			if (digit == 0)
				continue;
			for (ssize_type j = -n1m; j < n1M; ++j) {
				rv.add_to_digit(multiply(digit, rhs.get_digit(j)), i + j);
			}
			rv.bcd_carry();
		}
		rv.bcd_shrink();

		return rv;
	}

	std::string to_string() const
	{
		std::string rv;
		rv.reserve(integral.size() + fractional.size() + 4); // reserve a bit more than needed

		if (integral.empty()) {
			rv.push_back('0');
		} else {
			for (auto it = integral.rbegin(); it != integral.rend(); ++it)
				rv.push_back(digit2char(*it));
		}

		rv.push_back('.');

		if (fractional.empty()) {
			rv.push_back('0');
		} else {
			for (auto& digit : fractional)
				rv.push_back(digit2char(digit));
		}
		return rv;
	}

};

void input_error()
{
	std::cerr << "input error" << std::endl;
	std::exit(1);
}

int main()
{
	char op; // operator
	std::string s1, s2;

	std::cin >> op >> s1 >> s2;
	if (!std::cin)
		input_error();

	std::function<number (const number&, const number&)> func;

	switch (op) {
	case '+':
		func = [](const number& lhs, const number& rhs) {
			return lhs + rhs;
		};
		break;
	case '-':
		func = [](const number& lhs, const number& rhs) {
			return lhs - rhs;
		};
		break;
	case 'x':
		func = [](const number& lhs, const number& rhs) {
			return lhs * rhs;
		};
		break;
	default:
		input_error();
	}

	number n1, n2;
	try {
		n1.from_string(s1.begin(), s1.end());
		n2.from_string(s2.begin(), s2.end());
	} catch (number::bad_input& e) {
		input_error();
	}

	std::cout << func(n1, n2).to_string() << std::endl;

	return 0;
}
