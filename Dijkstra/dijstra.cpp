//
//  dijstra.cpp
//  algo
//
//  Created by 김재구 on 2017. 7. 16..
//  Copyright © 2017년 김재구. All rights reserved.
//

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


struct Node H[SIZE];
struct Node backUp[SIZE];
int heapSize;

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

struct Node root()  // Θ(log n)
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
int cnt = 0;

void dijstra(int n)
{
    for (int u = 1; u <= num_V; u++)
    { d[u] = 99999999; flag[u] = 0; }
    
    d[1] = 0;
    p[1] = -1;
    
    inputNode[inputNum].vertex = 1;
    inputNode[inputNum].edge = 0;
    insertHeap(inputNode[inputNum++]);
    
    //INSERT(PQ, <r, d[r]>);
    while(heapSize != 0)
    {
        struct Node u = root();
        
        if (flag[u.vertex] == 0)
        {
            for (Node * temp = L[u.vertex].head; temp != NULL; temp = temp->next)
            {
                if (flag[temp->vertex] == 0 && d[temp->vertex]> temp->edge + d[u.vertex])
                {
                    p[temp->vertex] = u.vertex;
                    d[temp->vertex] = temp->edge + d[u.vertex];
                    
                    inputNode[inputNum].vertex = temp->vertex;
                    inputNode[inputNum].edge = d[temp->vertex];
                    insertHeap(inputNode[inputNum++]);
                }
            }
            flag[u.vertex] = 1;
            cnt++;
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
    
    cout << endl;
    
    dijstra(num_V);
    
    int sum = 0;
    for (int i = 1; i<= num_V;i++)
    {
        cout << d[i] << " ";
    }
    cout << endl;
    
    for (int i = 1; i<= num_V;i++)
    {
        cout << p[i] << " ";
    }
    cout << endl;
}

