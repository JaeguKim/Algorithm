#include <iostream>
#include <fstream>
#define SIZE 500

using namespace std;

typedef struct __list {
	struct Node *cur;
	struct Node *head;
	struct Node *tail;
} linkedList;

typedef struct Node
{
	int vertex;
	int edge;
	struct Node * next;
}Node;

int d[500];
int p[500];
int flag[500];


int num_V;
int num_E;
int count = 0;

struct Node H[SIZE];
struct Node backUp[SIZE];
int heapSize;
struct Node S[SIZE];

linkedList *L;

void siftdown(int i, int heap_size)
{
	struct Node siftkey;
	int parent;
	bool found;
	int smallerChild;

	siftkey = H[i];	parent = i;	found = false;
	while ((2 * parent <= heap_size) && (found == false))
	{
		if ((2 * parent < heap_size) && (H[2 * parent].edge > H[2 * parent + 1].edge))
			smallerChild = 2 * parent + 1;
		else  smallerChild = 2 * parent;
		if (siftkey.edge > H[smallerChild].edge)
		{
			H[parent] = H[smallerChild];
			parent = smallerChild;
		}
		else found = true;
	}
	H[parent] = siftkey;
}

void makeheap(int n)
{
	int heapsize = n;
	for (int i = n / 2; i >= 1; i--)
		siftdown(i, n);
}

struct Node root()  // ЅШ(log n) 
{                         // delete-max //
	struct Node keyout = H[1];
	struct Node root;
	H[1] = H[heapSize];
	heapSize = heapSize - 1;
	siftdown(1, heapSize);
	root = keyout;

	return root;
}

void insertHeap(struct Node input)
{
	heapSize = heapSize + 1;
	H[heapSize] = input;
	int i = heapSize;

	while (i>1 && H[i / 2].edge > input.edge){
		
		H[i] = H[i / 2];

		i = i / 2;
	}
	H[i] = input;
}
void removekeys(int n)
{
	for (int i = 1; i <= n; i++)
		S[i] = root();  //heapsort
}

void heapsort(int n)
{
	makeheap(n);
	removekeys(n);
}

void createNode(linkedList *L, int vertex, int edge) {
	Node *newNode = (Node *)malloc(sizeof(Node));
	newNode->vertex = vertex;
	newNode->edge = edge;
	newNode->next = NULL;
	if (L->head == NULL && L->tail == NULL)
		L->head = L->tail = newNode;
	else {
		L->tail->next = newNode;
		L->tail = newNode;
	}
}

Node inputNode[500];
int inputNum = 0;

void PRIM(int n)
{
	for (int u = 1; u <= num_V; u++)
	{ d[u] = 99999999; flag[u] = 0; }
	
	d[1] = 0;
	p[1] = -1;
	
	inputNode[inputNum].vertex = 1;
	inputNode[inputNum].edge = 0;
	insertHeap(inputNode[inputNum++]);
	
	/*
	struct Node * input = (Node *)malloc(sizeof(Node));
	input->vertex = 1;
	input->edge = 0;
*/
	
	//INSERT(PQ, <r, d[r]>);
	while(heapSize != 0)
	{
		if (count == n-1)
			break;

		struct Node u = root();

		if (flag[u.vertex] == 0)
		{
			for (Node * temp = L[u.vertex].head; temp != NULL; temp = temp->next)
			{
				if (flag[temp->vertex] == 0 && temp->edge < d[temp->vertex])
				{
					p[temp->vertex] = u.vertex;
					d[temp->vertex] = temp->edge;
					inputNode[inputNum].vertex = temp->vertex;
					inputNode[inputNum].edge = d[temp->vertex];
					insertHeap(inputNode[inputNum++]);	
				}
			}
			flag[u.vertex] = 1;
			count++;
			for (int i = 1; i<=heapSize; i++)
			{
				cout << H[i].edge << " ";
			}
			cout << endl;
		}
	}
}


int main(void)
{
	ifstream inFile("input.txt");
	inFile >> num_V;
	inFile >> num_E;

	L = (linkedList *)malloc(sizeof(linkedList)*(num_V + 1));

	for (int i = 1; i <= num_V; i++)
	{
		L[i].cur = NULL;
		L[i].head = NULL;
		L[i].tail = NULL;
	}

	int temp_V1, temp_V2, tempEdge;

	for (int i = 0; i< num_E; i++)
	{
		inFile >> temp_V1;
		inFile >> temp_V2;
		inFile >> tempEdge;

		createNode(&L[temp_V1], temp_V2, tempEdge);
		createNode(&L[temp_V2], temp_V1, tempEdge);
	}

	PRIM(num_V);

	cout << "nearest : ";
	int sum = 0;
	for (int i = 2; i<= num_V;i++)
	{
		cout << p[i] << " ";
	}
	cout << endl;

	for (int i = 1; i<= num_V;i++)
	{
		sum += d[i];
	}
	cout << "weighted Че: " << " " << sum  << endl;

	for (int i = 1; i<= num_V;i++)
	{
		cout << p[i] << " ";
	}
	cout << endl;
}
