// ConsoleApplication13.cpp : 定义控制台应用程序的入口点。
//

#include <iostream>
#include<string>
#include<algorithm>
#include <vector>
using namespace std;

class Input_error {};

void calculator(string a, string b) {//calculate and output the answer
	if (a=="0" || b == "0") {
		cout << "0.0";
	}
	else {
		int a_point, b_point;
		int multiply = 0;
		int a_size = a.size();
		int b_size = b.size();
		if (a.find('.', 0) < a_size)
			a_point = a.find(".", 0);
		else
			a_point = a_size;
		if (b.find('.', 0) < b_size)
			b_point = b.find('.', 0);
		else
			b_point = b_size;//find where the '.' of a and b are
		vector<int>as;
		vector<int>bs;
		for (int i = 0; i < a_size; i++) {
			if (i != a_point)
				as.push_back(a[i]);
		}
		for (int i = 0; i < b_size; i++) {
			if (i != b_point)
				bs.push_back(b[i]);
		}
		a_size = as.size();
		b_size = bs.size();
		vector<int>singles;
		int single = 0;
		for (int i = 0; i <= a_size + b_size; i++) {
			single = 0;
			singles.push_back(single);
		}
		for (int i = a_size - 1; i >= 0; i--) {
			for (int j = b_size - 1; j >= 0; j--) {
				multiply = (as[i] - '0')*(bs[j] - '0');
				single = multiply % 10;
				singles[i + j + 1] += single;
				single = multiply / 10;
				singles[i + j] += single;
			}
		}
		int over = -1;
		for (int i = 0; i < a_point + b_point; i++)
			if (singles[i]>9) {
				over = i;
			}
		for (int i = over; i > 0; i--) {
			multiply = singles[i] / 10;
			singles[i] %= 10;
			singles[i - 1] += multiply;
		}
		int j = a_point + b_point - 1;
		int k = a_point + b_point;
		for (int i = 0; i < (a_point + b_point); i++) {
			if (singles[i] != 0) {
				j = i;
				break;
			}
		}//if answer starts like '0000123'
		for (int i = singles.size() - 1; i >= (a_point + b_point); i--) {
			if (singles[i] != 0) {
				k = i;
				break;
			}
		}//if answer ends like '1.2000'
		for (int i = j; i <= k; i++) {
			cout << singles[i];
			if (i == a_point + b_point - 1)
				cout << '.';
		}
		if (k == a_point + b_point)
			cout << '0';
	}
}
bool judgement(string a) {
	int j = 0;
	for (int i = 0; i < a.size(); i++) {
		if (a[i] == '.')
			j += 1;
		if (j > 1)
			return 0;
	}
	return 1;
}//how many '.' in a and b

int main()
{
	string a, b, operation;
	bool a_bool, b_bool;
	cout << "input:";
	cin >> operation >> a >> b;
	for (unsigned int i = 0; i < a.length(); i++) {
		a_bool = ((('0' <= a[i]) && (a[i] <= '9')) || (a[i] == '.')) && judgement(a);
	}
	for (unsigned int i = 0; i < b.length(); i++) {
		b_bool = ((('0' <= b[i]) && (b[i] <= '9')) || (b[i] == '.')) && judgement(b);
	}//test the input legal or not
	try {
		if (!(a_bool&& b_bool && (operation == "x")))
			throw Input_error{};
		calculator(a, b);
	}
	catch (Input_error) {
		cerr << "input error";
	}
	return 0;
}