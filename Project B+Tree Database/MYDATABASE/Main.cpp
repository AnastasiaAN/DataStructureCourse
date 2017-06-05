#include"database.h"

int main()
{
	database MYDATABASE;
	while (true) {
		string input = "";
		cout << "Please input:" << endl;
		getline(cin, input);
		if (input == "QUIT")
		{
			exit(0);
		}
		stringstream infor(input);
		string ACTION;
		infor >> ACTION;
		if (ACTION == "INSERT")
		{
			MYDATABASE.make_record(infor);
			MYDATABASE.insert_record();
		}
		else if (ACTION == "FIND")
		{
			MYDATABASE.make_key(infor);
			MYDATABASE.find_record();
		}
		else if (ACTION == "REPLACE")
		{
			MYDATABASE.make_record(infor);
			MYDATABASE.replace_record();
		}
		else if (ACTION == "DELETE")
		{
			MYDATABASE.make_key(infor);
			MYDATABASE.delete_record();
		}
		else
		{
			cout << "Wrong input." << endl << endl;
		}
	}
	return 0;
}

