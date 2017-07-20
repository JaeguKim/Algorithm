#include <iostream>
#include <fstream>
#include "adjList.h"

#define WHITE -1
#define GRAY 0
#define BLACK 1
#define MAX_VERTEX 1000

using namespace std;

void DFS_visit(int u, int *color, int * p, LinkedList _adjList[])
{
	color[u] = GRAY;
	for (Node * temp = _adjList[u].getRoot()->head; temp != NULL; temp = temp->next)
	{
		if (color[temp->vertex] == WHITE)
		{
			p[temp->vertex] = u;
			DFS_visit(temp->vertex, color,p,_adjList);
		}
	}
	color[u] = BLACK;
}

void DFS(int V_num, int *color, int *p, LinkedList _adjList[]) {
	for (int u = 1; u <= V_num; u++)
	{
		color[u] = WHITE;
		p[u] = -1;
	}
	for (int u = 1; u <= V_num; u++)
	{
		if (color[u] == WHITE)
			DFS_visit(u, color, p, _adjList);
	}
}

int main(void)
{
	ifstream fin;
	fin.open("input.txt");

	int V_num, E_num;
	
	fin >> V_num >> E_num;

	int color[MAX_VERTEX],p[MAX_VERTEX];
	LinkedList _adjList[MAX_VERTEX];

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
	
	DFS(V_num, color, p, _adjList);
	cout << "dfs p[i] : ";
	for (int i = 1; i<= V_num; i++)
	{
		cout << p[i] << " ";
	}
	cout << endl;
}


