/*题目：
PPP p50 习题10 (必答题)

问题描述：
编写一个程序，执行一个包括二元运算的操作(+ - * /)，然后输出结果。例如：
+ 100 3.14
* 4 5
将操作符读入一个字符串称为 operation，用一个 if 语句判断哪个操作是用户希望的。例如 if(operation==”+” )。输入的数字为double类型。

测试样例：
输入：+ 100 3.14
输出：103.14
输入：- 30 20
输出：10
*/

#include<iostream>
using namespace std;

int main()
{
	char operation;
	double a, b;
	cin >> operation>> a >> b;
	if (operation == '+') {
		cout << a + b;
	}
	if (operation == '-') {
		cout << a - b;
	}
	if (operation == '*') {
		cout << a*b;
	}
	if (operation == '/') {
		cout << a / b;
	}
    return 0;
}

