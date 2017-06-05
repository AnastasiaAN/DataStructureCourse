/*题目：
闰年判断 (必答题)

问题描述：
5. 输入一个年份，确定该年份是否为闰年（Leap Year，闰年的定义）。保证输入的年份为正整数。

测试样例：
输入：2016
输出：2016 is a leap year

输入：-100
输出：please input positive number

输入：100
输出：100 is not a leap year

输入：400
输出：400 is a leap year

*/

#include<iostream>
using namespace std;

int main()
{
	int a;
	cin >> a;
	if (a < 0) {
		cout << "please input positive number";
	}
	else {
		if (a % 100 == 0) {
			if (a % 400 == 0) {
				cout << a << " is a leap year";
			}
			else {
				cout << a << " is not a leap year";
			}
		}
		else {
			 if (a%4==0){
			   cout << a << " is a leap year";
			}
	        else {
		        cout << a << " is not a leap year";
			    }
		     }
		 }
    return 0;
}
