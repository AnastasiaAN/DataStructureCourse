// ConsoleApplication19.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include <iostream>
#include<string>
#include<vector>
using namespace std;

vector<string>factors;
void change(string expression) {
	

}//��expression��������ֺ�p,a,m,d����˳����vector��
string multiply_and_divide(vector<string>& factors) {
	int a = factors.find('m');//vector��vector���������ǽ�һ��������߸���list
	int b = factors.find('d');
	if () {
		if (a < b) {

		}
	}
}//ͨ�����������ô˺�������vector�����г˳��ȼ����
string plus_and_substract(vector<string>& factors) {

}//����Ӽ�
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

