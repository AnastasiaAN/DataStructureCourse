/***************************************************
Homework 3: Calculor
Author:
Student ID:
Date:
***************************************************/
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
	//if (full)
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
	default: {}
	}
}


Token_stream ts;
double expression();

double primary()
{
	Token t = ts.get();
	switch (t.kind)
	{
	case '8':
		return t.value;
	default: {}
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
}

void calculate()
{
	while (cin)
	{

	}
}

int main()
{
	calculate();
	return 0;

}