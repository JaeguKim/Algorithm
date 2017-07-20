#pragma once
#include <iostream>

using namespace std;

typedef struct __list {
	struct Node *head;
	struct Node *tail;
} linkedList;

typedef struct Node
{
	int vertex;
	int capacity;
	int flow;
	struct Node * other;
	struct Node * next;
}Node;

class LinkedList {
private:
	__list * root;
public:
	LinkedList() {
		root = new __list();
		root->head = NULL;
		root->tail = NULL;
	}

	__list * getRoot() {
		return root;
	}

	Node * createNode(int vertex, int capacity) {
		Node *newNode = new Node();
		newNode->vertex = vertex;
		newNode->capacity = capacity;
		newNode->flow = 0;
		newNode->next = NULL;
		if (root->head == NULL && root->tail == NULL)
		{
			root->head = root->tail = newNode;
			return newNode;
		}

		//먼저 기존의 edge가 있는지 보기
		for (Node * temp = root->head; temp != NULL; temp = temp->next)
		{
			if (temp->vertex == vertex) //기존에 edge가 있으면 기존노드에 추가
			{
				temp->capacity = capacity;
				return temp;
			}
		}
		//기존의 edge가 없으면
		root->tail->next = newNode;
		root->tail = newNode;
		return newNode;
	}

	Node * findNode(int vertex) {
		for (Node * temp = root->head; temp != NULL; temp = temp->next)
		{
			if (temp->vertex == vertex)
				return temp;
		}
		return NULL;
	}

	void printAdjList(int startV) {
		cout << startV << ": ";
		for (Node * temp = root->head; temp != NULL; temp = temp->next)
		{
			cout << "(" << startV << "," << temp->vertex << "," << temp->capacity << "," << temp->flow << ")" << " ";
		}
		cout << endl;
	}
};
