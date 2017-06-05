#include"BPTree.h"
#include<sstream>
#include<vector>

void BPNode::clear_node(BPNode* node)
{
	if (node != NULL)
	{
		clear_node(node);
		for (int i = 0; i < node->record_size; i++)
		{
			BPNode* child = node->records[i].child;
			clear_node(child);
			delete child;
		}
		delete node;
	}
	delete[] records;
}

void BPTree::clear_tree()
{
	if (root != NULL)
	{
		root->clear_node(root);
		delete root;
		root = NULL;
	}
}

bool BPTree::split_node(fstream& index_file, int& parent_offset,BPNode* child, BPNode* parent)
{
	int pos;
	record split_record = child->records[HALF];
	child->record_size = HALF;//split
	for (pos = 0; pos < parent->record_size; pos++)
	{
		if (parent->records[pos].key>split_record.key)
		{
			break;
		}
	}
	parent->record_size++;
	for (int j = parent->record_size - 1; j > pos; j--)
	{
		parent->records[j] = parent->records[j - 1];
	}
	int size_offset;
	size_offset = parent->records[pos - 1].child_offset;
	size_offset += sizeof(int);
	index_file.seekp(size_offset, ios::beg);
	index_file.write(reinterpret_cast<char*>(&child->record_size), sizeof(int));
	parent->records[pos] = split_record;
	BPNode* new_child = new BPNode();//new node
	parent->records[pos].child = new_child;
	for (int i = 0; i < HALF + 1; i++)
	{
		new_child->records[i] = child->records[i + HALF];
	}
	parent->records[pos].key = new_child->records[0].key;//change key
	index_file.seekg(0, ios::end);
	int end = index_file.tellg();
	parent->records[pos].child_offset = end;
	new_child->record_size = HALF + 1;
	if (new_child->records[0].child_offset == 0)
	{
		new_child->internal_or_leaf = 0;
	}
	else
	{
		new_child->internal_or_leaf = 1;
	}
	write_node(index_file, end, new_child);//write new node
	return (parent->record_size == MAX_BRANCH);
}

void BPTree::write_key(fstream& index_file, string& key, BPNode* now, BPNode* parent)//改成传offset
{
	int pos;
	for (pos = 0; pos < parent->record_size; pos++)
	{
		if (parent->records[pos].child == now)
			break;
	}
	int offset = parent->records[pos].child_offset + 2*sizeof(int);
	int size = key.size();
	index_file.write(reinterpret_cast<char*>(&size), sizeof(int));
	index_file.write(key.c_str(), size);
}

int BPTree::insert_node(fstream& index_file, record& record, int& data_file_end)
{
	if (root == NULL)
	{
		root = new BPNode();
	}
	BPNode* now = root;
	vector<BPNode*>tree;
	vector<int>key_pos;
	int pos = 0;
	int root_offset,now_offset,offset, end_offset;
	bool key_change = false;
	string key = record.key;
	index_file.seekg(0, ios::end);
	if (index_file.tellg() == streamoff(0))
	{
		root->internal_or_leaf = 0;
		root_offset = sizeof(int);
		index_file.write(reinterpret_cast<char*>(&root_offset), sizeof(int));
		index_file.flush();
	}
	else
	{
		index_file.seekg(0, ios::beg);
		index_file.read(reinterpret_cast<char*>(&root_offset), sizeof(int));
		if (root->record_size == 0)
		{
			read_node(index_file, root_offset, now);
		}
	}
	tree.push_back(root);
	//插入值为新的最小值 需递归改key
	if (root->records[0].key > key)
	{
		while (now->records[0].child_offset != 0)
		{
			key_pos.push_back(0);
			now_offset = now->records[0].child_offset;
			now = now->records[0].child;
			if (now->record_size == 0)
			{
				read_node(index_file, now_offset, now);
			}
			tree.push_back(now);
		}
		key_change = true;
		for (int j = now->record_size; j > 0; j--)
		{
			now->records[j] = now->records[j - 1];
		}
		now->records[0] = record;
		for (int i = tree.size() - 2; i >= 1; i--)
		{
			tree[i]->records[0].key = key;
			write_key(index_file, key, tree[i], tree[i - 1]);
		}
		//改root的key
		index_file.seekp(root_offset + 2 * sizeof(int), ios::beg);
		int size = key.size();
		index_file.write(reinterpret_cast<char*>(&size), sizeof(int));
		index_file.write(key.c_str(), size);
	}
	else//不是最小值
	{
		while (now->records[0].child_offset != 0)
		{
			for (pos = 0; pos < now->record_size; pos++)
			{
				if (now->records[pos].key>key)
				{
					break;
				}
			}
			key_pos.push_back(pos - 1);
			now_offset = now->records[pos - 1].child_offset;
			now = now->records[pos - 1].child;
			if (now->record_size == 0)
			{
				read_node(index_file, now_offset, now);
			}
			tree.push_back(now);
		}
	}
	int pos_size = key_pos.size();
	if (tree.size() == 1)//only root node
	{
		if (!key_change)
		{
			for (pos = 0; pos < now->record_size; pos++)
			{
				if (now->records[pos].key == key)
				{
					int data_offset = now->records[pos].data_offset;
					if (data_offset == -1)
					{
						now->records[pos].data_size = record.data.size();
						now_offset = root_offset + (3 * sizeof(int) + MAX_STRING_SIZE)*(pos + 1);
						index_file.seekp(now_offset, ios::beg); 
						index_file.write(reinterpret_cast<char*>(&data_file_end), sizeof(int));
						index_file.write(reinterpret_cast<char*>(&now->records[pos].data_size), sizeof(int));
						now->records[pos].data_offset = data_file_end;
						return -1;
					}
					else
					{
						return 0;
					}
				}
				if (now->records[pos].key>key)
				{
					break;
				}
			}
			if (pos == now->record_size)
			{
				now->records[pos] = record;
			}
			else
			{
				for (int j = now->record_size; j > pos; j--)
				{
					now->records[j] = now->records[j - 1];
				}
				now->records[pos] = record;
			}
		}
		now->record_size++;
		write_node(index_file, root_offset, now);
	}
	else//tree
	{
		if (!key_change)
		{
			for (pos = 0; pos < now->record_size; pos++)
			{
				if (now->records[pos].key == key)
				{
					int data_offset = now->records[pos].data_offset;
					if (data_offset == -1)
					{
						now->records[pos].data_size = record.data.size();
						now_offset = tree[tree.size() - 2]->records[key_pos[tree.size() - 2]].child_offset + (3 * sizeof(int) + MAX_STRING_SIZE)*(pos + 1);
						index_file.seekp(now_offset, ios::beg);
						index_file.write(reinterpret_cast<char*>(&data_file_end), sizeof(int));
						index_file.write(reinterpret_cast<char*>(&now->records[pos].data_size), sizeof(int));
						now->records[pos].data_offset = data_file_end;
						return -1;
					}
					else
					{
						return 0;
					}
				}
				if (now->records[pos].key>key)
				{
					break;
				}
			}
			if (pos == now->record_size)
			{
				now->records[pos] = record;
			}
			else
			{
				for (int j = now->record_size; j > pos; j--)
				{
					now->records[j] = now->records[j - 1];
				}
				now->records[pos] = record;
			}
		}
		now->record_size++;
		index_file.seekp(0, ios::end);
		end_offset = index_file.tellp();
		write_node(index_file, end_offset, now);
		int parent_pos = key_pos[pos_size - 1];
		tree[tree.size() - 2]->records[parent_pos].child_offset = end_offset;
		offset = (2 * sizeof(int) + MAX_STRING_SIZE)*(parent_pos + 1) + sizeof(int);
		if (tree.size() == 2)
		{
			offset += root_offset;
		}
		else
		{
			offset += tree[tree.size() - 3]->records[key_pos[pos_size - 2]].child_offset;
		}
		index_file.seekp(offset, ios::beg);
		index_file.write(reinterpret_cast<char*>(&end_offset), sizeof(int));
	}
	if (now->record_size == MAX_BRANCH)//split
	{	
		int tree_size = tree.size();
		for (pos = tree_size - 1; pos >= 1; pos--)
		{
			int parent_offset;
			if (pos > 1)
			{
				parent_offset = tree[pos - 2]->records[key_pos[pos - 2]].child_offset;
			}
			else
			{
				parent_offset = root_offset;
			}
			if (!split_node(index_file, parent_offset, tree[pos], tree[pos - 1]))
			{
				index_file.seekp(0, ios::end);
				offset = index_file.tellp();
				write_node(index_file, offset, tree[pos - 1]);
				if (parent_offset == root_offset)
				{
					index_file.seekp(0, ios::beg);
					index_file.write(reinterpret_cast<char*>(&offset), sizeof(int));
				}
				else if(pos==2)
				{
					now_offset =root_offset+ (3*sizeof(int)+MAX_STRING_SIZE)*(key_pos[pos-2]+1);
					index_file.seekp(now_offset,ios::beg);
					index_file.write(reinterpret_cast<char*>(&offset), sizeof(int));
				}
				else if (pos > 2)
				{
					now_offset = tree[pos - 3]->records[key_pos[pos - 2]].child_offset + (3 * sizeof(int) + MAX_STRING_SIZE)*(key_pos[pos - 2] + 1);
					index_file.seekp(now_offset, ios::beg);
					index_file.write(reinterpret_cast<char*>(&offset), sizeof(int));
				}				
				return 1;
			}
			else
			{
				index_file.seekp(0, ios::end);
				offset = index_file.tellp();
				write_node(index_file, offset, tree[pos - 1]);
				if (parent_offset == root_offset)
				{
					index_file.seekp(0, ios::beg);
					index_file.write(reinterpret_cast<char*>(&offset), sizeof(int));
				}
				else if (pos == 2)
				{
					now_offset = root_offset +  (3 * sizeof(int) + MAX_STRING_SIZE)*(key_pos[pos - 2] + 1);
					index_file.seekp( now_offset,ios::beg);
					index_file.write(reinterpret_cast<char*>(&offset), sizeof(int));
				}
				else if (pos > 2)
				{
					now_offset = tree[pos - 3]->records[key_pos[pos - 2]].child_offset +  (3 * sizeof(int) + MAX_STRING_SIZE)*(key_pos[pos - 2] + 1);
					index_file.seekp( now_offset,ios::beg);
					index_file.write(reinterpret_cast<char*>(&offset), sizeof(int));
				}
			}
		}
		if (pos == 0 && root->record_size == MAX_BRANCH)//split root   
		{
			BPNode* left = root;
			left->record_size = HALF;
			char internal_or_leaf;
			if (left->records[0].child != NULL)
			{
				left->internal_or_leaf = 1;
				internal_or_leaf = '1';
			}
			else
			{
				left->internal_or_leaf = 0;
				internal_or_leaf = '0';
			}
			BPNode* right = new BPNode();
			for (int i = 0; i < HALF + 1; i++)
			{
				right->records[i] = left->records[i + HALF];
			}
			right->record_size = HALF + 1;
			if (right->records[0].child != NULL)
			{
				right->internal_or_leaf = 1;
			}
			root = new BPNode();
			root->records[0].child = left;
			root->records[0].key = left->records[0].key;
			index_file.seekp(0, ios::beg);
			index_file.read(reinterpret_cast<char*>(&root_offset), sizeof(int));
			root->records[0].child_offset = root_offset;
			root->records[1].child = right;
			root->records[1].key = right->records[0].key;
			index_file.seekp(0, ios::end);
			end_offset = index_file.tellp();
			root->records[1].child_offset = end_offset;
			root->record_size = 2;
			root->internal_or_leaf = 1;
			write_node(index_file, end_offset, right);
			end_offset = index_file.tellp();
			write_node(index_file, end_offset, root);
			index_file.seekp(0, ios::beg);
			index_file.write(reinterpret_cast<char*>(&end_offset), sizeof(int));
			index_file.seekp(root_offset, ios::beg);
			int half = HALF;
			index_file.write(reinterpret_cast<char*>(&left->internal_or_leaf), sizeof(int));
			index_file.write(reinterpret_cast<char*>(&half), sizeof(int));
		}
	}
	return 1;
}


string BPTree::find_node(fstream& index_file, const string& key)
{
	if (root == NULL)
	{
		root = new BPNode();
	}
	int pos, root_offset;
	BPNode* now = root;
	index_file.read(reinterpret_cast<char*>(&root_offset), sizeof(int));
	if (now->record_size == 0)
	{
		read_node(index_file, root_offset, now);
	}
	while (now->records[0].child_offset!=0)
	{
		for (pos = 0; pos < now->record_size; pos++)
		{
			if (now->records[pos].key>key)
				break;
		}
		int now_offset = now->records[pos - 1].child_offset;
		now = now->records[pos - 1].child;
		if (now->record_size == 0)
		{			
			read_node(index_file, now_offset, now);
		}
	}
	for (int i = 0; i < now->record_size; i++)
	{
		if (now->records[i].key == key)
		{
			if (now->records[i].data_offset == -1)//deleted
			{
				return "";
			}
			string offset, size;
			stringstream offset_infor;
			offset_infor << now->records[i].data_offset;
			stringstream size_infor;
			size_infor << now->records[i].data_size;
			offset_infor >> offset;//data_offset
			size_infor >> size;//data_size
			string infor = offset + ' ' + size;
			return infor;
		}
	}
	return "";
}

int BPTree::replace_node(fstream& index_file, record& record)
{
	string key = record.key;
	int size = record.data.size();
	if (root == NULL)
	{
		root = new BPNode();
	}
	BPNode* now = root;
	int pos, now_offset, root_offset;
	vector<BPNode*>tree;
	index_file.seekp(0, ios::beg);
	index_file.read(reinterpret_cast<char*>(&root_offset), sizeof(int));
	if (now->record_size==0)
	{
		read_node(index_file, root_offset, now);
	}
	tree.push_back(root);
	while (now->records[0].child_offset != 0)
	{
		for (pos = 0; pos < now->record_size; pos++)
		{
			if (now->records[pos].key>key)
				break;
		}
		now = now->records[pos - 1].child;
		tree.push_back(now);
		if (now->record_size == 0)
		{
			now_offset = now->records[pos - 1].child_offset;
			read_node(index_file, now_offset, now);
		}
	}
	if (tree.size() == 1)//only root
	{
		now_offset = root_offset;
	}
	else
	{
		now_offset = tree[tree.size() - 2]->records[pos-1].child_offset;//tree
	}
	for (pos = 0; pos < now->record_size; pos++)
	{
		if (now->records[pos].key == key)
		{
			int data_offset = now->records[pos].data_offset;
			if (data_offset == -1)//deleted
			{
				return -1;
			}	
			now->records[pos].data_size = size;
			now_offset += (3 * sizeof(int) + MAX_STRING_SIZE)*(pos + 1);
			index_file.seekp(now_offset+sizeof(int), ios::beg);		
			index_file.write(reinterpret_cast<char*>(&size), sizeof(int));//rewrite data_size
			return now->records[pos].data_offset;
		}
	}
	return -1;
}

void BPTree::delete_node(fstream& index_file, string& key)//simple version:change data_offset to -1
{
	if (root == NULL)
	{
		root = new BPNode();
	}
	int pos, size, now_offset, root_offset;
	BPNode* now = root;
	index_file.read(reinterpret_cast<char*>(&root_offset), sizeof(int));
	if (now->record_size == 0)
	{
		read_node(index_file, root_offset, now);
	}
	vector<BPNode*>tree;
	vector<int>key_pos;
	tree.push_back(root);
	while (now->records[0].child_offset != 0)
	{
		for (pos = 0; pos< now->record_size; pos++)
		{
			if (now->records[pos].key > key)
			{
				break;
			}
		}
		key_pos.push_back(pos-1);
		now_offset = now->records[pos - 1].child_offset;
		now = now->records[pos - 1].child;
		if (now->record_size == 0)
		{
			read_node(index_file, now_offset, now);
		}
		tree.push_back(now);
	}
	for (pos = 0; pos< now->record_size; pos++)
	{
		if (now->records[pos].key == key)
		{
			now->records[pos].data_offset = -1;
			key_pos.push_back(pos);
			break;
		}
	}
	size = tree.size();
	if (size > 1)
	{
		write_node(index_file, tree[size - 2]->records[key_pos[size - 2]].child_offset, now);
	}
	else
	{
		write_node(index_file, root_offset, now);
	}

}

void BPTree::read_node(fstream& index_file, int& index_offset, BPNode* now)//rebuild B Plus Tree from index file
{
	index_file.seekg(index_offset, ios::beg);
	index_file.read(reinterpret_cast<char*>(&now->internal_or_leaf), sizeof(int));
	index_file.read(reinterpret_cast<char*>(&now->record_size), sizeof(int));
	if (now->internal_or_leaf == 1)//internal
	{
		for (int i = 0; i < now->record_size; i++)
		{
			index_file.read(reinterpret_cast<char*>(&now->records[i].key_size), sizeof(int));

			char* readChars = new char[now->records[i].key_size + 1];
			index_file.read(readChars, now->records[i].key_size);
			readChars[now->records[i].key_size] = '\0';
			now->records[i].key = readChars;
			delete readChars;

			index_file.seekp(MAX_STRING_SIZE - now->records[i].key_size, ios::cur);
			index_file.read(reinterpret_cast<char*>(&now->records[i].child_offset), sizeof(int));
			now->records[i].child = new BPNode();
		}
	}
	else
	{
		for (int i = 0; i < now->record_size; i++)//leaf
		{
			index_file.read(reinterpret_cast<char*>(&now->records[i].key_size), sizeof(int));

			char* readChars = new char[now->records[i].key_size + 1];
			index_file.read(readChars, now->records[i].key_size);
			readChars[now->records[i].key_size] = '\0';
			now->records[i].key = readChars;
			delete readChars;

			index_file.seekp(MAX_STRING_SIZE - now->records[i].key_size, ios::cur);
			int tempInt = now->records[i].data_offset;
			index_file.read(reinterpret_cast<char*>(&tempInt), sizeof(int));
			now->records[i].data_offset = tempInt;
			index_file.read(reinterpret_cast<char*>(&now->records[i].data_size), sizeof(int));
		}
	}
	
}

void BPTree::write_node(fstream& index_file, int& offset, BPNode* now)//write node information into file
{
	index_file.seekp(offset, ios::beg);
	index_file.write(reinterpret_cast<char*>(&now->internal_or_leaf), sizeof(int));
	index_file.write(reinterpret_cast<char*>(&now->record_size), sizeof(int));
	if (now->internal_or_leaf == 1)//internal
	{
		for (int i = 0; i < now->record_size; i++)
		{
			now->records[i].key_size = now->records[i].key.size();
			index_file.write(reinterpret_cast<char*>(&now->records[i].key_size), sizeof(int));
			index_file.write(now->records[i].key.c_str(), now->records[i].key_size);
			index_file.seekp(MAX_STRING_SIZE - now->records[i].key_size, ios::cur);
			index_file.write(reinterpret_cast<char*>(&now->records[i].child_offset), sizeof(int));
			index_file.flush();
		}
		
	}
	else
	{
		for (int i = 0; i < now->record_size; i++)//leaf
		{
			now->records[i].key_size = now->records[i].key.size();
			index_file.write(reinterpret_cast<char*>(&now->records[i].key_size), sizeof(int));
			index_file.write(now->records[i].key.c_str(), now->records[i].key_size);
			index_file.seekp(MAX_STRING_SIZE - now->records[i].key_size, ios::cur);
			index_file.write(reinterpret_cast<char*>(&now->records[i].data_offset), sizeof(int));
			int size = now->records[i].data.size();
			if (size != 0)
			{
				now->records[i].data_size = size;
			}
			index_file.write(reinterpret_cast<char*>(&now->records[i].data_size), sizeof(int));
			index_file.flush();
		}
		
	}
}
