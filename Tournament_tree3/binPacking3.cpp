#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

void init(int tree[], int player[], int bin_num, int bin_capacity); //tree,player �ʱ�ȭ
void insertToBin(int player[], int tree[], int bin_num, int &search_idx, int insert_num); //bin�� ����
void update(int player[], int tree[], int bin_num, int &search_idx); //tree�� update
void printTreePlayer(int tree[], int plyaer[], int bin_num); //tree,flare ���

double Log2(double n) //���� 2�� �αװ� ���ϱ�
{
	// log(n)/log(2) is log2.  
	return log(n) / log(double(2));
}

int main(void)
{
	ifstream fin;
	int bin_num, n, bin_capacity;
	int * tree;
	int * player;

	fin.open("input4.txt");
	fin >> bin_num >> n >> bin_capacity;

	tree = new int[bin_num]; //tree 1~bin_num-1 ���� ���� �Ҵ�
	player = new int[bin_num + 1]; //player 1~bin_num ���� ���� �Ҵ�

	init(tree, player, bin_num, bin_capacity); //tree, flare �ʱ�ȭ

	int insert_num;
	int search_idx;

	printTreePlayer(tree, player, bin_num);

	for (int i = 0; i <n; i++) //input ���� ��ŭ �ݺ�
	{
		fin >> insert_num;
		search_idx = 1;
		insertToBin(player, tree, bin_num, search_idx, insert_num); //insert_num�� Bin�� �ֱ�(update���� ����)
		printTreePlayer(tree, player, bin_num); //tree, flare �迭 ���
	}

}

void init(int tree[], int player[], int bin_num, int bin_capacity)
{
	int p;
	int s = pow(2, ceil(Log2(double(bin_num)) - 1.0));
	int offset = 2 * s - 1;
	int LowExt = 2 * ((bin_num - 1) - (s - 1));

	//player �ʱ�ȭ
	for (int i = 1; i <= bin_num; i++)
	{
		player[i] = bin_capacity;
	}

	//tree �ʱ�ȭ
	if (bin_num % 2 == 0) //n�� ¦��
	{
		for (int k = 1; k <= bin_num; k = k + 2) {
			if (k <= LowExt)
				p = (k + offset) / 2;
			else
				p = (k - LowExt + bin_num - 1) / 2;
			tree[p] = k;
		}
	}
	else { // n �� Ȧ��
		for (int k = 1; k <= LowExt; k = k + 2) {
			p = (k + offset) / 2;
			tree[p] = k;
		}
		for (int k = LowExt + 2; k <= bin_num; k = k + 2)
		{
			p = (k - LowExt + bin_num - 1) / 2;
			tree[p] = k;
		}
	}

	for (int k = (bin_num - 1) / 2; k > 0; k--) //������ tree �ʱ�ȭ
		tree[k] = tree[k * 2];
}

void insertToBin(int player[], int tree[], int bin_num, int &search_idx, int insert_num)
{
	int s = pow(2, (ceil(Log2(double(bin_num)) - 1.0)));
	int offset = 2 * s - 1;
	int LowExt = 2 * ((bin_num - 1) - (s - 1));
	int start_bin_idx = (2 * s - 1 + LowExt) / 2 + 1; //leaf node�� ��Ÿ���� �����ϴ� index��ȣ

	while (1)
	{
		if (player[tree[search_idx]] >= insert_num) //���� ����Ű�� ��ġ���ִ� bin�� �뷮�� insert_num���� ũ�ų� ������
		{
			search_idx *= 2; //child��� �� �̵�
			if (search_idx >= start_bin_idx  && search_idx <= (2 * s - 1) + LowExt)//leaf ��忡 �����ϸ�
			{
				if (search_idx <= offset) //index��ȣ�� offset ���� �۰ų� ������
				{
					if (player[search_idx+1 - start_bin_idx + LowExt] >= insert_num) //���ʳ���� bin�� �뷮�� insert_num ���� ũ�ų� ������
						player[search_idx+1 - start_bin_idx + LowExt] = player[search_idx+1 - start_bin_idx + LowExt] - insert_num; //���ʳ�忡 �ش��ϴ� bin�� �뷮�� ����
					else //���ʳ���� bin �� �뷮�� insert_num ���� ������
					{
						player[search_idx+1- start_bin_idx + LowExt + 1] = player[search_idx+1 - start_bin_idx + LowExt + 1] - insert_num; //������ ��忡 �ش��ϴ� bin�� �뷮�� ����
						search_idx += 1; //������ ���� index �̵�
					}
				}
				else //offset ���� ũ��
				{
					if (player[search_idx - offset] >= insert_num) //���ʳ���� bin�� �뷮�� insert_num ���� ũ�ų� ������
						player[search_idx - offset] = player[search_idx - offset] - insert_num; //���ʳ�忡 �ش��ϴ� bin�� �뷮�� ����
					else //���ʳ���� bin �� �뷮�� insert_num ���� ������
					{
						player[search_idx - offset + 1] = player[search_idx - offset + 1] - insert_num; //������ ��忡 �ش��ϴ� bin�� �뷮�� ����
						search_idx += 1; //������ ���� index �̵�
					}
				}
				//tree�� ������Ʈ
				update(player, tree, bin_num, search_idx);
				break; //update�� �Ϸ�Ǿ����� while���� Ż��
			}
		}
		else //���� ����Ű�� ��ġ�� �ִ� bin�� �뷮�� insert_num���� ������
		{
			search_idx += 1; //�������� �̵�
			if (search_idx == start_bin_idx)
			{
				player[search_idx - start_bin_idx + LowExt + 1] = player[search_idx - start_bin_idx + LowExt + 1] - insert_num;
				update(player, tree, bin_num, search_idx);
				break; //update�� �Ϸ�Ǿ����� while���� Ż��
			}
		}

	}
}

void update(int player[], int tree[], int bin_num, int &search_idx)
{
	int s = pow(2, (ceil(Log2(double(bin_num)) - 1.0)));
	int offset = 2 * s - 1;
	int LowExt = 2 * ((bin_num - 1) - (s - 1));
	int start_bin_idx = (2 * s - 1 + LowExt) / 2 + 1;

	while (search_idx != 1) //root��忡 �����Ҷ����� �ݺ�
	{
		if (search_idx % 2 == 0) //index��ȣ�� ¦���̸�
		{
			if (search_idx >= start_bin_idx) //leaf node�̸鼭
			{
				if (search_idx > offset) //index��ȣ�� offset(2s-1)���� Ŭ��
				{
					if (player[search_idx - offset] >= player[search_idx - offset + 1]) //���ʳ���� �뷮�� ũ�ų� ������
					{
						tree[search_idx / 2] = search_idx - offset; //�뷮�� �� ū ���� ��ȣ�� ����
					}
					else //�����ʳ���� �뷮�� �� ũ��
					{
						tree[search_idx / 2] = search_idx - offset + 1;
					}
				}
				else //index��ȣ�� offset(2s-1)���� �۰ų�������
				{
					if (player[search_idx +1 - start_bin_idx + LowExt] >= player[search_idx+1 - start_bin_idx + LowExt + 1]) //���ʳ���� �뷮�� ũ�ų� ������
					{
						tree[search_idx / 2] = search_idx+1 - start_bin_idx + LowExt; //�뷮�� �� ū ���� ��ȣ�� ����
					}
					else //�����ʳ���� �뷮�� �� ũ��
					{
						tree[search_idx / 2] = search_idx+1 - start_bin_idx + LowExt + 1;
					}
				}
			}
			else //start_bin_index���� ������
			{
				if (search_idx == start_bin_idx - 1) //start_bin_idx-1 �� ��쿡��
				{
					if (player[tree[search_idx]] >= player[search_idx + 2 - start_bin_idx + LowExt]) //���ʳ���� �뷮�� ũ�ų� ������
					{
						tree[search_idx / 2] = tree[search_idx];
					}
					else //�����ʳ���ǿ뷮�� �� ũ��
					{
						tree[search_idx / 2] = search_idx + 2 - start_bin_idx + LowExt;
					}
				}
				else
				{
					if (player[tree[search_idx]] >= player[tree[search_idx + 1]]) //���ʳ���� �뷮�� ũ�ų� ������
					{
						tree[search_idx / 2] = tree[search_idx];
					}
					else //�����ʳ���� �뷮�� �� ũ��
					{
						tree[search_idx / 2] = tree[search_idx + 1];
					}
				}
			}
		}
		else //index��ȣ�� Ȧ���̸�
		{
			if (search_idx >= start_bin_idx) //leaf node�̸鼭
			{
				if (search_idx > offset) //index��ȣ�� offset���� Ŭ��
				{
					if (player[search_idx - offset - 1] >= player[search_idx - offset]) //���� ��尡 �����ʳ�庸�� ũ�ų� ������
					{
						tree[search_idx / 2] = search_idx - offset - 1;
					}
					else //������ ��尡 �� Ŭ��
					{
						tree[search_idx / 2] = search_idx - offset;
					}
				}
				else //offset���� �۰ų�������
				{
					if (search_idx == start_bin_idx) //start_bin_idx �� ��쿡��
					{
						if (player[tree[search_idx - start_bin_idx + LowExt]] >= player[search_idx + 1 - start_bin_idx + LowExt]) //���ʳ���� �뷮�� ũ�ų� ������
						{
							tree[search_idx / 2] = tree[search_idx - 1 - start_bin_idx + LowExt];
						}
						else //������ ��尡 �� Ŭ��
						{
							tree[search_idx / 2] = search_idx + 1 - start_bin_idx + LowExt;

						}
					}
					else
					{
						if (player[search_idx+1 - start_bin_idx + LowExt - 1] >= player[search_idx+1 - start_bin_idx + LowExt]) //���� ��尡 �����ʳ�庸�� ũ�ų� ������
						{
							tree[search_idx / 2] = search_idx+1 - start_bin_idx + LowExt - 1;
						}
						else //������ ��尡 ��Ŭ��
						{
							tree[search_idx / 2] = search_idx+1 - start_bin_idx + LowExt;
						}
					}
				}
			}
			else //search_idx�� start_bin_idx���� ������
			{
				if (player[tree[search_idx - 1]] >= player[tree[search_idx]]) //���ʳ���� �뷮�� ũ�ų� ������
				{
					tree[search_idx / 2] = tree[search_idx - 1];
				}
				else
				{
					tree[search_idx / 2] = tree[search_idx];
				}
			}
		}
		search_idx /= 2; //�θ���� �̵�
	}
}

void printTreePlayer(int tree[], int player[], int bin_num)
{
	//tree ���
	cout << "tree : ";
	for (int i = 1; i <= bin_num - 1; i++)
	{
		cout << tree[i] << " ";
	}
	cout << endl;
	//flare ���
	cout << "player : ";

	for (int i = 1; i <= bin_num; i++)
	{
		cout << player[i] << " ";
	}
	cout << endl << endl;;
}
