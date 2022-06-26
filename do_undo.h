#include <string>
#pragma once

using namespace std;

class Stack
{
public:
	Stack();
	~Stack();

	int GetSize() { return Size; }
	void clear();
	void push_back(string text);
	string pop_last();
	string& operator[](const int index);

private:
	class Node
	{
	public:
		Node *pNext;
		string data;
		Node(string data = string(), Node* pNext = nullptr)
		{
			this->data = data;
			this->pNext = pNext;
		}

	};
	int Size;
	Node *head;
};