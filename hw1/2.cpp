/*题目：
PPP p50 习题8 (必答题)

问题描述：
编写一个程序，测试一个整数值是奇数还是偶数。

测试样例：
输入：4
输出：The value 4 is an even number

输入：11
输出：The value 11 is an odd number*/

#include <iostream>
using namespace std;

int main()
{
int a;
cin >> a;
if (a % 2 == 0)
{
    cout << "The value " << a << " is an even number";
}
else {
    cout << "The value " << a << " is an odd number";
}
return 0;
}