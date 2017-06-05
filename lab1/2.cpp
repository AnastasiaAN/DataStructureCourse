// ConsoleApplication5.cpp : 定义控制台应用程序的入口点。
//

#include<iostream>
using namespace std;

#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <ctime>
using namespace std;
#define MAX_CHAR_NUM 100

//get filename
void read_file(string&file_string,string&file_line);

//get order number
void read_order(int &order, int&go);

//build model
void model_read(string&file_string, const int& order, map<string, vector<char> >& model);

//write
void random_write(string&file_string,const int& order, map<string, vector<char> >& model);

void read_file(string&file_string,string&file_line) {
	cout << "Please enter filename containing source text:(enter':q'to quit)";
	string file_name;
	cin >> file_name;
	if (file_name == ":q") exit(0);
	else {
		ifstream file_input(file_name.c_str());
		if (file_input.is_open()) {
			while (getline(file_input, file_line)) {
				file_line += '\n';//get content of the file line by line and add line break 
				file_string += file_line;//save content into a string
			}
		}
	}
}

void read_order(int &order,int&go) {
	cout << "What order to analysis?(a number from 1 to 10)";
	cin >> order;
	if (order < 0 || order>10) {
		go = 0;
	}
	cout << "Analyzing...please wait." << endl;
}

void model_read(string&file_string, const int& order, map<string, vector<char> >& model) {
	string word;
	char ch;
	for (int i = 0; i < file_string.size() - order; i++) {
		word = file_string.substr(i, order);
		char ch = file_string[i + order];//save the char after this string
		model[word].push_back(ch);
	}
}

void random_write(string&file_string,const int& order, map<string, vector<char> >& model) {
	srand((unsigned)time(0));
	int start = rand() % (file_string.size() - order);//choose the start char randomly
	string output_string,start_string,last_string;
	start_string= file_string.substr(start, order);//start string of the writing
	output_string = start_string;
	last_string = file_string.substr(file_string.size() - order, order);//record the last string of this file
	int last_size = model[last_string].size();//to know whether the end string can be used to continue writing
	for (int i = 0; i < MAX_CHAR_NUM; i++) {
		if ((start_string != last_string)||((start_string==last_string)&(last_size!=0))) {//if the writing can go on normally
			int choose = rand() % (model[start_string].size());
			char after = model[start_string][choose];
			output_string += after;
			start_string = start_string.substr(1, order - 1) + after;
		}
		else break;//stop writing
	}
	cout << output_string << endl<<endl;//output the writing
}

int main() {
	while (true) {
		string file_string, file_line;
		int order;
		int go = 1;//number to stop building moder when order>10 or order<0
		map<string, vector<char> >model;
		read_file(file_string,file_line);
		read_order(order,go);
		if (go = 1) {//if order matches the requirements
			model_read(file_string, order, model);
			random_write(file_string,order, model);
		}
	}
}

