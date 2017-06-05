#include<iostream>
#include<string>
using namespace std;
int main() {
    string s[2] = {"even", "odd"};
    int n;
    cin >> n;
    cout << "The value " << n << " is an " << s[n % 2] + " number" << endl;
    return 0;
}
