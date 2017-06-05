#include <iostream>

using namespace std;

void swap2(int &a, int &b) //Swap two integers
{
	int t = a;
	a = b;
	b = t;
}

int main()
{
	int x, y, z;
	cin >> x >> y >> z;
	if (x > y)
		swap2(x,y);
	if (y > z)
		swap2(y,z);
	if (x > y)
		swap2(x,y);
	cout << x << "," << y << "," << z << endl;
	return 0;
}
