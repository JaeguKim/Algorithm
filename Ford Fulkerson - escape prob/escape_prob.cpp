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
	
	//matrix를 보고 starting point들을 모두연결
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
	//1번부터 t-1까지의 노드연결
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < row_cnt - 1; j++)
		{
			_inputAry[input_cnt].input_v1 = node_cnt;
			_inputAry[input_cnt].input_v2 = node_cnt + 1;
			_inputAry[input_cnt++].input_c = 1;

			if (j == row_cnt - 2)  //마지막 반복할때 t와 앞에노드에 연결
			{
				_inputAry[input_cnt].input_v1 = node_cnt + 1;
				_inputAry[input_cnt].input_v2 = t;
				_inputAry[input_cnt++].input_c = 1;

				_inputAry[input_cnt].input_v1 = node_cnt + 1;
				_inputAry[input_cnt].input_v2 = node_cnt - 2;
				_inputAry[input_cnt++].input_c = 1;

				if (i == 0) //첫번째행이면 아래쪽방향과 연결
				{
					_inputAry[input_cnt].input_v1 = node_cnt + 1;
					_inputAry[input_cnt].input_v2 = node_cnt + row_cnt;
					_inputAry[input_cnt++].input_c = 1;
				}
				else if (i == n - 1) //마지막행이면 위쪽방향과 연결
				{
					_inputAry[input_cnt].input_v1 = node_cnt + 1;
					_inputAry[input_cnt].input_v2 = node_cnt - row_cnt;
					_inputAry[input_cnt++].input_c = 1;
				}
				else //중간행이면 위아래 모두 연결
				{
					_inputAry[input_cnt].input_v1 = node_cnt + 1;
					_inputAry[input_cnt].input_v2 = node_cnt + row_cnt;
					_inputAry[input_cnt++].input_c = 1;

					_inputAry[input_cnt].input_v1 = node_cnt + 1;
					_inputAry[input_cnt].input_v2 = node_cnt - row_cnt;
					_inputAry[input_cnt++].input_c = 1;
				}
			}

			if (i == 0 && node_cnt % 2 == 0) //첫번째 행이면서, node번호가 2의배수이면 t와 연결하고 밑의 노드와 연결 
			{
				_inputAry[input_cnt].input_v1 = node_cnt;
				_inputAry[input_cnt].input_v2 = node_cnt + row_cnt - 1;
				_inputAry[input_cnt++].input_c = 1;

				_inputAry[input_cnt].input_v1 = node_cnt;
				_inputAry[input_cnt].input_v2 = t;
				_inputAry[input_cnt++].input_c = 1;

				if (j != 1) //행에서 첫번째 짝수를 제외하고는 앞에 노드와 연결
				{
					_inputAry[input_cnt].input_v1 = node_cnt;
					_inputAry[input_cnt].input_v2 = node_cnt - 3;
					_inputAry[input_cnt++].input_c = 1;
				}
				node_cnt++;
				continue;
			}
			if (i == n - 1 && node_cnt % 2 == 0) //마지막행이면서 node_cnt가 2의배수이면 t와 연결하거나 밑에서 위로 연결 
			{
				_inputAry[input_cnt].input_v1 = node_cnt;
				_inputAry[input_cnt].input_v2 = node_cnt - row_cnt - 1;
				_inputAry[input_cnt++].input_c = 1;

				_inputAry[input_cnt].input_v1 = node_cnt;
				_inputAry[input_cnt].input_v2 = t;
				_inputAry[input_cnt++].input_c = 1;

				if (j != 1) //행에서 첫번째 짝수를 제외하고는 앞에 노드와 연결
				{
					_inputAry[input_cnt].input_v1 = node_cnt;
					_inputAry[input_cnt].input_v2 = node_cnt - 3;
					_inputAry[input_cnt++].input_c = 1;
				}
				node_cnt++;
				continue;
			}
			if (node_cnt % 2 == 0) //나머지행에 대해서는 밑과 위모두 연결하기
			{
				_inputAry[input_cnt].input_v1 = node_cnt;
				_inputAry[input_cnt].input_v2 = node_cnt + row_cnt - 1;
				_inputAry[input_cnt++].input_c = 1;

				_inputAry[input_cnt].input_v1 = node_cnt;
				_inputAry[input_cnt].input_v2 = node_cnt - row_cnt - 1;
				_inputAry[input_cnt++].input_c = 1;

				if (j == 1) //두번째 반복할때 t와 연결
				{
					_inputAry[input_cnt].input_v1 = node_cnt;
					_inputAry[input_cnt].input_v2 = t;
					_inputAry[input_cnt++].input_c = 1;
				}
				if (j != 1) //행에서 첫번째 짝수를 제외하고는 앞에 노드와 연결
				{
					_inputAry[input_cnt].input_v1 = node_cnt;
					_inputAry[input_cnt].input_v2 = node_cnt - 3;
					_inputAry[input_cnt++].input_c = 1;
				}
			}
			node_cnt++;
		}
		node_cnt++; //한행이 지나가면 +2을 추가로증가
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

	//mattrix 초기화
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			fin >> temp_mattrix[i][j];
		}
	}

	int color[MAX_VERTEX], p[MAX_VERTEX], d[MAX_VERTEX];
	LinkedList _adjList[MAX_VERTEX];
	input input[MAX_INPUT]; // 새로운 input으로 변환해서 저장할 공간t
	MyQueue _queue;
	
	int input_cnt = 0;
	int start_cnt = 0;

	convert_Input(temp_mattrix, input, n,s,t,input_cnt, start_cnt);
	//변환 완료
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

	//인접리스트 생성
	int input_v1, input_v2, input_c;
	for (int i = 0; i < E_num; i++)
	{
		input_v1 = input[i].input_v1;
		input_v2 = input[i].input_v2;
		input_c = input[i].input_c;
		tempNode1 = _adjList[input_v1].createNode(input_v2, input_c);
		tempNode2 = _adjList[input_v2].findNode(input_v1);
		if (tempNode2 == NULL) //반대방향으로 가는노드가 없으면
			tempNode2 = _adjList[input_v2].createNode(input_v1, 0); //연결노드생성
																	//(u,v),(v,u) 연결
		tempNode1->other = tempNode2;
		tempNode2->other = tempNode1;
	}

	/*cout << "adjList before FF algorithm : " << endl;
	for (int i = 0; i <= V_num + 1; i++)
	{
		_adjList[i].printAdjList(i);
	}
	cout << endl;*/

	int maxFlow = 0; //maxFlow값 초기화
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


