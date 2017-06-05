#include <string>
#include <iostream>
#include <cctype>

using namespace std;

//prototypes
int GetInput(string *oper, string *num1, string *num2);
int isNumber(string num);
int OrderUp(string *num1, string *num2);
int GetFraction(string *num);
string Add(string num1, string num2, int fraction);
string Subtract(string num1, string num2, int fraction);
string Multiply(string num1, string num2, int fraction1, int fraction2);
string Prettify(string raw_result);


int main(void) {
    // read input
    string oper, num1, num2;
    if (GetInput(&oper, &num1, &num2) != 0) {
        cerr << "input error" << endl;
        return 1;
    }

    // different operation for different operator
    string raw_result;
    if (oper == "+") {
        // adjust numbers to matching order by adding '0's and remove '.', if any
        int fraction = OrderUp(&num1, &num2);
        raw_result = Add(num1, num2, fraction);
    } else if (oper == "-") {
        // same as Addition
        int fraction = OrderUp(&num1, &num2);
        raw_result = Subtract(num1, num2, fraction);
    } else if (oper == "x") {
        // remove '.' only, without adding new '0's
        int fraction1 = GetFraction(&num1);
        int fraction2 = GetFraction(&num2);
        raw_result = Multiply(num1, num2, fraction1, fraction2);
    }

    // for your pleasure...
    string result = Prettify(raw_result);

    // output result
    cout << result << endl;

    return 0;
}


int GetInput(string *oper, string *num1, string *num2) {
    if (!(cin >> *oper >> *num1 >> *num2)) {
        return 1;
    }

    if (*oper != "+" && *oper != "-" && *oper != "x") {
        return 2;
    }

    if (!isNumber(*num1) || !isNumber(*num2)) {
        return 3;
    }

    return 0;
}


// judging whether num is a floating point number
int isNumber(string num) {
    // for multiple dots detection
    bool hasdot = false;
    for (int i = 0, n = num.size(); i < n; ++i) {
        if (!isdigit(num[i]) && num[i] != '.') {
            return false;
        }
        if (num[i] == '.') {
            if (hasdot) {
                return false;
            } else {
                hasdot = true;
            }
        }
    }

    return true;
}

// remove '.', add '0', return the longer length of fractional part
int OrderUp(string *num1, string *num2) {
    int fraction1 = GetFraction(num1);
    int fraction2 = GetFraction(num2);

    // add '0' to the one with shorter fraction part
    if (fraction1 < fraction2) {
        (*num1).append(fraction2 - fraction1, '0');
    } else {
        (*num2).append(fraction1 - fraction2, '0');
    }

    // add '0' to the one with shorter integer part
    if ((*num1).size() < (*num2).size()) {
        (*num1).insert(0, (*num2).size() - (*num1).size(), '0');
    } else {
        (*num2).insert(0, (*num1).size() - (*num2).size(), '0');
    }

    return max(fraction1, fraction2);
}


// get length of fractional part and remove '.' in the given number
// return length of fractional part
int GetFraction(string *num) {
    string::size_type dot_position;
    int fraction;

    // find '.' in number 1
    dot_position = (*num).find('.');
    if (dot_position == string::npos) {
        fraction = 0;
    } else {
        // delete '.'
        (*num).erase(dot_position, 1);
        fraction = (*num).size() - dot_position;
    }

    return fraction;
}


// do addition
string Add(string num1, string num2, int fraction) {
    string raw_result;
    // add digit by digit
    int carry = 0;
    for (int i = num1.size(); i > 0; --i) {
        int this_digit = num1[i - 1] - '0' + num2[i - 1] - '0' + carry;
        if (this_digit >= 10) {
            carry = 1;
            this_digit -= 10;
        } else {
            carry = 0;
        }
        raw_result.insert(0, to_string(this_digit));
    }
    if (carry == 1) {
        raw_result.insert(0, "1");
    }

    // add the mising '.', if any
    if (fraction != 0) {
        int dot_pos = raw_result.size() - fraction;
        raw_result.insert(dot_pos, ".");
    }

    return raw_result;
}


// do substraction
string Subtract(string num1, string num2, int fraction) {
    string raw_result;
    // add digit by digit
    int borrow = 0;
    for (int i = num1.size(); i > 0; --i) {
        int this_digit = num1[i - 1] - num2[i - 1] + borrow;
        if (this_digit < 0) {
            borrow = -1;
            this_digit += 10;
        } else {
            borrow = 0;
        }

        raw_result.insert(0, to_string(this_digit));
    }

    // if it has to be negative...
    if (borrow == -1) {
        raw_result.insert(0, "-");
    }

    // add the mising '.', if any
    if (fraction != 0) {
        int dot_pos = raw_result.size() - fraction;
        raw_result.insert(dot_pos, ".");
    }

    return raw_result;
}


// do multiplication
string Multiply(string num1, string num2, int fraction1, int fraction2) {
    string raw_result;

    int len1 = num1.size();
    int len2 = num2.size();

    for (int i = len2; i > 0; --i) {
        string temp = "";
        int num2_digit = num2[i - 1] - '0', carry = 0;

        for (int j = len1; j > 0; --j) {
            int temp_digit = (num1[j - 1] - '0') * num2_digit + carry;
            if (temp_digit >= 10) {
                carry = temp_digit / 10;
                temp_digit %= 10;
            } else {
                carry = 0;
            }
            temp.insert(0, to_string(temp_digit));
        }

        if (carry > 0) {
            temp.insert(0, to_string(carry));
        }

        temp.append(len2 - i, '0');

        OrderUp(&raw_result, &temp);
        raw_result = Add(raw_result, temp, 0);
    }

    // add the mising '.', if any
    if (fraction1 != 0 || fraction2 != 0) {
        // insert '0' in the front if raw_result too short for dot insertion
        if (fraction1 + fraction2  >= raw_result.size()) {
            raw_result.insert(0, fraction1 + fraction2 - raw_result.size() + 1, '0');
        }

        int dot_pos = raw_result.size() - fraction1 - fraction2;
        raw_result.insert(dot_pos, ".");
    }

    return raw_result;
}


// prettify raw result
string Prettify(string raw_result) {
    // parsing raw_result into two parts
    string integer_part, fraction_part;
    if (raw_result.find('.') == string::npos) {
        integer_part = raw_result;
    } else {
        integer_part = raw_result.substr(0, raw_result.find('.'));
        fraction_part = raw_result.substr(raw_result.find('.') + 1);
    }

    // delete leading '0's in integer part
    while (integer_part.front() == '0' && integer_part.size() > 1) {
        integer_part.erase(0, 1);
    }

    // delete '0's at the back of fraction part
    while (fraction_part.back() == '0' && fraction_part.size() > 1) {
        fraction_part.pop_back();
    }

    if (fraction_part.size() == 0) {
        return integer_part + ".0";
    } else {
        return integer_part + "." + fraction_part;
    }
}
