#include<iostream>
using namespace std;

bool is_leap(int yr) {
    return !(yr % 400) || (!(yr % 4) && (yr % 100));
}

int main() {
    int yr;
    cin >> yr;
    if (yr <= 0) {
        cout << "please input positive number" << endl;
    } else {
        cout << yr << " is " << (is_leap(yr) ? "" : "not ") << "a leap year" << endl;
    }
    return 0;
}
