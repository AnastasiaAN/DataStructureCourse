// ConsoleApplication19.cpp : 定义控制台应用程序的入口点。
//

#include <iostream>
#include<string>
#include<vector>
using namespace std;

vector<string>factors;
void change(string expression) {
	

}//把expression处理成数字和p,a,m,d，按顺序存进vector里
string multiply_and_divide(vector<string>& factors) {
	int a = factors.find('m');//vector无vector方法，考虑进一步处理或者改用list
	int b = factors.find('d');
	if () {
		if (a < b) {

		}
	}
}//通过自身反复调用此函数，将vector中所有乘除先计算掉
string plus_and_substract(vector<string>& factors) {

}//计算加减
void calculate()
{
	try {
		string expression;
		cin>>expression;
		change(expression);
		multiply_and_divide(factors);
		plus_and_substract(factors);
	}
	catch (runtime_error) {
		cout << "error" << endl;
	}
}

int main()
{
	calculate();
}

