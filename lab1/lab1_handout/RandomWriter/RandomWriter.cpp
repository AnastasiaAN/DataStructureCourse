/*
* File: RandomWriter.cpp
* ----------------------
* [TODO: fill in your name and student ID]
* Name:
* Student ID:
* This file is the starter project for the random writer problem
* on Assignment #2.
* [TODO: extend the documentation]
*/

#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <ctime>
using namespace std;
#define MAX_CHAR_NUM 100

//get filename
void read_file(ifstream& file_input);

//get order number
int read_order();

//build model
void model_read(ifstream& file_input, const int& order, map<string, vector<char> >& model);

//write
void random_write(const int& order, map<string, vector<char> >& model);

void read_file(ifstream& file_input) {
	// TODO
	// your code here
}

int read_order() {
	// TODO
	// your code here
}

void model_read(ifstream& file_input, const int& order, map<string, vector<char> >& model) {
	// TODO
	// your code here
}

void random_write(const int& order, map<string, vector<char> >& model) {
	// TODO
	// your code here
}

int main() {
	// TODO
	// your code here
	return 0;
}
