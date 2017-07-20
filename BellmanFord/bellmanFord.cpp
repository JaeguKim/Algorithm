#include <iostream>
#include <fstream>
#include "adjList.h"
#include "topological.h"

#define MAX 100
#define INF 987654321

using namespace std;

typedef struct block {
	int area;
	int height;
	int weight;
} block;

int height[MAX];
int d[MAX];
int P[MAX];

int main(void)
{
	ifstream fin;
	int n; //��������
	block block_ary[MAX];
	int color[MAX], p[MAX];
	LinkedList _adjList[MAX];
	LinkedList output;

	fin.open("input.txt");
	fin >> n;

	//�ʱ� block ���� �ʱ�ȭ
	for (int i = 0; i <= n; i++)
	{
		if (i == 0)
		{
			block_ary[0].area = INF;
			block_ary[0].weight = INF;
			continue;
		}
		else if (i == n + 1)
		{
			block_ary[n + 1].area = -INF;
			block_ary[n + 1].weight = -INF;
			continue;
		}
		fin >> block_ary[i].area >> block_ary[i].height >> block_ary[i].weight; //ó�� �������� �޾ƿ���
		_adjList[0].createNode(i); //start node�� ����
	}

	//block������ ��������Ʈ����
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			if (i == j)
				continue;
			if (block_ary[i].area >= block_ary[j].area && block_ary[i].weight > block_ary[j].weight)
			{
				_adjList[i].createNode(j);
			}
		}
	}

	//���� vertex�� ����
	for (int i = 0; i <= n; i++)
	{
		_adjList[i].createNode(n+1); 
	}

	//���� adjList ���
	for (int i = 0; i <= n+1; i++)
	{
		_adjList[i].printAdjList(i);
	}

	//���������� ����� output�� ����
	Topological_sort(n, color, p, _adjList, output); 

	//output���� sort�迭�� ���� �� �������� �ʱ�ȭ
	int cnt = 0;
	int sort[MAX]; //output���� ������ �迭����
	for (Node *temp = output.getRoot()->head; temp != NULL; temp = temp->next)
	{
		if (temp->vertex == 0)
		{
			sort[cnt] = 0;
			height[cnt++] = 0;
			continue;
		}
		sort[cnt] = temp->vertex;
		height[cnt++] = block_ary[temp->vertex].height;
	}
	sort[n + 1] = n + 1;

	//B&F �˰����� d�迭 �ʱ�ȭ
	d[0] = 0;
	for (int i = 1; i <= n+1; i++)
	{
		d[i] = -INF;
	}

	//Bellan Ford algo
	for (int i = 0; i <= n; i++)
	{
		for (int j = i + 1; j <= n+1; j++)
		{
			//edge�� �����ϸ�
			if (block_ary[sort[i]].area > block_ary[sort[j]].area && block_ary[sort[i]].weight > block_ary[sort[j]].weight) 
			{
				if (d[j] < d[i] + height[i])
				{
					d[j] = d[i] + height[i];
					P[sort[j]] = sort[i];
				}
			}
		}
	}

	cout << endl;
	int temp = n+1;
	int cnt2 = 0;
	int idx_ary[MAX];
	while (P[temp] != 0)
	{
		temp = P[temp];
		idx_ary[cnt2++] = temp;
	}
	cout << "used block count : " << cnt2 << endl;

	for (int i = 0; i <= cnt2 - 1; i++)
		cout << idx_ary[i] << endl;
	
	cout << "height : " << d[cnt] << endl;
}