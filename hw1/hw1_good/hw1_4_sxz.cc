#include <iostream>
#include <cmath>
using namespace std;

int main() {
    char c;
    double a, b;
    cin >> c >> a >> b;
    switch(c) {
      case '+': cout << a+b << endl; break;
      case '-': cout << a-b << endl; break;
      case '*': cout << a*b << endl; break;
      case '/': cout << a/b << endl; break;
    }
    return 0;
}
