#pragma once
#include <iostream>
#include <fstream>
#include <math.h>
#include "adjList.h"
#include "MyQueue.h"

#define WHITE -1
#define GRAY 0
#define BLACK 1
#define INF 987654321;
#define MAX_VERTEX 850
#define MAX_INPUT 20000

void BFS(int s, int t, int V_num, int *color, int *p, int *d, LinkedList _adjList[], MyQueue &_queue) {

	for (int u = 0; u <= V_num - 1; u++)
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
	int residualCap;

	while (_queue.isEmpty() == false)
	{
		u = _queue.getFront();
		for (Node * temp = _adjList[u].getRoot()->head; temp != NULL; temp = temp->next)
		{
			residualCap = temp->capacity - temp->flow;
			if (residualCap > 0 && color[temp->vertex] == WHITE) { //residual capacity > 0 �� �����߰�
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

void FF(int s, int t, int V_num, int *color, int *p, int *d, LinkedList _adjList[], MyQueue &_queue, int &maxFlow)
{
	Node * _path[MAX_VERTEX];

	while (1)
	{
		BFS(s, t, V_num, color, p, d, _adjList, _queue);
		if (p[t] == -1) // ���̻� ��ΰ� ����
		{
			//���̻� ��ΰ� ������ �׷��� �������
			/*cout << "adjList after FF algorithm" << endl;
			for (int i = 0; i <= V_num - 1; i++)
			{
				_adjList[i].printAdjList(i);
			}
			cout << endl;*/
			return;
		}

		//��θ� ã������ �׷����� �ٽ� setting
		int temp_idx = t;
		//Node ������ �迭�� ��λ��� �������
		for (int i = d[t] - 1; i >= 0; i--) //����� ���̸�ŭ �ݺ�
		{
			_path[i] = _adjList[p[temp_idx]].findNode(temp_idx);
			temp_idx = p[temp_idx];
		}
		//residual capacity ã��
		int residual_cap = INF;
		for (int i = 0; i <= d[t] - 1; i++)
		{
			if ((_path[i]->capacity - _path[i]->flow) < residual_cap)
				residual_cap = _path[i]->capacity - _path[i]->flow;
		}
		//��λ��� ������ flow������
		for (int i = 0; i <= d[t] - 1; i++)
		{
			_path[i]->flow = _path[i]->flow + residual_cap;
			_path[i]->other->flow = 0 - _path[i]->flow;
		}
		//maxFlow�� ����
		maxFlow = maxFlow + residual_cap;
	}
}