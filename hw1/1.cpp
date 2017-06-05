/*题目：
PPP p49 习题6 (必答题)

问题描述：
编写一个程序，提示用户输入三个整数值，然后按照数值次序输出这些值并以逗号隔开。
样例测试：
输入：10 4 6
输出：4,6,10

输入：4 5 4
输出：4,4,5*/

#include<iostream>
using namespace std;
int main()
{
	int a, b, c, d;
	cout <<"please input 3 integer:";
	cin >> a>> b>> c;
	if (a > b){
		d = a;
		a = b;
		b = d;
	}
	if (b > c){
		d = b;
		b = c;
		c = d;
		}
	cout << a<<","<<b<<","<<c;
    return 0;
}