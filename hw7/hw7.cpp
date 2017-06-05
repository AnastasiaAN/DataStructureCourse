// ConsoleApplication20.cpp : 定义控制台应用程序的入口点。
//

#include <iostream>
#include<vector>
using namespace std;

typedef enum{UNDISCOVERED,DISCOVERED}Vstatus;
typedef enum { USED,UNUSED }Etype;

template<typename Tv>struct Vertex {
	Tv data;
	int priority;
	Vertex(Tv const&d) :data(d), priority(INT_MAX) {};
};
template<typename Tv>
class Graph {
private:
	int v_number;
	int martrix_weight[v_number][v_number];
	Etype martrix_type[v_number][v_number];
	vector<Vertex<Tv>>V_data;
	vector<Vertex<Tv>>V_status;
public:
	Graph(const &v_number) {
		for (int i = 0; i < v_number; i++) {
			for (int j = 0; j < v_number; j++) {
				martrix_weight[i][j] = MAX_INT;
				martrix_type[i][j] = UNUSED;
			}
			new Vertex ver;
			ver.data = i;
			ver.priority = MAX_INT;
			V_data.pushback(Vertex ver);
			V_status.pushback(UNDISCOVERED);
		}
		V_data[0].priority = 0;
		V_status[0] = DISCOVERED;
	};
	~Graph() {
	};
	virtual void get_data() = 0;
	virtual void dijgkstra() = 0;
	virtual void near(const Tv&j) = 0;
	virtual void new_priority(const Tv&i, const Tv&j) = 0;
	virtual void smallest_weight(const Tv&j) = 0;
};
template<typename Tv, typename Te>
void Graph::get_data() {

	Tv data1, data2;
	int data3;
	while (true) {
		cin >> data1;
		cin >> data2;
		cin >> data3;
		martrix_weight[data1][data2] = data3;
	}
};
template<typename Tv>
void Graph::dijgkstra() {
	Tv i = V[0];
	while (j.data != v_number) {
		TV j = smallest_weight(i);
		new_priority(i, j);
	}
};
template<typename Tv>
void Graph::near(const Tv&j) {
	vector<Vertex<Tv>>near;
	for (int i = 0; i < v_number; i++)
		if (martrix_weight[j][i] != INT_MAX)
			near.push_back(V_data[i]);
};
template<typename Tv>
void Graph::new_priority(const Tv&i,const Tv&j) {
	if (j.priority > i.priority + martrix_weight[i][j])
		j.priority = i.priority + martrix_weight[i][j];
	near(j);
	for (int i = 0; i < near.size(); i++) {
		if (near[i].priority > i.priority + martrix_weight[near[i]][j]) {
			j.priority = near[i].priority + martrix_weight[near[i]][j];
			martrix_type[i][j] = UNUSED;
		}
	}
};
template<typename Tv>
void Graph::smallest_weight(const Tv&j) {
	int smallest = MAX_INT;
	Tv small = j;
	for (int k = 0; k < V_status.size();k++)
	for (int i = 0; i < v_number; i++) {
		if (smallest > martrix_weight[k][i]|| martrix_type[i][j]=UNUSED){
		smallest = martrix_weight[k][i];
		small = V_data.i;
		V_status[i] = DISCOVERED;
		martrix_type[i][j.data] = USED;
		};
	};
	return small;
};

int main()
{
	int v_number;
	cin >> v_number;

	return 0;
}

