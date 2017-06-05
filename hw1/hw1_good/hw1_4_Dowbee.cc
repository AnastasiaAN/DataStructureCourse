#include <iostream>
using namespace std;

int main()
{
	cout << "Input one operator and two numbers:\n";
	string operation;
	double x;
	double y;
	cin >> operation >> x >> y;
	if (operation == "+")
		cout << x + y << endl;
	else if (operation == "-")
		cout << x - y << endl;
	else if (operation == "*")
		cout << x * y << endl;
	else if (operation == "/")
		cout << x / y << endl;
	else
		cout << "ERROR!\n";
	return 0;
}
