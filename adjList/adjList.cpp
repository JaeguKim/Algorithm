#include <iostream>
#include <fstream>

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


void createNode(linkedList *L, int vertex, int edge) {
    Node *newNode = (Node *)malloc(sizeof(Node));
	newNode->vertex = vertex;
	newNode->edge = edge;
    newNode->next = NULL;
    if(L->head == NULL && L->tail == NULL)
        L->head = L->tail = newNode;    
    else {
        L->tail->next = newNode;
        L->tail = newNode;
    }
}

int num_V;
int num_E;

linkedList ** aryPtr;

int main(void)
{
	ifstream inFile("input.txt");
	inFile >> num_V;
	inFile >> num_E;

	linkedList *L = (linkedList *)malloc(sizeof(linkedList)*(num_V+1));

	for (int i = 1; i<= num_V; i++)
	{
		L[i].cur = NULL;
		L[i].head = NULL;
		L[i].tail = NULL;
	}

	int temp_V1, temp_V2,tempEdge;

	for (int i = 0; i< num_E; i++)
	{
		inFile >> temp_V1;
		inFile >> temp_V2;
		inFile >> tempEdge;
		
		createNode(&L[temp_V1],temp_V2,tempEdge);
		createNode(&L[temp_V2],temp_V1,tempEdge);
	}

	Node * printCur;

	for (int i = 1; i <= num_V; i++)
	{
		cout << i << " : ";
		printCur = L[i].head;
		while (printCur != NULL)
		{
			cout << "(" << printCur->vertex << ", " << printCur->edge << ")" << " ";
			printCur = printCur->next;
		}
		cout << endl;
	}
}