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
			if (residualCap > 0 && color[temp->vertex] == WHITE) { //residual capacity > 0 인 조건추가
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
		if (p[t] == -1) // 더이상 경로가 없음
		{
			//더이상 경로가 없을때 그래프 정보출력
			/*cout << "adjList after FF algorithm" << endl;
			for (int i = 0; i <= V_num - 1; i++)
			{
				_adjList[i].printAdjList(i);
			}
			cout << endl;*/
			return;
		}

		//경로를 찾았으면 그래프를 다시 setting
		int temp_idx = t;
		//Node 포인터 배열에 경로상의 노드저장
		for (int i = d[t] - 1; i >= 0; i--) //경로의 길이만큼 반복
		{
			_path[i] = _adjList[p[temp_idx]].findNode(temp_idx);
			temp_idx = p[temp_idx];
		}
		//residual capacity 찾기
		int residual_cap = INF;
		for (int i = 0; i <= d[t] - 1; i++)
		{
			if ((_path[i]->capacity - _path[i]->flow) < residual_cap)
				residual_cap = _path[i]->capacity - _path[i]->flow;
		}
		//경로상의 노드들의 flow값변경
		for (int i = 0; i <= d[t] - 1; i++)
		{
			_path[i]->flow = _path[i]->flow + residual_cap;
			_path[i]->other->flow = 0 - _path[i]->flow;
		}
		//maxFlow값 증가
		maxFlow = maxFlow + residual_cap;
	}
}