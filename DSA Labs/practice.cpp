#include <iostream>

using namespace std;

template <typename Type> 
class Stack
{
private:
    class Node;
    class ListIterator;
    Node *Head;
    Node *Tail;
    int size;

public:
    typedef ListIterator Iterator;
    bool IsEmpty()
    {
        return Head == nullptr;
    }
    int GetSize() const
    {
        return size;
    }
    void Clear()
    {
        ListIterator it = Head;
    }
    void Push(const Type&);
    Type ReturnTop();
    Type Pop();
    ListIterator Begin() const;
};

template <typename Type> 
class Stack<Type>::Node
{
public:
   Type Data;
   Node *Next;
   Node *Previous;
   Node(const Type &, Node * = 0, Node * = 0);
   ~Node();
};

template <typename Type> 
Stack<Type>::Node::Node(const Type &d, Node *n)
{
    Data = d;
    Next = n;
}

template <typename Type> 
Stack<Type>::Node::~Node()
{
    Next = nullptr;
    Previous = nullptr;
}

template <typename Type> 
class Stack<Type>::ListIterator
{
private:
    Node* Iptr;
public:
    friend class Stack;
    ListIterator();
    ListIterator(Node*);
    ListIterator operator++();
    ListIterator operator++(int);
    bool operator!() const;
    bool operator!=(const ListIterator&) const;
    bool operator==(const ListIterator&) const;
    bool operator<(const ListIterator&) const;
    bool operator>(const ListIterator&) const;
    bool operator<(const Type&) const;
    bool operator>(const Type&) const;
    template<typename T>
    friend bool operator>(const T&,const ListIterator&);
    template<typename T>
    friend bool operator<(const T&,const ListIterator&);
    Type& operator*();
    Iterator operator=(const ListIterator&);
    ~ListIterator();
};

template <typename Type> 
Stack<Type>::ListIterator::ListIterator()
{
    Iptr = nullptr;
}

template <typename Type> 
Stack<Type>::ListIterator::ListIterator(Node* other)
{
    Iptr = other;
}

template <typename Type> 
typename Stack<Type>::ListIterator Stack<Type>::ListIterator::operator++()
{
    Iptr = Iptr->Next;
    return Iptr; 
}


template <typename Type> 
typename Stack<Type>::ListIterator Stack<Type>::ListIterator::operator++(int)
{
    Node* Old = Iptr;
    Iptr = Iptr->Next;
    return Old; 
}

template <typename Type> 
bool Stack<Type>::ListIterator::operator!() const
{
    return Iptr == nullptr;
}

template <typename Type> 
bool Stack<Type>::ListIterator::operator!=(const ListIterator& other) const
{
    return Iptr != other.Iptr;
}

template <typename Type> 
bool Stack<Type>::ListIterator::operator==(const ListIterator& other) const
{
    return Iptr == other.Iptr;
}

template <typename Type> 
bool Stack<Type>::ListIterator::operator<(const ListIterator& other) const
{
    if(Iptr)
        return Iptr->Data < other.Iptr->Data;
}

template <typename Type> 
bool Stack<Type>::ListIterator::operator>(const ListIterator& other) const
{
    if(Iptr)
        return Iptr->Data > other.Iptr->Data;
}

template <typename Type> 
bool Stack<Type>::ListIterator::operator<(const Type& other) const
{
    if(Iptr)
        return Iptr->Data < other;
}

template <typename Type> 
bool Stack<Type>::ListIterator::operator>(const Type& other) const
{
    if(Iptr)
        return Iptr->Data > other;
}

template<typename T>
bool operator>(const T& data,const typename Stack<T>::ListIterator& other)
{
    if(other.Iptr)
        return data > other.Iptr->Data;
}

template<typename T>
bool operator<(const T& data,const typename Stack<T>::ListIterator& other)
{
    if(other.Iptr)
        return data < other.Iptr->Data;
}

template <typename Type> 
typename Stack<Type>::Iterator Stack<Type>::ListIterator::operator=(const ListIterator& other) 
{
    Iptr = other.Iptr;
    return *this;
}

template <typename Type> 
Type& Stack<Type>::ListIterator::operator*()
{
    return Iptr->Data;   
}

template <typename Type> 
Stack<Type>::ListIterator::~ListIterator()
{
    Iptr = nullptr; 
}


int main()
{
    Stack<int> l1;
    
    return 0;
}