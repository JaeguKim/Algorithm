#include <iostream>
#include <fstream>

using namespace std;

void init(int tree[], int flare[], int bin_num, int bin_capacity); //tree,flare �ʱ�ȭ
void insertToBin(int flare[], int tree[], int bin_num, int &search_idx, int insert_num); //bin�� ����
void update(int flare[], int tree[], int bin_num, int &search_idx); //tree�� update
void printTreeFlare(int tree[], int flare[], int bin_num); //tree,flare ���

int main(void)
{
	ifstream fin;
	int bin_num, n, bin_capacity;
	int * tree;
	int * flare;

	fin.open("input2.txt");
	fin >> bin_num >> n >> bin_capacity;

	tree = new int[bin_num]; //tree 1~bin_num-1 ���� ���� �Ҵ�
	flare = new int[bin_num + 1]; //flare 1~bin_num ���� ���� �Ҵ�

	init(tree, flare, bin_num,bin_capacity); //tree, flare �ʱ�ȭ

	int insert_num;
	int search_idx;

	for (int i = 0; i <n; i++) //input ���� ��ŭ �ݺ�
	{
 		fin >> insert_num;
		search_idx = 1;
		insertToBin(flare, tree, bin_num, search_idx, insert_num); //insert_num�� Bin�� �ֱ�(update���� ����)
		printTreeFlare(tree, flare, bin_num); //tree, flare �迭 ���
	}

}

void init(int tree[], int flare[], int bin_num, int bin_capacity)
{
	int idx_num = 1;
	//�ʱ�ȭ
	for (int i = 1; i <= bin_num; i++)
	{
		flare[i] = bin_capacity;
	}

	//�� �ؿ� �� �ʱ�ȭ
	for (int i = bin_num - bin_num / 2; i <= bin_num - 1; i++)
	{
		tree[i] = idx_num;
		idx_num = idx_num + 2;
	}

	//������ ���� �� �ʱ�ȭ
	for (int i = bin_num - bin_num / 2 - 1; i >= 1; i--)
	{
		tree[i] = tree[2 * i];
	}
}

void insertToBin(int flare[], int tree[], int bin_num, int &search_idx, int insert_num)
{
	while (1)
	{
		if (flare[tree[search_idx]] >= insert_num) //���� ����Ű�� ��ġ���ִ� bin�� �뷮�� insert_num���� ũ�ų� ������
		{
			search_idx *= 2; //child��� �� �̵�
			if (search_idx >= bin_num && search_idx <= 2 * bin_num - 1) //leaf ��忡 �����ϸ�
			{
				if (flare[search_idx - bin_num + 1] >= insert_num) //bin�� �뷮�� insert_num ���� ũ�ų� ������
					flare[search_idx - bin_num + 1] = flare[search_idx - bin_num + 1] - insert_num;
				else //bin �� �뷮�� insert_num ���� ������
				{
					flare[search_idx - bin_num + 2] = flare[search_idx - bin_num + 2] - insert_num;
					search_idx+=1;
				}
				//tree�� ������Ʈ
				update(flare, tree, bin_num, search_idx);
			}
		}
		else //���� ����Ű�� ��ġ�� �ִ� bin�� �뷮�� insert_num���� ������
		{
			search_idx += 1; //�������� �̵�
		}

		///while ��������///
		if (search_idx == 1) //update�� �Ϸ�Ǿ� idx�� 1�� setting �Ǹ� break
			break;
	}
}

void update(int flare[], int tree[], int bin_num, int &search_idx)
{
	while (search_idx != 1) //root��忡 �����Ҷ����� �ݺ�
	{
		if (search_idx % 2 == 0) //index��ȣ�� ¦���̸�
		{
			if (search_idx > bin_num - 1) //index��ȣ�� tree�迭 �ٿ������ �Ѿ��
			{
				if (flare[search_idx - bin_num + 1] >= flare[search_idx - bin_num + 2]) //���ʳ���� �뷮�� ũ�ų� ������
				{
					tree[search_idx / 2] = search_idx - bin_num + 1; //�뷮�� �� ū ���� ��ȣ�� ����
				}
				else
				{
					tree[search_idx / 2] = search_idx - bin_num + 2;
				}
			}
			else //index��ȣ�� tree�迭 �ٿ������ �Ѿ��������
			{
				if (flare[tree[search_idx]] >= flare[tree[search_idx + 1]]) //���ʳ���� �뷮�� ũ�ų� ������
				{
					tree[search_idx / 2] = tree[search_idx]; //�뷮�� �� ū ���� ��ȣ�� ����
				}
				else
				{
					tree[search_idx / 2] = tree[search_idx + 1];
				}
			}
		}
		else //index��ȣ�� Ȧ���̸�
		{
			if (search_idx > bin_num - 1) //index��ȣ�� tree�迭 �ٿ������ �Ѿ��
			{
				if (flare[search_idx - bin_num] >= flare[search_idx - bin_num + 1])
				{
					tree[search_idx / 2] = search_idx - bin_num;
				}
				else
				{
					tree[search_idx / 2] = search_idx - bin_num + 1;
				}
			}
			else
			{
				if (flare[tree[search_idx - 1]] >= flare[tree[search_idx]])
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

void printTreeFlare(int tree[], int flare[], int bin_num)
{
	//tree ���
	cout << "tree : ";
	for (int i = 1; i <= bin_num - 1; i++)
	{
		cout << tree[i] << " ";
	}
	cout << endl;
	//flare ���
	cout << "flare : ";

	for (int i = 1; i <= bin_num; i++)
	{
		cout << flare[i] << " ";
	}
	cout << endl << endl;;
}
