/*题目：
简单计算题 (必答题)

问题描述：
学习使用基本的数学库函数，加入头文件。
输入两个浮点数(double类型) x和y，通过数学库函数pow(x,y)计算结果。
输入：4.0 3.0
输出：64
输入：5 5
输出：3124
输入：1.1 2.2
输出：1.23329*/

#include<iostream>
#include<math.h>
using namespace std;

int main()
{
	double a, b;
	cout << "input 2 double";
	cin >> a >> b;
	cout << pow(a, b);
    return 0;
}