// ConsoleApplication18.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include <iostream>
using namespace std;

long long factorial(int n, long long a)
{
	if (n < 0) {
		cout << "false age";
		exit(0);
	}
	if (n == 0)return 1;
	if (n == 1)return a;
	if (n > 1)return factorial(n - 1, (n - 1)*a);
}

int main()
{
	int age;
	cout << "input your age:";
	cin >> age;
	cout << factorial(age,age);
	return 0;
}
//���⣺��age�ϴ�ʱ��Խ�磬����׳�Ӧ�ĳɸ߾����㷨
