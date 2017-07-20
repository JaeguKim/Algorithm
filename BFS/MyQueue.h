#pragma once
#define MAXSIZE 1000

class MyQueue{
private:
	 int myQueue[MAXSIZE];
	 int front;
	 int rear;
	 int Q_size;
public:
	MyQueue()
	{
		front = 0;
		rear = 0;
		Q_size = 0;
	}
	void _enqueue(int input)
	{
		myQueue[rear] = input;
		rear++;
		Q_size++;
	}
	int _dequeue()
	{
		int output = myQueue[front];
		front++;
		Q_size--;
		return output;
	}
	int getFront()
	{
		return myQueue[front];
	}
	bool isEmpty()
	{
		if (Q_size == 0)
			return true;
		return false;
	}
};


