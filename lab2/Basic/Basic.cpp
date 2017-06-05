/*
* File: Basic.cpp
* ---------------
* Name: [TODO: enter name here]
* Section: [TODO: enter section leader here]
* This file is the starter project for the BASIC interpreter from
* Assignment #6.
* [TODO: extend and correct the documentation]
*/
#include <cctype>
#include <iostream>
#include <string>
#include "exp.h"
#include "parser.h"
#include "program.h"
#include "../StanfordCPPLib/error.h"
#include "../StanfordCPPLib/tokenscanner.h"

#include "../StanfordCPPLib/simpio.h"
#include "../StanfordCPPLib/strlib.h"
using namespace std;

/* Function prototypes */
void storeLines_or_run(string &line, Program &program, Statement *stmt, EvalState& state);
bool checkLines(string line);

/* Main program */

int main() {
        //initialize
	EvalState state;
	Program program;
	Statement* stmt=NULL;
	while (true) {
		try {
			string line = getLine();
			if (line == "RUN") {//control command:RUN
				int lineNumber = program.getFirstLineNumber();
				while (lineNumber != -1) {
					program.setParsedStatement(lineNumber, stmt, state);//run statement
					lineNumber = program.getNextLineNumber(lineNumber);
				};
				continue;
			}
			if (line == "LIST") {//control command:LIST
				int lineNumber = program.getFirstLineNumber();
				while (lineNumber != -1) {
					cout << lineNumber << program.getSourceLine(lineNumber)<<endl;
					lineNumber = program.getNextLineNumber(lineNumber);
				};
				continue;
			}
			if (line == "CLEAR") {//control command:CLEAR
				program.clear();
                                state.clear();
				continue;
			}
			if (line == "QUIT")exit(0);//control command:QUIT
			if (line == "HELP") {//control command:HELP
				cout << "NO HELP:(\n";
				continue;
			}
			storeLines_or_run(line, program, stmt, state);//no control command in this line:execute statement
		}
		catch (ErrorException & ex) {//error
			cout << "SYNTAX ERROR" << endl;
		}
	}
	return 0;
}

/*
* Function: storeLines_or_run
* Usage: storeLines_or_run(line, program, stmt,state);
* -----------------------------------------
* To store input lines and run single statement or a list of statements entered by the user. 
*/

void storeLines_or_run(string &line, Program &program, Statement *stmt, EvalState& state) {
	TokenScanner scanner;
	scanner.setInput(line);//initialize Tokenscanner
	scanner.scanNumbers();
	string instant = scanner.nextToken();
	int Nsize = instant.size();
	int instantLineNumber = atoi(instant.c_str());//lineNumber
	string instantLine = line.substr(Nsize, line.size() - Nsize);//lineString
	if (instantLineNumber == 0) {
		program.runOneStatement(line, stmt, state);//no lineNumber,just statement
	} else {
		if (checkLines(line))
			program.addSourceLine(instantLineNumber, instantLine);//add legal line
		if (instantLine == "")
			program.removeSourceLine(instantLineNumber);//delete line
	}
}
/*
* Function: checkLines
* Usage: checkLines(line);
* -----------------------------------------
* To check the input lines are legal or not.
*/


bool checkLines(string line) {
	if (line[0] == ' ')line = line.substr(1, line.size() - 2);//ignore whitespace
	string three = line.substr(0, 3);
	string five = line.substr(0, 5);
	if (three == "REM"||three=="LET"||three=="END"){//check:if the statement is legal
		char four = line[3];
		if (four == ' ')return true;
		return false;
	}
	if (five == "PRINT" || five == "INPUT") {//check:if the statement is legal
		char six = line[5];
		if (six == ' ')return true;
		return false;
	}
}
