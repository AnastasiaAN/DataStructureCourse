// ConsoleApplication17.cpp : 定义控制台应用程序的入口点。
//

#include <iostream>
#include<vector>
using namespace std;

vector<int>factors;
int factor;
bool perfect(int number) {
	factors.clear();
	for (int i = 1; i < (number/2+1); i++) {
		if (number%i == 0) {
			factors.push_back(i);
		}
	}
	int sum = 0;
	for (int i = 0; i < factors.size(); i++) {
		sum += factors[i];
	}
	return(sum == number);
}
int main()
{
	int x;
	cout << "input a number:";
	cin >> x;
	if (x <= 6)
		cout << "no perfect number";
	else {
		for (int i = 1; i < x; i++) {
			if (perfect(i)) {
				cout << "perfect number:" << i << ' ' << "factors are:";
				for (int i = 0; i < factors.size(); i++)
					cout << factors[i] << ' ';
				cout << endl;
			}
		}
	}
    return 0;
}

