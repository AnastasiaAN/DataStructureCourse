/*
* File: statement.h
* -----------------
* This file defines the Statement abstract type.  In
* the finished version, this file will also specify subclasses
* for each of the statement types.  As you design your own
* version of this class, you should pay careful attention to
* the exp.h interface specified in Chapter 17, which is an
* excellent model for the Statement class hierarchy.
*/

#ifndef _statement_h
#define _statement_h

#include "evalstate.h"
#include "exp.h"
#include"parser.h"

#include "../StanfordCPPLib/tokenscanner.h"
/*
* Class: Statement
* ----------------
* This class is used to represent a statement in a program.
* The model for this class is Expression in the exp.h interface.
* Like Expression, Statement is an abstract class with subclasses
* for each of the statement and command types required for the
* BASIC interpreter.
*/

class Statement {

public:

	/*
	* Constructor: Statement
	* ----------------------
	* The base class constructor is empty.  Each subclass must provide
	* its own constructor.
	*/

	Statement();

	/*
	* Destructor: ~Statement
	* Usage: delete stmt;
	* -------------------
	* The destructor deallocates the storage for this expression.
	* It must be declared virtual to ensure that the correct subclass
	* destructor is called when deleting a statement.
	*/

	virtual ~Statement();

	/*
	* Method: execute
	* Usage: stmt->execute(state);
	* ----------------------------
	* This method executes a BASIC statement.  Each of the subclasses
	* defines its own execute method that implements the necessary
	* operations.  As was true for the expression evaluator, this
	* method takes an EvalState object for looking up variables or
	* controlling the operation of the interpreter.
	*/

	virtual void execute(int &lineNumber, EvalState &state) = 0;

};

/*
 * Class: REM
 * ------------------
 * This subclass represents statement REM.
 */
class REM :public Statement {
public:
/*
 * Constructor: REM
 * Usage: stmt = new REM(scanner);
 * ------------------------------------------------
 * The constructor initializes a new REM statement.
 */
	REM(TokenScanner &scanner);
/*
 * Method: execute
 * Usage: stmt->execute(lineNumber, state);
 * -----------------------------------------------------
 * Ignore the comments.
 */
	virtual void execute(int &lineNumber, EvalState &state);
};

/*
 * Class: LET
 * ------------------
 * This subclass represents statement LET.
 */
class LET :public Statement {
public:
/*
 * Constructor: LET
 * Usage: stmt = new LET(scanner);
 * ------------------------------------------------
 * The constructor initializes a new LET statement.
 */
	LET(TokenScanner &scanner);
	virtual ~LET() {};
/*
 * Method: execute
 * Usage: stmt->execute(lineNumber, state);
 * -----------------------------------------------------
 * Assignment statement.
 */
	virtual void execute(int &lineNumber, EvalState &state);
private:
	Expression *ex;
};

/*
 * Class: INPUT
 * ------------------
 * This subclass represents statement INPUT.
 */
class INPUT :public Statement {
public:
/*
 * Constructor: INPUT
 * Usage: stmt = new INPUT(scanner);
 * ------------------------------------------------
 * The constructor initializes a new INPUT statement.
 */
	INPUT(TokenScanner &scanner);
	virtual ~INPUT() {};
/*
 * Method: execute
 * Usage: stmt->execute(lineNumber, state);
 * -----------------------------------------------------
 * Print a prompt consisting of the string " ? " and then to read in a value to be stored in the variable.
 */
	virtual void execute(int &lineNumber, EvalState &state);
private:
	string var;
};

/*
 * Class: PRINT
 * ------------------
 * This subclass represents statement PRINT.
 */
class PRINT :public Statement {
public:
/*
 * Constructor: PRINT
 * Usage: stmt = new PRINT(scanner);
 * ------------------------------------------------
 * The constructor initializes a new PRINT statement.
 */
	PRINT(TokenScanner &scanner);
	virtual ~PRINT() {};
/*
 * Method: execute
 * Usage: stmt->execute(lineNumber, state);
 * -----------------------------------------------------
 * Print the value of the expression on the console and then print a newline character. 
 */
	virtual void execute(int &lineNumber, EvalState &state);
private:
	Expression *ex;
};

/*
 * Class: END
 * ------------------
 * This subclass represents statement END.
 */
class END :public Statement {
public:
/*
 * Constructor: END
 * Usage: stmt = new END(scanner);
 * ------------------------------------------------
 * The constructor initializes a new END statement.
 */
	END(TokenScanner &scanner);
	virtual ~END() {};
/*
 * Method: execute
 * Usage: stmt->execute(lineNumber, state);
 * -----------------------------------------------------
 * Marks the end of the program. Execution halts when this line is reached. Execution also stops if the
 * program continues past the last numbered line.   
 */
	virtual void execute(int &lineNumber, EvalState &state);
};

/*
 * Class: GOTO
 * ------------------
 * This subclass represents statement GOTO.
 */
class GOTO :public Statement {
public:
/*
 * Constructor: GOTO
 * Usage: stmt = new GOTO(scanner);
 * ------------------------------------------------
 * The constructor initializes a new GOTO statement.
 */
	GOTO(TokenScanner &scanner);
	virtual ~GOTO() {};
/*
 * Method: execute
 * Usage: stmt->execute(lineNumber, state);
 * -----------------------------------------------------
 * Transfers control unconditionally to line n in the program. 
 */
	virtual void execute(int &lineNumber, EvalState &state);
private:
	string var;
};

/*
 * Class: IFTHEN
 * ------------------
 * This subclass represents statement IF THEN .
 */
class IFTHEN :public Statement {
public:
/*
 * Constructor: IFTHEN
 * Usage: stmt = new IFTHEN(scanner);
 * ------------------------------------------------
 * The constructor initializes a new IFTHEN statement.
 */
	IFTHEN(TokenScanner &scanner);
	virtual ~IFTHEN() {};
/*
 * Method: execute
 * Usage: stmt->execute(lineNumber, state);
 * -----------------------------------------------------
 * Performs a conditional transfer of control.  
 */
	virtual void execute(int &lineNumber, EvalState &state);
private:
       Expression *ex;
       int then;
       string exp;
};

#endif
