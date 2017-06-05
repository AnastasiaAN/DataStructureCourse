#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<sstream>
#include<cmath>
#include<time.h>
#define DOUBLE_MIN -1.79E+308
#define DOUBLE_MAX 1.79E+308
using namespace std;

//task information
struct task
{
	string name;
	double CPU;
	double memory;
	double time;
	bool done = false;
};
//host information
struct Host
{
	string name;
	double total_CPU;
	double total_memory;
	double remaining_CPU;
	double remaining_memory;
	int job = 0;
	bool on = false;
	vector<task>Host_task;
};
//cluster
class Scheduler {
private:
	vector<Host>Hosts;
	vector<task> new_tasks;
	vector<task>undone;
	clock_t time=clock();//initiaize
public:
	Scheduler(string& file_name);
	bool clear=true;
	void update_tasks();
	void choose_Host();
	void print_cluster();
	double calculate(const double&task_CPU, const double&task_memory,const double& total_CPU, const double& remaining_CPU, const double& total_memory, const double& remaining_memory);
	void update_cluster();
	void make_task(string& get_task);
	bool ask_clear();
};

//initialize
Scheduler::Scheduler(string& file_name)
{
	ifstream cluster_infor(file_name.c_str());
	if (cluster_infor.is_open())
	{
		string Host_infor;
		while (getline(cluster_infor, Host_infor))
		{
			string name;
			double CPU, memory;
			istringstream infor(Host_infor);
			infor >> name >> CPU >> memory;
			Host new_Host;
			new_Host.name = name;
			new_Host.total_CPU = CPU;
			new_Host.remaining_CPU = new_Host.total_CPU;
			new_Host.total_memory = memory;
			new_Host.remaining_memory = new_Host.total_memory;
			Hosts.push_back(new_Host);
		};
	}
};
//print cluster information
void Scheduler::print_cluster()
{
	for (int i = 0; i < Hosts.size(); i++)
	{
		cout << "Host:" << Hosts[i].name <<" total job:"<< Hosts[i].job<< endl;
		cout << "         " << "total CPU of this Host:" << Hosts[i].total_CPU << " total memory of this Host:" << Hosts[i].total_memory << endl;
		cout << "         " << "remaining CPU of this Host:" << Hosts[i].remaining_CPU << " remaining memory of this Host:" << Hosts[i].remaining_memory << endl;
		if (Hosts[i].on)
		{
			for (int j = 0; j < Hosts[i].job; j++)
			{
				cout << "         "
					<< Hosts[i].Host_task[j].name << ' '
					<< "CPU:" << Hosts[i].Host_task[j].CPU
					<< " memory:" << Hosts[i].Host_task[j].memory
					<< endl;
			}
		}
		else
		{
			cout << "         " << "This host isn't running now."<<endl;
		}
		cout << endl;
	}
	cout << endl;
}
//calculate to find out which host is the best choice
double Scheduler::calculate(const double&task_CPU, const double&task_memory,const double& total_CPU, const double& remaining_CPU, const double& total_memory, const double& remaining_memory)
{
	double priority = (total_CPU - remaining_CPU)/total_CPU + (total_memory - remaining_memory)/total_memory - fabs(task_CPU/remaining_CPU - task_memory/remaining_CPU);
	return priority;
}

void Scheduler::choose_Host()
{
	Host* choose=nullptr;
	double priority = DOUBLE_MIN;
	vector<int>used_computers;
	int used_computer = -1;
	for (int j = 0; j < new_tasks.size(); j++) 
	{
		for (int i = 0; i < Hosts.size(); i++)
		{
			bool used = false;
			for (int k = 0; k < used_computers.size(); k++)
			{
				if (used_computers[k] == i)
				{
					used = true;
					break;
				}
			}
			if (new_tasks[j].CPU < Hosts[i].remaining_CPU&&new_tasks[j].memory < Hosts[i].remaining_memory&&!used)
			{
				double now_priority = calculate(new_tasks[j].CPU, new_tasks[j].memory, Hosts[i].total_CPU, Hosts[i].remaining_CPU, Hosts[i].total_memory, Hosts[i].remaining_memory);
				if (now_priority > priority)
				{
					priority = now_priority;
					choose = &(Hosts[i]);
					new_tasks[j].done=true;
					used_computer = i;
				}
			}
		}
		if (new_tasks[j].done)
		{
			(*choose).on = true;
			(*choose).Host_task.push_back(new_tasks[j]);
			(*choose).job++;
			(*choose).remaining_CPU -= new_tasks[j].CPU;
			(*choose).remaining_memory -= new_tasks[j].memory;
			used_computers.push_back(used_computer);
			priority = DOUBLE_MIN;
			choose = nullptr;
		}
		else
		{
			undone.push_back(new_tasks[j]);
			cout << "Cluster is too busy to deal with " << new_tasks[j].name << endl;
		}
	}
}

//delete tasks that have been done already
void Scheduler::update_cluster()
{
	clock_t now = clock();
	double duration = double((now - time)/CLOCKS_PER_SEC);
	time = now;
	for (int i = 0; i < Hosts.size(); i++)
	{
		if (Hosts[i].on == true)
		{
			vector<task>::iterator iter;
			bool erase = false;
			for (iter = Hosts[i].Host_task.begin(); iter != Hosts[i].Host_task.end(); iter++)
			{
				if (erase)
				{
					iter--;
					erase = false;
				}
				if (duration >= (*iter).time)
				{
					Hosts[i].remaining_CPU += (*iter).CPU;
					Hosts[i].remaining_memory += (*iter).memory;
					iter=Hosts[i].Host_task.erase(iter);
					erase = true;
				}
				if (iter == Hosts[i].Host_task.end())
				{
					break;
				}
			}
			Hosts[i].job = Hosts[i].Host_task.size();
			if (Hosts[i].job != 0)//specially deal with the last task
			{
				iter = Hosts[i].Host_task.end();
				iter--;
				if (duration >= (*iter).time)
				{
					Hosts[i].remaining_CPU += (*iter).CPU;
					Hosts[i].remaining_memory += (*iter).memory;
					iter = Hosts[i].Host_task.erase(iter);
				}
				Hosts[i].job = Hosts[i].Host_task.size();
			}
			if (Hosts[i].job == 0)//shut down this host
			{
				Hosts[i].on = false;
			}
		}
	}
}

//deal with tasks information
void Scheduler::make_task(string& get_task)
{
	string name;
	double CPU, memory, time;
	int copy;
	istringstream task_infor(get_task);
	task_infor >> name >> CPU >> memory>>time>>copy;
	for (int i = 0; i < copy; i++) {
		task new_task;
		if (copy > 1) {
			string copy_name;
			stringstream order;
			order << i + 1;
			string task_order = order.str();
			copy_name = name + "(copy" + task_order + ")";
			new_task.name = copy_name;
		}
		else {
			new_task.name = name;
		}
		new_task.CPU = CPU/1000;
		new_task.memory = memory;
		new_task.time = time;
		new_tasks.push_back(new_task);
	}
}

void Scheduler::update_tasks()
{
	if (clear)
	{
		new_tasks.clear();
	}
	else
	{
		new_tasks = undone;
	}
	undone.clear();
}

bool Scheduler::ask_clear()
{
	return (undone.size() != 0);
}

int main()
{
	string file_name = "Hosts.txt";
	Scheduler sche(file_name);	//initialize cluster
	while (true) {
		sche.update_tasks();
		sche.clear = false;
		string get_task = "";
		cout << "Please input new job information:" << endl;
		getline(cin,get_task);
		sche.update_cluster(); 
		sche.make_task(get_task);
		sche.choose_Host();
		sche.print_cluster();
		if (sche.ask_clear())
		{
			cout << "Clear or not?(input 'clear' to skip tasks undone)";
			string get_order = "";
			getline(cin, get_order);
			if (get_order == "clear")
			{
				sche.clear = true;
			}
		}
	}
	return 0;
}

