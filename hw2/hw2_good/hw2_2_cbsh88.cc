#include<iostream>
#include<string>
using namespace std;
int main() {
	char o;
	string a, b;
	int time = 0;
	cin >> o >> a >> b;
	if (o != '-') {
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
	int move_num = comma_a - comma_b;
	if (move_num >= 0) {
		new_a = '0' + a;
		string temp(move_num + 1, '0');
		new_b = temp + b;
		comma_a += 1;
	}
	else {
		new_b = '0' + b;
		string temp(-move_num + 1, '0');
		new_a = temp + a;
		comma_a += (-move_num + 1);
	}
	if (new_a.size() >= new_b.size()) {
		new_b.resize(new_a.size(), '0');
	}
	else {
		new_a.resize(new_b.size(), '0');
	}
	int sum = 0, carrying = 0;
	string output;
	char temp1[2];
	for (size_t i = new_a.size() - 1; i >0; i--) {
		if (i == comma_a) {
			output = '.' + output;
			continue;
		}
		else {
			sum = new_a[i] -new_b[i] + carrying ;
			sprintf(temp1, "%d", (sum>0?sum % 10:(sum+10)%10));
			output = temp1 + output;
			carrying = sum >=0?0:-1;
		}
	}
	while (output[0] == '0') output = output.substr(1, output.size() - 1);
	while (output[output.size() - 1] == '0') output = output.substr(0, output.size() - 1);
	if (output[0] == '.') output = '0' + output;
	if (output[output.size() - 1] == '.') output = output + '0';
	cout << output;
}
