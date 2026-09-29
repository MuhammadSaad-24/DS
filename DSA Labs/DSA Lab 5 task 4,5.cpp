#include<iostream>
using namespace std;

template <typename t>
class Queue
{
private:
	class Node
	{
	public:
		t Data;
		Node* Next;
		Node(const t& data, Node* n = 0)
		{
			Data = data;
			Next = n;
		}
		~Node()
		{
			Next = nullptr;
		}
	};
	Node* Head;
	Node* Tail;
	int size;
public:
	Queue()
	{
		Head = nullptr;
		Tail = nullptr;
		size = 0;
	}
	int GetSize() const { return size; }
	void Enqueue(t data)
	{
		if (Head)
		{
			Tail->Next = new Node(data);
			Tail = Tail->Next;
		}
		else
		{
			Head = Tail = new Node(data);
		}
		size++;
	}
	bool Dequeue(t& val)
	{
		if (Head)
		{
			Node* temp = Head;
			Head = Head->Next;

			if (!Head)
				Tail = nullptr;
			
			val = temp->Data;
			delete temp;
			size--;
			return true;
		}
		
		cout << "Error:: Empty Stack\n";
		val = 0;
		return false;
	}
	void Print()
	{		
		Node* temp = Head;
		cout << "Queue::";
		while (temp != nullptr)
		{
			cout << temp->Data;
			temp = temp->Next;
		}
		cout << endl;
	}
	bool IsEmpty() { return Head == nullptr; }
	t& Front() 
	{ 
		if (Head)
			return Head->Data;
		else
		{
			cout << "Error::Empty Queue\n";
			return 0;
		}
	}

	~Queue()
	{
		while (Head != nullptr)
		{
			Node* temp = Head;
			Head = Head->Next;
			delete temp;
		}

		Head = Tail = nullptr;
	}
};

template <typename t>
void ChangeSequence(Queue<t>& queue)
{
	if (queue.GetSize() % 2 != 0)
	{
		cout << "Error:: Not Even Queue\n";
		return;
	}
		
	int i = 1;
	Queue<t> firsthalf;
	t data;
	int Size = queue.GetSize();
	while (i <= Size / 2)
	{
		queue.Dequeue(data);
		firsthalf.Enqueue(data);
		i++;
	}

	while (firsthalf.GetSize() != 0)
	{
		firsthalf.Dequeue(data);
		queue.Enqueue(data);
		queue.Dequeue(data);
		queue.Enqueue(data);
	}

}
int main()
{
	Queue<int> q1;
	int val;

	q1.Enqueue(4);
	if (q1.Dequeue(val))
		cout << "Dequeue :: " << val << endl;

	q1.Enqueue(3);
	q1.Enqueue(2);
	q1.Enqueue(5);
	q1.Enqueue(6);
	q1.Enqueue(7);
	q1.Enqueue(9);
	q1.Enqueue(8);
	q1.Enqueue(4);
	cout << "Before Changing::\n";
	q1.Print();
	ChangeSequence(q1);
	cout << "After Changing::\n";
	q1.Print();
}