#include <iostream>
using namespace std;

int main() {
    int a;
    cin >> a;
    if (a % 2) {
        cout << "The value " << a << " is an odd number" << endl;
    }
    else {
        cout << "The value " << a << " is an even number" << endl;
    }
    return 0;
}
