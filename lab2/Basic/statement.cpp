/*
* File: statement.cpp
* -------------------
* This file implements the constructor and destructor for
* the Statement class itself.  Your implementation must do
* the same for the subclasses you define for each of the
* BASIC statements.
*/

#include <string>
#include "statement.h"
#include "evalstate.h"
#include "exp.h"
#include"parser.h"

#include "../StanfordCPPLib/strlib.h"
#include "../StanfordCPPLib/tokenscanner.h"
#include "../StanfordCPPLib/error.h"
using namespace std;

/* Implementation of the Statement class */

Statement::Statement() {
	/* Empty */
}

Statement::~Statement() {
	/* Empty */
}

/*
 * Implementation notes: the REM subclass
 * ----------------------------------------------
 * The REM subclass skip line of comments.
 */
REM::REM(TokenScanner &scanner) {
}

void REM::execute(int &lineNumber, EvalState &state) {
	return;
}

/*
 * Implementation notes: the LET subclass
 * ----------------------------------------------
 * The LET subclass declares a Expression *ex that represent statement after LET.
 */
LET::LET(TokenScanner &scanner) {
	scanner.ignoreWhitespace();
	ex = parseExp(scanner);
};

void LET::execute(int &lineNumber, EvalState &state) {
	ex->eval(state);
}

/*
 * Implementation notes: the INPUT subclass
 * ----------------------------------------------
 * The INPUT subclass declares a variate and store the its value inputted by users.
 */
INPUT::INPUT(TokenScanner &scanner) {
	scanner.ignoreWhitespace();
	var = scanner.nextToken();
}
void INPUT::execute(int &lineNumber, EvalState &state) {
	int value;
	while (true) {
		try {
			cout << " ? ";
			string str;
			getline(cin, str);
			value = stringToInteger(str);
			break;
		}
		catch (ErrorException & ex) {
			cout << "INVALID NUMBER" << endl;
		}
	}
	state.setValue(var, value);
}

/*
 * Implementation notes: the PRINT subclass
 * ----------------------------------------------
 * The PRINT subclass declares a Expression *ex that represent statement after PRINT and print the value.
 */
PRINT::PRINT(TokenScanner &scanner) {
	scanner.ignoreWhitespace();
	ex = parseExp(scanner);
}
void PRINT::execute(int &lineNumber, EvalState &state) {
	int value = ex->eval(state);
	cout << value << endl;
}

/*
 * Implementation notes: the END subclass
 * ----------------------------------------------
 * The END subclass stops the execution by changing current lineNumber.
 */
END::END(TokenScanner &scanner) {
	scanner.ignoreWhitespace();
}
void END::execute(int &lineNumber, EvalState &state) {
	lineNumber = -1;
}

/*
 * Implementation notes: the GOTO subclass
 * ----------------------------------------------
 * The GOTO subclass changes current lineNumber.
 */
GOTO::GOTO(TokenScanner &scanner) {
	scanner.ignoreWhitespace();
	scanner.scanNumbers();
	var = scanner.nextToken();
}
void GOTO::execute(int &lineNumber, EvalState &state) {
	lineNumber = stringToInteger(var);
}

/*
 * Implementation notes: the IFTHEN subclass
 * ----------------------------------------------
 * The IFTHEN subclass checks evaluating condition.If true, it changes current lineNumber.
 */
IFTHEN::IFTHEN(TokenScanner &scanner) {
	scanner.ignoreWhitespace();

}
void IFTHEN::execute(int &lineNumber, EvalState &state) {

}

