#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <queue>
#include <vector>
using namespace std;

void show_ans(vector<string>& ans, queue<vector<string>>&search_queue,int&go) {//cout the found ladder
	cout << "Found ladder:";
	cout << ans[0];
	for (int i = 1; i < ans.size(); i++) {
		cout << "->" << ans[i];
	}
	cout << endl << endl;
	go = 0;
	for (int i = 0; i < search_queue.size(); i++)//clear the queue
		search_queue.pop();
}

void input_words(string& start, string& dest, set<string>&English,int&go) {
	cout << "Enter start word (enter ':q' to quit):";
	cin >> start;
	if (start == ":q") {
		exit(0);
	}
	cout << "Enter destination word:";
	cin >> dest;
	if ((English.find(start) == English.end()) ||( English.find(dest) == English.end()) ||( start.size() != dest.size())) {//if start word or destination word is not in file ,or they have different numbers of characters
		cout << "No Ladder found"<<endl<<endl;
		go = 0;
	}
}

void read_English(set<string>& English) {
	while (true) {
		cout << "Please enter filename containing source text:";
		string file_name;
		cin >> file_name;
		ifstream file_input(file_name.c_str());
		if (file_input.is_open()) {
			string temp_word;
			while (getline(file_input, temp_word)) {//save words in the file into a set
				English.insert(temp_word);
			}
		}
		break;
	}
}

bool used_words(const string &word, set<string> &used) {
	return (used.find(word) != used.end());//whether the word has been used in ladder or not
}
void different_words(string last_word, vector<string>&different_word, set<string>& English,set<string> used,vector<char>&English_characters) {
	for (int i = 0; i < last_word.size(); i++)
	{
		for (int j = 0; j < English_characters.size(); j++)
		{
			string temp_word = last_word;
			temp_word[i] = English_characters[j];//the word similar to last word in ladder
			if ((English.find(temp_word)!=English.end())&(!used_words(temp_word, used)))//all words similar to last word and these words need to exsit in file
				different_word.push_back(temp_word);
		}
	}
}

void expand_queue(queue<vector<string>>&search_queue, vector<string>&different_word,set<string> used, string& start, string& dest,int&go, set<string>& English, vector<char>&English_characters) {
	search_queue.push({ start });//push start word into queue
	used.insert(start);
	different_words({ start },different_word,English,used,English_characters);
	vector<string> new_ladder;
	while (!search_queue.empty()) {
		vector<string>first_ladder = search_queue.front();
		if (first_ladder[first_ladder.size() - 1] == dest) {//found the ladder
			show_ans(first_ladder,search_queue,go);
			break;
		}
		else {
			string last_word = first_ladder[first_ladder.size() - 1];
			different_words(last_word, different_word, English, used, English_characters);//find similar words
			for (int i = 0; i < different_word.size(); i++) {
				new_ladder = search_queue.front();
				new_ladder.push_back(different_word[i]);//create new ladder
				search_queue.push(new_ladder);
				used.insert(different_word[i]);
			}
			different_word.clear();//clear the vector to avoid mistakes in next time of finding ladder
			search_queue.pop();//delete first ladder
		}
	}
	if (go == 1) {
		cout << "No Ladder found." << endl<<endl;//having not shown answers
	}
}

int main() {
	set<string>used;
	vector<string>different_word;
	set<string>English;
	string start, dest;
	int go = 1;
	read_English(English);//read the file
	vector<char>English_characters;
	for (char i = 'a'; i <= 'z'; i++) {//26 English characters
		English_characters.push_back(i);
	}
	while (true) {
 		go = 1;
		queue<vector<string>>search_queue;
		input_words(start, dest,English,go);
		if (go == 1) {//the start and destination word match the requirements
			expand_queue(search_queue,different_word,used,start,dest,go,English,English_characters);
		}
	}
}
