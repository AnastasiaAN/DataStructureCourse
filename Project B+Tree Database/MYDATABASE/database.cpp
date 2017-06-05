#include"database.h"

database::database() :key(""), data("")
{
	index_file_name = "index_file.txt";
	fstream index_file(index_file_name.c_str(), ios::in | ios::out | ios::binary);
	if (!index_file)
	{
		create_index_file();
	}
	index_file.close();

	data_file_name = "data_file.txt";
	fstream data_file(data_file_name.c_str(), ios::in | ios::out | ios::binary);
	if (!data_file)
	{
		create_data_file();
	}
	data_file.close();
}

void database::create_index_file()//Create a new file
{
	fstream index_file(index_file_name.c_str(),ios::out | ios::binary);
}

void database::create_data_file()//Create a new file
{
	fstream data_file(data_file_name.c_str(), ios::out | ios::binary);;
}

void database::make_record(stringstream &information)
{
	information >> key >> data;
	new_record.key = key;
	new_record.data = data;
}

void database::make_key(stringstream &information)
{
	information >> key;
}

void database::insert_record()
{
	fstream index_file(index_file_name.c_str(), ios::in | ios::out | ios::binary);
	fstream data_file(data_file_name.c_str(), ios::in | ios::out | ios::binary);
	data_file.seekg(0, ios::end);
	int data_file_end = data_file.tellg();
	new_record.data_offset = data_file_end;
	if (index_file.is_open())
	{
		int flag = index.insert_node(index_file, new_record, data_file_end);
		if (flag==1)//new record
		{
			index_file.flush();
			string data = new_record.data;
			data_file.write(data.c_str(), data.size());
			data_file.flush();
		}
		else if (flag == 0)
		{
			cout << "Record exists."<<endl;
		}
		else if (flag == -1)//There was a record with the same key once deleted
		{
			string data = new_record.data;
			data_file.write(data.c_str(), data.size());
			data_file.flush();
		}
	}
	index_file.close();
	data_file.close();
}

string database::find_record()
{
	fstream index_file(index_file_name.c_str(), ios::in | ios::out | ios::binary);
	fstream data_file(data_file_name.c_str(), ios::in | ios::out | ios::binary);
	string infor = index.find_node(index_file, key);
	if (infor != "") {//find
		stringstream information(infor);
		int data_offset, data_size;
		information >> data_offset >> data_size;
		data_file.seekg(data_offset, ios::beg);
		string data;
		//read data
		char* readChars = new char[data_size + 1];
		data_file.read(readChars, data_size);
		readChars[data_size] = '\0';
		data = readChars;
		delete readChars;

		cout << data << endl;
		return data;
	}
	cout << "Record doesn't exist."<<endl;
	return "";//Not find
	index_file.close();
	data_file.close();
}

void database::replace_record()
{
	fstream index_file(index_file_name.c_str(), ios::in | ios::out | ios::binary);
	fstream data_file(data_file_name.c_str(), ios::in | ios::out | ios::binary);
	data_file.seekp(0, ios::end);
	int data_file_end = data_file.tellp();
	int data_offset = index.replace_node(index_file, new_record);
	if (data_offset == -1)
	{
		cout << "Record doesn't exist."<<endl;
	}
	else if (data_offset != -1)
	{
		data_file.seekg(data_offset, ios::beg);
		data_file.write(data.c_str(), data.size());
	}
	index_file.close();
	data_file.close();
}

void database::delete_record()
{
	fstream index_file(index_file_name.c_str(), ios::in | ios::out | ios::binary);
	fstream data_file(data_file_name.c_str(), ios::in | ios::out | ios::binary);
	index.delete_node(index_file, key);
	index_file.close();
	data_file.close();
}

void database::clear()
{
	index.clear_tree();
}