#pragma once

#include"BPTree.h"
#include<sstream>
#include<vector>

class database
{
public:
	database();
	void create_index_file();
	void create_data_file();
	void make_record(stringstream &information);
	void make_key(stringstream &information);
	void insert_record();
	string find_record();
	void replace_record();
	void delete_record();
	void clear();
private:
	string key;
	string data;
	record new_record;
	BPTree index;
	string index_file_name;
	string data_file_name;
	fstream index_file;
	fstream data_file;
};