#include"database.h"
#include<ctime>
#include<map>

const string charset = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
const int CHARSIZE = charset.length();
const int nrec = 50;
vector<vector<string>>store_records;

database MYDATABASE;
string rand_key, rand_data;
int count1, count2, count3, count4;

string rand_keys()
{
	int length = rand() % MAX_STRING_SIZE+1;
	if (length > MAX_STRING_SIZE)
	{
		length = MAX_STRING_SIZE;
	}
	string key = "";
	for (int i = 0; i < length; i++)
	{
		key += charset[rand() % CHARSIZE];
	}
	return key;
}

string rand_datas(int length)
{
	if (length == -1)
	{
		length = rand() % MAX_STRING_SIZE +1;
	}
	if (length > MAX_STRING_SIZE)
	{
		length = MAX_STRING_SIZE;
	}
	string data = "";
	for (int i = 0; i < length; i++)
	{
		data += charset[rand() % CHARSIZE];
	}
	return data;
}


void test_insert(database& MYDATABASE, string& key,string& data)
{
	count1++;
	string input = key + ' ' + data;
	stringstream infor(input);
	MYDATABASE.make_record(infor);
	MYDATABASE.insert_record();
}

void test_delete(database& MYDATABASE, string& key, string& data)
{
	count2++;
	string input = key + ' ' + data;
	stringstream infor(input);
	MYDATABASE.make_record(infor);
	MYDATABASE.delete_record();
}

void test_replace(database& MYDATABASE, string& key, string& data)
{
	count3++;
	string input = key + ' ' + data;
	stringstream infor(input);
	MYDATABASE.make_record(infor);
	MYDATABASE.replace_record();
}

void test_find(database& MYDATABASE, string& key, string& data)
{
	count4++;
	string input = key + ' ' + data;
	stringstream infor(input);
	MYDATABASE.make_record(infor);
	string find_data=MYDATABASE.find_record();
	if (find_data != data)
	{
		cout << "WRONG" << endl;
	}
}


void test1()
{
	clock_t begin = clock();
	for (int i = 0; i < nrec; i++)
	{
		rand_key = rand_keys();
		rand_data = rand_datas(-1);
		store_records.push_back({ rand_key, rand_data });
		test_insert(MYDATABASE, rand_key, rand_data);
	}
	clock_t end = clock();
	cout << "INSERT  " << (end - begin)  << " ms"<<endl<<endl;
}

void test2()
{

	clock_t begin = clock();
	for (int i = 0; i < nrec; i++)
	{
		int pos = rand() % store_records.size();
		rand_key = store_records[pos][0];
		rand_data = store_records[pos][1];
		test_find(MYDATABASE, rand_key, rand_data);
	}
	clock_t end = clock();
	cout << "FIND  " << (end - begin)  << " ms"<<endl;
}

void test3()
{
	clock_t begin = clock();
	for (int i = 0; i < 5 * nrec; i++)
	{
		int pos = rand() % store_records.size();
		rand_key = store_records[pos][0];
		rand_data = store_records[pos][1];
		test_find(MYDATABASE, rand_key, rand_data);
		if (i % 37 == 0)
		{
			int pos = rand() % store_records.size();
			rand_key = store_records[pos][0];
			rand_data = store_records[pos][1];
			test_delete(MYDATABASE, rand_key, rand_data);
			store_records[pos][1] = "";
		}
		if (i % 11 == 0)
		{
			rand_key = rand_keys();
			rand_data = rand_datas(-1);
			store_records.push_back({ rand_key, rand_data });
			test_insert(MYDATABASE, rand_key, rand_data);
			test_find(MYDATABASE, rand_key, rand_data);
		}
		if (i % 17 == 0)
		{
			int pos = rand() % store_records.size();
			rand_key = store_records[pos][0];
			rand_data = store_records[pos][1];
			int length = rand_data.size();
			if (i % 34 == 0)
			{
				rand_data = rand_datas(length);
			}
			else
			{
				length = length + rand() % length;
				rand_data = rand_datas(length);
			}
			test_replace(MYDATABASE, rand_key, rand_data);
		}
	}
	clock_t end = clock();
	cout << "TEST3 " << (end - begin)  << " ms" << endl;
}

void test4()
{
	clock_t begin = clock();
	int size = store_records.size();
	for (int i = 0; i < size; i++)
	{
		int pos = rand() % store_records.size();
		rand_key = store_records[pos][0];
		rand_data = store_records[pos][1];
		test_delete(MYDATABASE, rand_key, rand_data);
		store_records[pos][1] = "";
		for (int j = 0; j < 10; j++)
		{
			int pos = rand() % store_records.size();
			rand_key = store_records[pos][0];
			rand_data = store_records[pos][1];
			test_find(MYDATABASE, rand_key, rand_data);
		}
	}
	clock_t end = clock();
	cout << "DELETE" << (end - begin)  << " ms" << endl;
}
int main()
{
	srand(time(NULL));

	MYDATABASE.create_index_file();
	MYDATABASE.create_data_file();
	
	test1();
	test2();
	test3();
	test4();
	cout << count1 << endl << count2 << endl << count3 << endl << count4 << endl;
	return 0;
}

