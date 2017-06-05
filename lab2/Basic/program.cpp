/*
* File: program.cpp
* -----------------
* This file is a stub implementation of the program.h interface
* in which none of the methods do anything beyond returning a
* value of the correct type.  Your job is to fill in the bodies
* of each of these methods with an implementation that satisfies
* the performance guarantees specified in the assignment.
*/

#include<map>
#include <string>
#include "program.h"
#include "statement.h"
#include "parser.h"
using namespace std;

Program::Program() {
   /* Empty */
}

Program::~Program() {
   /* Empty */
}

void Program::clear() {
	store.clear();
	parsed.clear();
}

void Program::addSourceLine(int lineNumber, string line) {
	store[lineNumber] = line;
}

void Program::removeSourceLine(int lineNumber) {
	string temp = store[lineNumber];
	if (temp == "") {
		store.erase(lineNumber);
	}
}

string Program::getSourceLine(int lineNumber) {
	storeIter = store.find(lineNumber);
	if (storeIter == store.end()) return "";
	return store[lineNumber];
}

void Program::setParsedStatement(int &lineNumber, Statement *stmt, EvalState&state) {
	storeIter == store.find(lineNumber);
	if (storeIter == store.end()) {
		cout << "SYNTAX ERROR" << endl;
		return;
	}
	TokenScanner scanner;
	scanner.setInput(store[lineNumber]);
	scanner.nextToken();
	string choose = scanner.nextToken();
	if (choose == "REM") {
		stmt = new REM(scanner);
		stmt->execute(lineNumber, state);
		parsed[lineNumber] = stmt;
		return;
	}
	if (choose == "LET") {
		stmt = new LET(scanner);
		stmt->execute(lineNumber, state);
		parsed[lineNumber] = stmt;
		return;
	}
	if (choose == "IF") {
		stmt = new IFTHEN(scanner);
		stmt->execute(lineNumber, state);
		parsed[lineNumber] = stmt;
		return;
	}
	if (choose == "INPUT") {
		stmt = new INPUT(scanner);
		stmt->execute(lineNumber, state);
		parsed[lineNumber] = stmt;
		return;
	}
	if (choose == "PRINT") {
		stmt = new PRINT(scanner);
		stmt->execute(lineNumber, state);
		parsed[lineNumber] = stmt;
		return;
	}
	if (choose == "GOTO") {
		stmt = new GOTO(scanner);
		stmt->execute(lineNumber, state);
		parsed[lineNumber] = stmt;
		return;
	}
	if (choose == "END") {
		stmt = new END(scanner);
		stmt->execute(lineNumber, state);
		parsed[lineNumber] = stmt;
		return;
	}
	cout<<"SYNTAX ERROR";
	return;
}


void Program::runOneStatement(string input, Statement* stmt, EvalState& state) {
	TokenScanner scanner;
	scanner.setInput(input);
	string choose = scanner.nextToken();
	int lineNumber = 0;
	if (choose == "REM") {
		stmt = new REM(scanner);
		stmt->execute(lineNumber, state);
		return;
	}
	if (choose == "LET") {
		stmt = new LET(scanner);
		stmt->execute(lineNumber, state);
		return;
	}
	if (choose == "IF") {
		stmt = new IFTHEN(scanner);
		stmt->execute(lineNumber, state);
		return;
	}
	if (choose == "INPUT") {
		stmt = new INPUT(scanner);
		stmt->execute(lineNumber, state);
		return;
	}
	if (choose == "PRINT") {
		stmt = new PRINT(scanner);
		stmt->execute(lineNumber, state);
		return;
	}
	if (choose == "GOTO") {
		stmt = new GOTO(scanner);
		stmt->execute(lineNumber, state);
		return;
	}
	if (choose == "END") {
		stmt = new END(scanner);
		stmt->execute(lineNumber, state);
		return;
	}
	cout << "SYNTAX ERROR";
	return;
}

Statement *Program::getParsedStatement(int lineNumber) {
	parsedIter == parsed.find(lineNumber);
	if (parsedIter == parsed.end()) return NULL;
	return (parsedIter->second);
}

int Program::getFirstLineNumber() {
	if (store.size() == 0) return -1;
	storeIter = store.begin();
	return (storeIter->first);
}

int Program::getNextLineNumber(int lineNumber) {
	storeIter = store.find(lineNumber);
	if (storeIter == store.end()) return -1;
	storeIter++;
	if (storeIter == store.end()) return -1;
	return (storeIter->first);
};
