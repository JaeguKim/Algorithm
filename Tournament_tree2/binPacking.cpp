#include <iostream>
#include <fstream>

using namespace std;

void init(int tree[], int flare[], int bin_num, int bin_capacity); //tree,flare 초기화
void insertToBin(int flare[], int tree[], int bin_num, int &search_idx, int insert_num); //bin에 삽입
void update(int flare[], int tree[], int bin_num, int &search_idx); //tree를 update
void printTreeFlare(int tree[], int flare[], int bin_num); //tree,flare 출력

int main(void)
{
	ifstream fin;
	int bin_num, n, bin_capacity;
	int * tree;
	int * flare;

	fin.open("input2.txt");
	fin >> bin_num >> n >> bin_capacity;

	tree = new int[bin_num]; //tree 1~bin_num-1 까지 공간 할당
	flare = new int[bin_num + 1]; //flare 1~bin_num 까지 공간 할당

	init(tree, flare, bin_num,bin_capacity); //tree, flare 초기화

	int insert_num;
	int search_idx;

	for (int i = 0; i <n; i++) //input 개수 만큼 반복
	{
 		fin >> insert_num;
		search_idx = 1;
		insertToBin(flare, tree, bin_num, search_idx, insert_num); //insert_num을 Bin에 넣기(update과정 포함)
		printTreeFlare(tree, flare, bin_num); //tree, flare 배열 출력
	}

}

void init(int tree[], int flare[], int bin_num, int bin_capacity)
{
	int idx_num = 1;
	//초기화
	for (int i = 1; i <= bin_num; i++)
	{
		flare[i] = bin_capacity;
	}

	//맨 밑에 줄 초기화
	for (int i = bin_num - bin_num / 2; i <= bin_num - 1; i++)
	{
		tree[i] = idx_num;
		idx_num = idx_num + 2;
	}

	//나머지 위에 줄 초기화
	for (int i = bin_num - bin_num / 2 - 1; i >= 1; i--)
	{
		tree[i] = tree[2 * i];
	}
}

void insertToBin(int flare[], int tree[], int bin_num, int &search_idx, int insert_num)
{
	while (1)
	{
		if (flare[tree[search_idx]] >= insert_num) //현재 가리키는 위치에있는 bin의 용량이 insert_num보다 크거나 같으면
		{
			search_idx *= 2; //child노드 로 이동
			if (search_idx >= bin_num && search_idx <= 2 * bin_num - 1) //leaf 노드에 도달하면
			{
				if (flare[search_idx - bin_num + 1] >= insert_num) //bin의 용량이 insert_num 보다 크거나 같으면
					flare[search_idx - bin_num + 1] = flare[search_idx - bin_num + 1] - insert_num;
				else //bin 의 용량이 insert_num 보다 작으면
				{
					flare[search_idx - bin_num + 2] = flare[search_idx - bin_num + 2] - insert_num;
					search_idx+=1;
				}
				//tree를 업데이트
				update(flare, tree, bin_num, search_idx);
			}
		}
		else //현재 가리키는 위치에 있는 bin의 용량이 insert_num보다 작으면
		{
			search_idx += 1; //인접노드로 이동
		}

		///while 종료조건///
		if (search_idx == 1) //update가 완료되어 idx가 1로 setting 되면 break
			break;
	}
}

void update(int flare[], int tree[], int bin_num, int &search_idx)
{
	while (search_idx != 1) //root노드에 도달할때까지 반복
	{
		if (search_idx % 2 == 0) //index번호가 짝수이면
		{
			if (search_idx > bin_num - 1) //index번호가 tree배열 바운더리를 넘어서면
			{
				if (flare[search_idx - bin_num + 1] >= flare[search_idx - bin_num + 2]) //왼쪽노드의 용량이 크거나 같으면
				{
					tree[search_idx / 2] = search_idx - bin_num + 1; //용량이 더 큰 빈의 번호를 저장
				}
				else
				{
					tree[search_idx / 2] = search_idx - bin_num + 2;
				}
			}
			else //index번호가 tree배열 바운더리를 넘어서지않으면
			{
				if (flare[tree[search_idx]] >= flare[tree[search_idx + 1]]) //왼쪽노드의 용량이 크거나 같으면
				{
					tree[search_idx / 2] = tree[search_idx]; //용량이 더 큰 빈의 번호를 저장
				}
				else
				{
					tree[search_idx / 2] = tree[search_idx + 1];
				}
			}
		}
		else //index번호가 홀수이면
		{
			if (search_idx > bin_num - 1) //index번호가 tree배열 바운더리를 넘어서면
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
		search_idx /= 2; //부모노드로 이동
	}
}

void printTreeFlare(int tree[], int flare[], int bin_num)
{
	//tree 출력
	cout << "tree : ";
	for (int i = 1; i <= bin_num - 1; i++)
	{
		cout << tree[i] << " ";
	}
	cout << endl;
	//flare 출력
	cout << "flare : ";

	for (int i = 1; i <= bin_num; i++)
	{
		cout << flare[i] << " ";
	}
	cout << endl << endl;;
}
