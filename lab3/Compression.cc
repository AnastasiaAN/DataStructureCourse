#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include<map>
#include<vector>
using namespace std;


struct Node 
{
	char ch;
	int times;
	Node* left;
	Node* right;
};

void scanFile(fstream& input_file,map<unsigned char,int>& content)
{
	char temp;
	unsigned char ch;
	while(input_file.get(temp)){
		ch=(unsigned char)temp;
		if(content.find(ch)==content.end())
			content[ch]=1;
		else
			content[ch]++;
	}
}

Node* minNode(vector<Node>& save_node,int& pos,vector<Node>& help_save_node,int& help_pos)
{
	if(pos==(save_node.size()-1))
		{
			help_pos++;
			return &help_save_node[help_pos-1];
		}
	int size=help_save_node.size()-help_pos;
	switch(size)
	{
		case 0:
		{
			pos++;
			return &save_node[pos-1];
		}
		default:
		{
			if(save_node[pos].times<=help_save_node[help_pos].times)
			{
				pos++;
				return &save_node[pos-1];
			}
			else
			{
				help_pos++;
				return &help_save_node[help_pos-1];
			}
		}
	}
}

Node* huffmanTree(vector<Node>save_node,int& length)
{
	vector<Node>help_save_node;
	int pos=0;
	int help_pos=0;
	for(int i=0;i<length-1;i++)
	{
		Node* minNode1=minNode(save_node,pos,help_save_node,help_pos);
		Node* minNode2=minNode(save_node,pos,help_save_node,help_pos);
		save_node[i].left=minNode1;
		save_node[i].right=minNode2;
		save_node[i].ch=0;
		save_node[i].times=minNode1->times+minNode2->times;
		help_save_node.push_back(save_node[i]);
	}
	Node* root=&save_node[length-2];
	return root;
}

void compressTree(fstream& output_file,Node* node,map<unsigned char,string>chToBits,string bits,string& tree,string& judge)
{
	if(node->left==NULL)
	{
		chToBits[node->ch]=bits;
		tree+=node->ch;
		judge+="l";
		int size=bits.size();
		bits=bits.substr(0,size-1);
		return;
	}
	else
	{
		tree+=node->ch;
		judge+="n";
		bits+="0";
		compressTree(output_file,node->left,chToBits,bits,tree,judge);
		bits+="1";
		compressTree(output_file,node->right,chToBits,bits,tree,judge);
		int size=bits.size();
		if(size>0)
		{
			bits=bits.substr(0,size-1);
		}
		return;
	}
}

void compress(string inputFilename,string outputFilename)
{	
	ifstream input_file(inputFilename.c_str(), ios::in | ios::binary);
	ofstream output_file(outputFilename.c_str(), ios::out | ios::binary);
        map<unsigned char,int>content;
	scanFile(input_file,content);
	int length=content.size();
        vector<Node>save_node(length);
	map<unsigned char,int>::iterator it;
	int pos=0;
	for(content.begin();it!=content.end();it++){
		save_node[pos].ch=(*it).first;
		save_node[pos].times=(*it).second;
		save_node[pos].left=NULL;
		save_node[pos].right=NULL;
		pos++;
	}

	//create a huffman tree
	Node* root=huffmanTree(save_node,length);

	//write head
	map<unsigned char,string>chToBits;
	string bits="";
	string tree="";
	string judge="";
	compressTree(output_file,root,chToBits,bits,tree,judge);
	length=tree.size();
	output_file.write(reinterpret_cast<char*>(&length), sizeof(int));
	output_file.write(tree.c_str(), length);
	output_file.write(judge.c_str(), length);

	//write body
	char temp;
	unsigned char ch;
	bits="";
	string now;
	input_file.close();
	ifstream ifs(inputFilename.c_str(), ios::in | ios::binary);
	while(input_file.get(temp))
	{
		ch=(unsigned char)temp;
		bits+=chToBits[ch];
		while(bits.length()>=8)
		{
			cout<<endl;
			now=bits.substr(0,8);
			if(bits.length()==8)
				bits="";
			else
				bits=bits.substr(8);
			output_file.write(now.c_str(),sizeof(char));//TODO
		}
	}
	if(bits!="")
	{
		bits="00000000";
		bits=bits.substr(8);
		output_file.write(bits.c_str(),sizeof(char));//TODO
	}
	input_file.close();
	output_file.close();
}
void decompressTree(string& tree,string& judge,Node* node)
{
	int length=tree.size();
	unsigned char ch=tree[0];
	node->ch=ch;
	if(length==1)
	{
		return;
	}
	length-=1;
	tree=tree.substr(1);	
	int pos=0;
	int root=0;
	int leaf=0;
	while(pos<length||leaf!=(root+1))
	{
		unsigned char now=tree[pos];
		if(now=='0'&&judge[pos]=='n')
		{	
		root+=1;
		}	
		else
		{
		leaf+=1;
		}
		pos++;
	}
	string leftTree=tree.substr(0,pos);
	string rightTree=tree.substr(pos);
	Node* nodeLeft;
	Node* nodeRight;
	nodeLeft->ch=leftTree[0];
	nodeRight->ch=rightTree[0];
	node->left=nodeLeft;
	node->right=nodeRight;
	decompressTree(judge,leftTree,nodeLeft);
	decompressTree(judge,rightTree,nodeRight);
}

void preorder(Node* node,map<string,unsigned char>& bitsToCh,string& bits)
{
	if(node->left == NULL)
	{
		bitsToCh[bits]=node->ch;
		int length=bits.size();
		bits=bits.substr(0,length-1);
		return;
	}
	else
	{
		bits+="0";
		preorder(node->left,bitsToCh,bits);
		bits+="1";
		preorder(node->right,bitsToCh,bits);
	}
}
void decompress(string inputFilename,string outputFilename)
{
	ifstream input_file(inputFilename.c_str(), ios::in | ios::binary);
	ofstream output_file(outputFilename.c_str(), ios::out | ios::binary);
	//read head
	int length;
	string tree,judge;
	int pos=0;
	char temp;
	unsigned char ch;
	while(pos<length)//TODO
	{	
		input_file.get(temp);
		ch=(unsigned char)temp;
		tree+=ch;
		pos++;
	}
	pos=0;
	while(pos<length)
	{	
		input_file.get(temp);
		ch=(unsigned char)temp;
		judge+=ch;
		pos++;
	}
	Node* root;
	decompressTree(tree,judge,root);
	map<string,unsigned char>bitsToCh;
	string bits="";
	preorder(root,bitsToCh,bits);
	//write
	string now="";
	string buffer="";
	pos=input_file.tellg();
	input_file.seekg(0,ios::end);
	int end=input_file.tellg();
	input_file.seekg(pos);
	while(input_file.tellg()!=end)
	{
		if(buffer.size()==0)
		{
			char temp;
			input_file.read(&temp,sizeof(char));
			ch=(unsigned char)temp;
			buffer+=ch;//TODO
		}
		if(bitsToCh.find(now)!=bitsToCh.end())
		{
			output_file.write(&bitsToCh[now],sizeof(char));//TODO
			now="";
			pos++;
			if(pos==length)
			{
				break;
			}
		}
		else
		{
			now+=buffer[0];
			if(buffer.size()==1)
			{
				buffer=="";
			}
			else
			{
				buffer==buffer.substr(1);
			}
		}
	}
	input_file.close();
	output_file.close();
}


void useage(string prog)
{
	cerr << "Useage: " << endl
	<< "    " << prog << "[-d] input_file output_file" << endl;
	exit(2);
}

int main(int argc, char* argv[]) 
{
	int i;
	string inputFilename, outputFilename;
	bool isDecompress = false;
	for (i = 1; i < argc; i++) 
	{
		if (argv[i] == string("-d")) isDecompress = true;
		else if (inputFilename == "") inputFilename = argv[i];
		else if (outputFilename == "") outputFilename = argv[i];
		else useage(argv[0]);
	}
	if (outputFilename == "") useage(argv[0]);
	if (isDecompress) decompress(inputFilename, outputFilename);
	else compress(inputFilename, outputFilename);
	return 0;
}
