#include <iostream>
#include <fstream>
#include "adjList.h"
#include "MyQueue.h"

#define WHITE -1
#define GRAY 0
#define BLACK 1
#define MAX_VERTEX 1000
#define INF 987654321;

using namespace std;

void BFS(int s,int V_num, int *color, int *p, int *d, LinkedList _adjList[], MyQueue &_queue) {
	
	for (int u = 1; u <= V_num; u++)
	{
		if (u == s)
			continue;
		color[u] = WHITE;
		d[u] = INF;
		p[u] = -1;
	}
	color[s] = GRAY;
	d[s] = 0;
	p[s] = -1;
	_queue._enqueue(s);

	int u = 0;
	while (_queue.isEmpty() == false)
	{
		u = _queue.getFront();
		for (Node * temp = _adjList[u].getRoot()->head; temp != NULL; temp = temp->next)
		{
			if (color[temp->vertex] == WHITE) {
				color[temp->vertex] = GRAY;
				d[temp->vertex] = d[u] + 1;
				p[temp->vertex] = u;
				_queue._enqueue(temp->vertex);
			}
		}
		_queue._dequeue();
		color[u] = BLACK;
	}
}

int main(void)
{
	ifstream fin;
	fin.open("input.txt");

	int V_num, E_num;

	fin >> V_num >> E_num;

	int color[MAX_VERTEX], p[MAX_VERTEX], d[MAX_VERTEX];
	LinkedList _adjList[MAX_VERTEX];
	MyQueue _queue;

	int input_v1, input_v2;
	for (int i = 0; i < E_num; i++)
	{
		fin >> input_v1 >> input_v2;
		_adjList[input_v1].createNode(input_v2);
	}
	
	cout << "adjList : " << endl;
	for (int i = 1; i <= V_num; i++)
	{
		_adjList[i].printAdjList(i);
	}

	cout << endl;
	BFS(1,V_num, color, p, d,  _adjList,_queue);
	cout << "bfs p[i] : ";
	for (int i = 1; i<= V_num; i++)
	{
		cout << p[i] << " ";
	}
	cout << endl;

}


