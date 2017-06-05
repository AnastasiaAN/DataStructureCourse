#include<iostream>
#include<string>
using namespace std;
int main() {
	char o;
	string a, b;
	int time = 0;
	cin >> o >> a >> b;
	if (o != 'x') {
		cout << "input error";
		return 0;
	}
	int comma_a = a.size(), comma_b = b.size();
	for (size_t i = 0; i < a.size(); i++) {
		if (a[i] >= '0' && a[i] <= '9') continue;
		if (a[i] == '.'&&time == 0) {
			comma_a = i;
			time += 1;
		}
		else {
			cout << "input error";
			return 0;
		}
	}
	time = 0;
	for (size_t i = 0; i < b.size(); i++) {
		if (b[i] >= '0' && b[i] <= '9') continue;
		if (b[i] == '.'&&time == 0) {
			comma_b = i;
			time += 1;
		}
		else {
			cout << "input error";
			return 0;
		}
	}
	if (comma_a == a.size()) a = a + '.';
	if (comma_b == b.size()) b = b + '.';
	string new_a, new_b;
	new_a = a.substr(0, comma_a) + a.substr(comma_a + 1);
	new_b = b.substr(0, comma_b) + b.substr(comma_b + 1);
	int sum=0, carrying=0;
	string output[10000];
	string *pointer = output;
	char temp1[2];
	for (int i = new_a.size()-1; i >= 0; i--) {
		for (int j = new_b.size()-1; j >= 0; j--) {
			sum = (new_a[i] - '0')*(new_b[j] - '0') + carrying;
			sprintf(temp1, "%d", sum % 10);
			string temp2(new_a.size()+new_b.size()-i-j, '0');
			*pointer = temp1+temp2;
			pointer += 1;
			carrying = sum / 10;
		}
	}
	string result,out;
	int summ;
	char temp4[2];
	for (int i = 0; i < sizeof(output) / sizeof(output[0]); i++) {
		if (output[i] == "") break;
		if (result.size() <= output[i].size()) {
			string temp3(output[i].size() - result.size(), '0');
				result = temp3 + result;
		}
		else {
			string temp3(result.size() - output[i].size(), '0');
			output[i] = temp3 + output[i];
		}
		out = "";
		for (int k = result.size() - 1; k >=0; k--) {
			summ = result[k] + output[i][k] + carrying - 96;
			sprintf(temp4, "%d", summ % 10);
			out = temp4 + out;
			carrying = summ / 10;
			}
		if (carrying != 0) out = '1' + out;
		result = out;
		}
	result = result.substr(0, comma_a + comma_b - 1) + '.' + result.substr(comma_a + comma_b - 1);
	while (result[0] == '0') result = result.substr(1);
	while (result[result.size() - 1] == '0') result = result.substr(0, result.size() - 1);
	if (result[result.size() - 1] == '.') result = result + '0';
	if (result[0] == '.') result = '0' + result;
	cout << result;
}
