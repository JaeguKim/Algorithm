#pragma once
#include <iostream>

using namespace std;

#define WHITE -1
#define GRAY 0
#define BLACK 1

void DFS_visit(int u, int *color, int * p, LinkedList _adjList[], LinkedList &output)
{
	color[u] = GRAY;
	for (Node * temp = _adjList[u].getRoot()->head; temp != NULL; temp = temp->next)
	{
		if (color[temp->vertex] == WHITE)
		{
			p[temp->vertex] = u;
			DFS_visit(temp->vertex, color, p, _adjList, output);
		}
	}
	color[u] = BLACK;
	output.createPreNode(u);
}

void Topological_sort(int V_num, int *color, int *p, LinkedList _adjList[], LinkedList &output)
{
	for (int u = 0; u <= V_num; u++)
	{
		color[u] = WHITE;
		p[u] = NULL;
	}
	for (int u = 0; u <= V_num; u++)
	{
		if (color[u] == WHITE)
			DFS_visit(u, color, p, _adjList, output);
	}
}