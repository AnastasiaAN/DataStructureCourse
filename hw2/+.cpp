// ConsoleApplication11.cpp : 定义控制台应用程序的入口点。
//

#include <iostream>
#include<string>
#include<algorithm>
#include <vector>
using namespace std;

class Input_error {};

void calculator(string a, string b) {//calculate and output the answer
	int a_point, b_point;
    if (a.find('.', 0) <a.size()) 
			a_point = a.find(".", 0);
	else 
			a_point = a.size();
	if (b.find('.', 0) <b.size()) 
			b_point = b.find('.', 0);
	else 
			b_point = b.size();//find where the '.' of a and b are
	vector<int>singles;
	int plus = 0;
	int single = 0;
	int number_before, number_after;
	if (a_point > b_point)
			number_before = b_point;
	else number_before = a_point;//how many figures a and b both have before '.'
	if (a.size() - a_point > b.size() - b_point) {
		if (b.size() != b_point)
			number_after = b.size() - b_point - 1;
		else number_after = 0;
	}
	else {
		if(a.size()!=a_point)
			number_after = a.size() - a_point - 1;
		else number_after = 0;
	}//how many figures a and b both have after '.'
	for (int i = number_after; i >= -number_before; i--) {
		if (i != 0) {
			plus += (a[a_point + i] - '0') + (b[b_point + i] - '0');
			single = plus % 10;
			plus = plus / 10;
			singles.push_back(single);
		}
	}//calculate a plus b within mutual figures
	single = 0;
	if (a_point > b_point) {
		for (int i = a_point - b_point - 1; i >= 0; i--) {
			single = plus + (a[i] - '0');
			plus = single / 10;
			single %= 10;
			singles.push_back(single);
		}
	}
	else {
		for (int i = b_point - a_point - 1; i >= 0; i--) {
			single = plus + (b[i] - '0');
			plus = single / 10;
			single %= 10;
			singles.push_back(single);
		}
	}//save figures only a or b have before '.'(plus considered)
	int max_point = max(a_point, b_point);
	if (plus != 0) {
		cout << plus;
		max_point++;
	}//if there's a new figure before all
	vector<int>befores;
	int before = 0;
	for (int i = singles.size() - 1; i >= 0; i--) {
		before = singles[i];
		befores.push_back(before);
	}//save numbers in singles into befores
	if (a.size() - a_point > b.size() - b_point) {
		for (int i = b.size() - b_point; i <a.size() - a_point; i++) {
			if (i != 0) {
				before = a[a_point + i]-'0';
				befores.push_back(before);
			}
		}
	}
	if (a.size() - a_point < b.size() - b_point) {
		for (int i = a.size() - a_point; i < b.size() - b_point; i++) {
			if (i !=0) {
				before = b[b_point + i]-'0';
				befores.push_back(before);
			}
		}
	}//save figures only a or b have after '.'
	int j = 0;
	for (int i = befores.size(); i >max_point; i--) {
		if (befores[i-1] != 0) {
		  j = 7;
		}
	}//if answer ends like '.0000000'
	if (j == 7) {
		for (int i = 0; i < befores.size(); i++) {
			cout << befores[i];
			if (i == befores.size() - max(a.size() - a_point, b.size() - b_point))
				cout << '.';
		}
	}
	if (j == 0) {
		for (int i = 0; i < max(a_point,b_point); i++) {
			cout << befores[i];
		}
		cout << ".0";
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
	string a, b,operation;
	bool a_bool, b_bool;
	cout << "input:";
	cin >> operation >> a >> b;
	for (unsigned int i = 0; i < a.length(); i++) {
		a_bool = ((('0' <= a[i]) && (a[i]<= '9'))||(a[i] == '.')) && judgement(a);
	}
	for (unsigned int i = 0; i < b.length(); i++) {
		b_bool = ((('0' <= b[i]) && (b[i]<= '9'))|| (b[i]== '.')) && judgement(b);
	}//test the input legal or not
	try {
		if (!(a_bool&& b_bool && (operation == "+")))
			throw Input_error{};
		calculator(a, b);
	}
       catch (Input_error) {
	    	cerr << "input error";
	  }
	return 0;
}

