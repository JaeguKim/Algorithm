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
	void createNode(int vertex) {
		Node *newNode = (Node *)malloc(sizeof(Node));
		newNode->vertex = vertex;
		newNode->next = NULL;
		if (root->head == NULL && root->tail == NULL)
			root->head = root->tail = newNode;
		else {
			root->tail->next = newNode;
			root->tail = newNode;
		}
	}
	void createPreNode(int vertex) {
		Node *newNode = new Node();
		newNode->vertex = vertex;
		newNode->next = NULL;
		if (root->head == NULL && root->tail == NULL)
			root->head = root->tail = newNode;
		else {
			newNode->next = root->head;
			root->head = newNode;
		}
	}
	void printAdjList(int startV) {
		cout << startV << ": ";
		for (Node * temp = root->head; temp != NULL; temp = temp->next)
		{
			cout << "(" << startV << "," << temp->vertex << ")" << " ";
		}
		cout << endl;
	}
};