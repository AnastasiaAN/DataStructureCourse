// ConsoleApplication15.cpp : 定义控制台应用程序的入口点。
//

#include <iostream>
#include<string>
#include<vector>
#include<cmath>
using namespace std;

const char number = '8';
const char quit = 'q';
const char print = ';';
const string prompt = "> ";
const string result = "= ";

void error();
void calculate();
class Token {
public:
	char kind;
	double value;
	Token(char ch)
		:kind(ch), value(0) { }
	Token(char ch, double val)
		:kind(ch), value(val) { }
};
class Token_stream {
public:
	Token_stream();
	Token get();
	void putback(Token t);
	void ignore(char c);
private:
	bool full;
	Token buffer;
};

Token_stream::Token_stream()
	:full(false), buffer(0)
{

}

void Token_stream::putback(Token t)
{
	if (full)
		error();
	buffer = t;
	full = true;
}
Token Token_stream::get()
{
	if (full)
	{
		full = false;
		return buffer;
	}

	char ch;
	cin >> ch;

	switch (ch)
	{
	case quit:
	case print:
	case '(':
	case ')':
	case '+':
	case '-':
	case '*':
	case '/':
	case '%':
	case '!':
		return Token(ch);
	case '.':
	case '0': case '1': case '2': case '3': case '4':
	case '5': case '6': case '7': case '8': case '9':
	{
		cin.putback(ch);
		double val;
		cin >> val;
		return Token(number, val);
	}
	default: 
		error();
	}
}


Token_stream ts;
double expression();

int factorial(int n,int a)
{
	if (n < 0)error();
	if (n == 0)return 1;
	if (n == 1)return a;
	if (n > 0)return factorial(n - 1, n*a);
}//calcalate factorial by tail recursion

double primary()
{
	Token t = ts.get();
	switch (t.kind)
	{
	case number:
	{
		Token t_more = ts.get();
		if (t_more.kind == '!') {
			int factorial_number = int(t.value);
			if(factorial_number==t.value)//whether the number is integer or not
			return factorial(t.value, t.value);
			else error();
		}
		else {
			ts.putback(t_more);
			return t.value;
		}
	}
	case'-':
		return-primary();
	case'+':
		return primary();
	case'(':
	{
		double d = expression();
		t = ts.get();
		if (t.kind != ')') {
			error();
		}
		else {
			Token t_more = ts.get();
			if (t_more.kind == '!') {
				int factorial_number = int(d);
				if (factorial_number == d)
					return factorial(d, d);
				else error();
			}
			else {
				ts.putback(t_more);
				return d;
			}
			break;
		}
	}
	default: error();
	}
}

double term()
{
	double left = primary();
	Token t = ts.get();
	while (true)
	{
		switch (t.kind)
		{
		case'*':
			left *= primary();
			t = ts.get();
			break;
		case'/': {
			double divisor = primary();
			if (divisor == 0)error();
			left /= divisor;
			t = ts.get();
			break;
		}
		case'%':
			{
				int i1 = int(left);
				if (i1 != left)error();//if the dividend is integer or not
				double divisor = primary();
				int i2 = int(divisor);
				if (i2 != divisor || i2 == 0) error();//if the divisor is integer or not & if the divisor is 0 or not 
				left = i1%i2;
				t = ts.get();
				break;
			}
		default:
			ts.putback(t);
			return left;
		}
	}
}

double expression()
{
	double left = term();
	Token t = ts.get();
	while (true) {
		switch (t.kind) {
		case'+':
			left += term();
			t = ts.get();
			break;
		case'-':
			left -= term();
			t = ts.get();
			break;
		default:
			ts.putback(t);
			return left;
		}
	}
}


void Token_stream::ignore(char c) {
	if (full&&c == buffer.kind) {
		full = false;
		return;
	}
	full = false;
	char ch = 0;
	while (cin >> ch)
	 if (ch == c) return;
}//when calculation goes wrong,delete current equation(until';')
void clean_up_mess()
{
	ts.ignore(print);
}
void error() {
	throw runtime_error("error");
}

 
void calculate()
{
	while (cin)
	{
		try {
			cout << prompt;
			Token t = ts.get();
			if (t.kind == print)
				t = ts.get();//turn to next equation
			if (t.kind == quit)
				exit(0);
			ts.putback(t);
			cout << result << expression() << endl;
		}
		catch (runtime_error) {
			cout << "error" << endl;
			clean_up_mess();
		}
	}
}

int main()
{
	calculate();
	return 0;
}

