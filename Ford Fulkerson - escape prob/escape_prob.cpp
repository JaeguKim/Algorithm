#include <iostream>
#include <fstream>
#include <math.h>
#include "adjList.h"
#include "MyQueue.h"
#include "FF.h"

#define MAX_VERTEX 850
#define MAX_INPUT 20000

using namespace std;

typedef struct new_input {
	int input_v1, input_v2, input_c;
} input;

void convert_Input(char input_mattrix[][MAX_VERTEX],input _inputAry[],int n,int s, int t, int &input_cnt,int &start_cnt)
{
	int row_cnt = 2 * n;
	int node_cnt = 1;
	
	//matrix�� ���� starting point���� ��ο���
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (input_mattrix[i][j] == '1')
			{
				_inputAry[input_cnt].input_v1 = 0;
				_inputAry[input_cnt].input_v2 = i*row_cnt + 2 * j + 1;
				_inputAry[input_cnt++].input_c = 1;
				start_cnt++;
			}
		}
	}
	//1������ t-1������ ��忬��
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < row_cnt - 1; j++)
		{
			_inputAry[input_cnt].input_v1 = node_cnt;
			_inputAry[input_cnt].input_v2 = node_cnt + 1;
			_inputAry[input_cnt++].input_c = 1;

			if (j == row_cnt - 2)  //������ �ݺ��Ҷ� t�� �տ���忡 ����
			{
				_inputAry[input_cnt].input_v1 = node_cnt + 1;
				_inputAry[input_cnt].input_v2 = t;
				_inputAry[input_cnt++].input_c = 1;

				_inputAry[input_cnt].input_v1 = node_cnt + 1;
				_inputAry[input_cnt].input_v2 = node_cnt - 2;
				_inputAry[input_cnt++].input_c = 1;

				if (i == 0) //ù��°���̸� �Ʒ��ʹ���� ����
				{
					_inputAry[input_cnt].input_v1 = node_cnt + 1;
					_inputAry[input_cnt].input_v2 = node_cnt + row_cnt;
					_inputAry[input_cnt++].input_c = 1;
				}
				else if (i == n - 1) //���������̸� ���ʹ���� ����
				{
					_inputAry[input_cnt].input_v1 = node_cnt + 1;
					_inputAry[input_cnt].input_v2 = node_cnt - row_cnt;
					_inputAry[input_cnt++].input_c = 1;
				}
				else //�߰����̸� ���Ʒ� ��� ����
				{
					_inputAry[input_cnt].input_v1 = node_cnt + 1;
					_inputAry[input_cnt].input_v2 = node_cnt + row_cnt;
					_inputAry[input_cnt++].input_c = 1;

					_inputAry[input_cnt].input_v1 = node_cnt + 1;
					_inputAry[input_cnt].input_v2 = node_cnt - row_cnt;
					_inputAry[input_cnt++].input_c = 1;
				}
			}

			if (i == 0 && node_cnt % 2 == 0) //ù��° ���̸鼭, node��ȣ�� 2�ǹ���̸� t�� �����ϰ� ���� ���� ���� 
			{
				_inputAry[input_cnt].input_v1 = node_cnt;
				_inputAry[input_cnt].input_v2 = node_cnt + row_cnt - 1;
				_inputAry[input_cnt++].input_c = 1;

				_inputAry[input_cnt].input_v1 = node_cnt;
				_inputAry[input_cnt].input_v2 = t;
				_inputAry[input_cnt++].input_c = 1;

				if (j != 1) //�࿡�� ù��° ¦���� �����ϰ�� �տ� ���� ����
				{
					_inputAry[input_cnt].input_v1 = node_cnt;
					_inputAry[input_cnt].input_v2 = node_cnt - 3;
					_inputAry[input_cnt++].input_c = 1;
				}
				node_cnt++;
				continue;
			}
			if (i == n - 1 && node_cnt % 2 == 0) //���������̸鼭 node_cnt�� 2�ǹ���̸� t�� �����ϰų� �ؿ��� ���� ���� 
			{
				_inputAry[input_cnt].input_v1 = node_cnt;
				_inputAry[input_cnt].input_v2 = node_cnt - row_cnt - 1;
				_inputAry[input_cnt++].input_c = 1;

				_inputAry[input_cnt].input_v1 = node_cnt;
				_inputAry[input_cnt].input_v2 = t;
				_inputAry[input_cnt++].input_c = 1;

				if (j != 1) //�࿡�� ù��° ¦���� �����ϰ�� �տ� ���� ����
				{
					_inputAry[input_cnt].input_v1 = node_cnt;
					_inputAry[input_cnt].input_v2 = node_cnt - 3;
					_inputAry[input_cnt++].input_c = 1;
				}
				node_cnt++;
				continue;
			}
			if (node_cnt % 2 == 0) //�������࿡ ���ؼ��� �ذ� ����� �����ϱ�
			{
				_inputAry[input_cnt].input_v1 = node_cnt;
				_inputAry[input_cnt].input_v2 = node_cnt + row_cnt - 1;
				_inputAry[input_cnt++].input_c = 1;

				_inputAry[input_cnt].input_v1 = node_cnt;
				_inputAry[input_cnt].input_v2 = node_cnt - row_cnt - 1;
				_inputAry[input_cnt++].input_c = 1;

				if (j == 1) //�ι�° �ݺ��Ҷ� t�� ����
				{
					_inputAry[input_cnt].input_v1 = node_cnt;
					_inputAry[input_cnt].input_v2 = t;
					_inputAry[input_cnt++].input_c = 1;
				}
				if (j != 1) //�࿡�� ù��° ¦���� �����ϰ�� �տ� ���� ����
				{
					_inputAry[input_cnt].input_v1 = node_cnt;
					_inputAry[input_cnt].input_v2 = node_cnt - 3;
					_inputAry[input_cnt++].input_c = 1;
				}
			}
			node_cnt++;
		}
		node_cnt++; //������ �������� +2�� �߰�������
	}
}
int main(void)
{
	ifstream fin;
	fin.open("input7.txt");

	int n;
	char temp_mattrix[MAX_VERTEX][MAX_VERTEX];
	fin >> n;

	
	int s = 0;
	int t = 2 * pow(n , 2) + 1;
	int temp;

	//mattrix �ʱ�ȭ
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			fin >> temp_mattrix[i][j];
		}
	}

	int color[MAX_VERTEX], p[MAX_VERTEX], d[MAX_VERTEX];
	LinkedList _adjList[MAX_VERTEX];
	input input[MAX_INPUT]; // ���ο� input���� ��ȯ�ؼ� ������ ����t
	MyQueue _queue;
	
	int input_cnt = 0;
	int start_cnt = 0;

	convert_Input(temp_mattrix, input, n,s,t,input_cnt, start_cnt);
	//��ȯ �Ϸ�
	int V_num = t - 1;
	int E_num = input_cnt;
	/*cout << V_num << " " << E_num << endl;
	for (int i = 0; i < input_cnt; i++)
	{
		cout << input[i].input_v1 << " " << input[i].input_v2 << " " << input[i].input_c << endl;
	}
	cout << endl;*/

	Node * tempNode1;
	Node * tempNode2;

	//��������Ʈ ����
	int input_v1, input_v2, input_c;
	for (int i = 0; i < E_num; i++)
	{
		input_v1 = input[i].input_v1;
		input_v2 = input[i].input_v2;
		input_c = input[i].input_c;
		tempNode1 = _adjList[input_v1].createNode(input_v2, input_c);
		tempNode2 = _adjList[input_v2].findNode(input_v1);
		if (tempNode2 == NULL) //�ݴ�������� ���³�尡 ������
			tempNode2 = _adjList[input_v2].createNode(input_v1, 0); //���������
																	//(u,v),(v,u) ����
		tempNode1->other = tempNode2;
		tempNode2->other = tempNode1;
	}

	/*cout << "adjList before FF algorithm : " << endl;
	for (int i = 0; i <= V_num + 1; i++)
	{
		_adjList[i].printAdjList(i);
	}
	cout << endl;*/

	int maxFlow = 0; //maxFlow�� �ʱ�ȭ
	FF(s, t, V_num + 2, color, p, d, _adjList, _queue, maxFlow);
	if (maxFlow == start_cnt)
	{
		cout << "start : " << start_cnt << " " << "= maxflow : " << maxFlow << endl;
		cout << "escape success!" << endl;
		return 0;
	}
	cout << "start : " << start_cnt << " " << "!= maxflow : " << maxFlow << endl;
	cout << "escape fail!" << endl;
	return 0;
}


