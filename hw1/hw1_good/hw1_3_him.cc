//
//  main.cpp
//  SilliMe
//
//  Created by Tang Chuzhe on 16/2/26.
//  Copyright © 2016年 Tang Chuzhe. All rights reserved.
//

#include <iostream>
#include <math.h>


using namespace std;


int main(int argc, const char * argv[]) {
    // get user's input
    double num1, num2;
    if (!(cin >> num1 >> num2)) {
        cerr << "Error: invalid user input." << endl;
        return 1;
    }

    // calculate and print result
    double result = pow(num1, num2);
    cout << result << endl;

    return 0;
}
