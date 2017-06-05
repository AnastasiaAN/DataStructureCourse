#include <iostream>
#include <cmath>
using namespace std;

int main() {
    int year;
    cin >> year;
    if (year < 0) {
        cout << "please input positive number" <<endl;
    }
    else if ((year % 4 == 0 && year % 100)
          || (year % 400 == 0)
          || (year % 3200 == 0 && year % 172800 == 0)){
        cout << year << " is a leap year" << endl;
    }
    else {
        cout << year << " is not a leap year" << endl;
    }
    return 0;
}
