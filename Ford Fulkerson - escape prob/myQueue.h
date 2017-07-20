#pragma once

typedef struct queue_list {
	struct QueueNode *front;
	struct QueueNode *rear;
} queueList;

typedef struct QueueNode
{
	int vertex;
	struct QueueNode * next;
}QueueNode;

class MyQueue {
private:
	queueList * root;
public:
	MyQueue()
	{
		root = new queueList();
		root->front = NULL;
		root->rear = NULL;
	}
	void _enqueue(int input)
	{
		QueueNode * newNode = new QueueNode();
		newNode->vertex = input;
		newNode->next = NULL;
		if (root->front == NULL && root->rear == NULL)
		{
			root->front = root->rear = newNode;
			return;
		}
		root->rear->next = newNode;
		root->rear = newNode;
	}
	void _dequeue()
	{
		QueueNode * dequeue_node = root->front;

		if (root->front == NULL && root->rear == NULL)
		{
			cout << "Queue is Empty" << endl;
			return;
		}
		int output = root->front->vertex;

		if (root->front->next == NULL) //마지막 한개노드가 dequeue 될때
		{
			root->front = NULL;
			root->rear = NULL;
			delete dequeue_node;
			return;
		}
		root->front = dequeue_node->next;
		delete dequeue_node;
	}
	int getFront()
	{
		return root->front->vertex;
	}
	bool isEmpty()
	{
		if (root->front == NULL && root->rear == NULL)
			return true;
		return false;
	}
};


