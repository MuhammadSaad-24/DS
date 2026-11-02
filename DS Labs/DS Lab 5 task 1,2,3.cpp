#include<iostream>
using namespace std;

template <typename Type>
class Stack
{
private:
	class Node
	{
	public:
		Type Data;
		Node* Next;
		Node(const Type& data, Node* n = 0)
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
public:
	Stack()
	{
		Head = nullptr;
	}
	void Push(Type data)
	{
		Node* NewNode = new Node(data, Head);
		Head = NewNode;
	}
	bool Pop()
	{
		if (Head)
		{
			Node* temp = Head;
			Head = Head->Next;
			delete temp;
			return true;
		}
		else 
			return false;
	}
	void Print()
	{
		Node* temp = Head;
		cout << "Stack:: ";
		while (temp != nullptr)
		{
			cout << temp->Data;
			temp = temp->Next;
		}
		cout << endl;
	}
	bool Top(Type& val)
	{
		if (Head)
		{
			val = Head->Data;
			return true;
		}
		cout << "Error::Empty Stack\n";
		return false;
	}
	bool IsEmpty()
	{
		return Head == nullptr;
	}
	~Stack()
	{
		while (Head != nullptr)
		{
			Node* temp = Head;
			Head = Head->Next;
			delete temp;
		}
	}
};

bool CheckBalance(string data)
{
	Stack<char> stack;
	int i = 0;
	while (data[i] != '\0')
	{
		if (data[i] == '[' || data[i] == '{' || data[i] == '(')
		{
			stack.Push(data[i]);
		}
		else if (data[i] == ']' || data[i] == '}' || data[i] == ')')
		{
			char top;
			stack.Top(top);
			if (data[i] - 1== top || data[i] - 2 == top)
			{
				stack.Pop();
			}
		}
		i++;
	}

	if (stack.IsEmpty())
		return true;
	else
		return false;

}

void PostFix(string data, Stack<int>& st)
{
	int i = 0;
	while (data[i] != '\0')
	{
		if (isdigit(data[i]))
			st.Push(data[i] - '0');
		
		if (data[i] == '+' || data[i] == '-' || data[i] == '*' || data[i] == '/')
		{
			if (st.IsEmpty())
			{
				cout << "No operand is Present for Binary Operation\n";
				return;
			}

			int a, b;
			st.Top(a);
			st.Pop();

			if (st.IsEmpty())
			{
				cout << "a Number is not enough for Binary Operation\n";
				return;
			}

			st.Top(b);
			st.Pop();

			switch (data[i])
			{
			case '+':
				a += b;
				break;
			case '-':
				 a = b - a;
				break;
			case '*':
				a *= b;
				break;
			case '/':
				if (a == 0)
				{
					cout << "Error::Division with Zero\n";
					return;
				}
				a = b/a ;
				break;
			default:
				break;
			}

			st.Push(a);
		}
		i++;
	}

	st.Print();
}
int main()
{
	string data = "512+4*+3-";

	if (CheckBalance(data))
		cout << "Balanced\n";
	else
		cout << "Not Balanced\n";

	Stack<int> st;
	PostFix(data, st);
}