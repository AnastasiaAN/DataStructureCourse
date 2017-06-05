#pragma once


#include <iostream>
#include<vector>
#include<string>
using namespace std;
const char over = '\n';

class Name_pairs {
	//OVERVIEW:a set of names and ages which are one-one mapping
	vector<string>name;
	vector<double>age;
public:
	vector<string>get_name();
	vector<double>get_age();
	void read_names();
	//MODIFIES:vector<string>name
	//EFFECTS:save names inputed by user in vector
	void read_ages();
	//MODIFIES:vector<string>age
	//EFFECTS:save names inputed by user in vector
	void print();
	//EFFECTS:print all the name and age in pairs like (name,age)
	void sort();
	//MODIFIES:this
	//EFFECTS:sort the name vertor and change the age vector accordingly
};

void Name_pairs::read_names()
{
	string names;
    while(cin>>names){
		name.push_back(names);
		if (cin.get() ==over )
			break;	
	}
}
void Name_pairs::read_ages()
{
	double ages;
	for (int i = 0; i < name.size(); i++) {
		cout << "input age of " << name[i]<<':';//input the age according to the name
		cin >> ages;
		age.push_back(ages);
	}
}
void Name_pairs::print() 
{
	for (int i = 0; i < name.size(); i++) {
		cout << '(' << name[i] << ',' << age[i] <<')'<< endl;//print (name,age)
	}
}
void Name_pairs::sort()
{
	for (int i = 0; i < name.size(); i++)
	{
		for (int j = name.size()-1; j >i;j--)
		{
			if (name[i] > name[j]) {
				string temp_name = name[i];
				name[i] = name[j];
				name[j] = temp_name;
				double temp_age = age[i];
				age[i] = age[j];
				age[j] = temp_age;
			}
		}
	}//sort two vectors  by bubble sorting
}

vector<string> Name_pairs::get_name()
{
	return name;
}
vector<double> Name_pairs::get_age()
{
	return age;
}
ostream&operator<<(ostream&os,Name_pairs&Np)//make "<<" work like print()
{
	for (int i = 0; i < Np.get_age().size(); i++)
	{
		 os << '(' << Np.get_name()[i] << ',' << Np.get_age()[i] << ')' << endl;
	}
	return os;
}

bool operator==(Name_pairs&first,Name_pairs&second)//judge if two Name_pairs equal regardless of the elements order
{
	Name_pairs first_copy=first;
	Name_pairs second_copy = second;
	first.sort();
	second.sort();
	bool equal = first.get_name() == second.get_name()
		&& first.get_age() == second.get_age();
	first = first_copy;
	second = second_copy;
	return equal;
}

bool operator!=(Name_pairs&first,Name_pairs&second)//judge if two Name_pairs inequal regardless of the elements order
{
	return !(first == second);
}
