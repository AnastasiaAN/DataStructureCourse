#pragma once

#include<iostream>
#include<fstream>
#include<string>
using namespace std;

#define DEGREE 65
#define HALF DEGREE / 2
#define MIN_BRANCH HALF//For Tree:MIN CHILD SIZE
#define MAX_BRANCH DEGREE//For Tree:MAX CHILD SIZE
#define MAX_STRING_SIZE 50//MAX KEY AND DATA SIZE

struct record;
struct BPNode;
class BPTree;

struct record//Store Record
{
	string key;
	string data;
	BPNode* child;
	int key_size;
	int data_size;
	int child_offset;
	int data_offset;
	record() :key(""), data(""), child(NULL), key_size(0), data_size(0), child_offset(0), data_offset(0) {};
};

struct BPNode//Node of B Plus Tree
{
public:
	BPNode() :record_size(0), internal_or_leaf(0)
	{
		records = new record[MAX_BRANCH+1];
	};
	int internal_or_leaf;//1:internal 0:leaf
	int record_size;
	record* records;
	//internal:  0:bool=1(internal) 1:record_size 2~:【 key长度 key child_offset】多个 
	//leaf:  0:bool=0(leaf) 1:record_size 2~: 【key长度 key data偏移量 data_size】多个 
	void clear_node(BPNode* node);
};

class BPTree
{
public:
	BPTree() {};
	int insert_node(fstream& index_file, record& record, int& data_file_end);
	string find_node(fstream& index_file, const string& key);
	int replace_node(fstream& index_file, record& record);
	void delete_node(fstream& index_file, string& key);
	void clear_tree();//For quit

private:
	BPNode *root;
	bool split_node(fstream& index_file, int& parent_offset,BPNode* child, BPNode* parent);//Split record when record_size is bigger than MAX_BRANCH
	void read_node(fstream& index_file, int& index_offset, BPNode* now);
	void write_node(fstream& index_file, int& offset, BPNode* now);
	void write_key(fstream& index_file, string& key, BPNode* now, BPNode* parent);
};
