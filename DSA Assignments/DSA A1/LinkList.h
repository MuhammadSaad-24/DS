#ifndef SINGLE_LINKLIST_H
#define SINGLE_LINKLIST_H

#include <iostream>
using namespace std;

class Program;

template <typename Type>
class LinkList
{
private : 
    class Node;
    class Iterator;
    Node* Head;
    Node* Tail;
    int size;
public:
    typedef Iterator ListIterator;//so it can be recognized globally
    LinkList();
    int Getsize() const;
    Iterator Find(const Type&);
    Iterator SearchByID(const int&);
    void AddtoHead(const Type&);
    void AddtoTail(const Type&);
    void DeleteTail();
    void DeleteAfter(Iterator&);
    Iterator ReturnPrevious(Iterator&);//it will return the previous node
    Iterator ReturnPrevious(const int&);
    void MovetoHead(Iterator&);//this will move the Node to the Head
    template <typename T>
    friend ostream& operator<<(ostream&,T&);
    Iterator Begin() const;
    Iterator End() const;
    ~LinkList();
};

template <typename Type>
class LinkList<Type>::Node
{
public:
    Type Data;
    Node* Next;
    Node(Type&, Node* = 0);
    Node(const Type&, Node* = 0);
    ~Node();
};


template <typename Type>
class LinkList<Type>::Iterator
{
private:
    Node* Iptr;
public:
    friend class LinkList;
    Iterator(Node* = 0);
    Iterator operator++();
    Iterator operator++(int);
    bool operator!() const;
    bool operator!=(const Iterator) const;
    bool operator==(const Iterator) const;
    Type& operator*();
    Iterator operator=(const Iterator&);
    bool IsNext() const;
    bool IsHead() const;
    bool IsTail() const;
    bool IsNull() const;
    Node* GetNode();
    ~Iterator();
};

//---------------------------------------------------------
//                  Node Declearation
//---------------------------------------------------------

template <typename Type>
LinkList<Type>::Node::Node(Type& d ,Node* n)
{
    Data = d;
    Next = n;
}

template <typename Type>
LinkList<Type>::Node::Node(const Type& d, Node* n):Data(d)
{
    Next = n;
}

template <typename Type>
LinkList<Type>::Node::~Node()
{
    Next = nullptr;
}


//---------------------------------------------------------
//                 Iterators Decleration
//---------------------------------------------------------

template <typename Type>
LinkList<Type>::Iterator::Iterator(Node* other)
{
    Iptr = other;
}

template <typename Type>
typename LinkList<Type>::Iterator LinkList<Type>::Iterator::operator++()
{
    Iptr = Iptr->Next;
    return Iptr;
}


template <typename Type>
typename LinkList<Type>::Iterator LinkList<Type>::Iterator::operator++(int)
{
    Node* Old = Iptr;
    Iptr = Iptr->Next;
    return Old;
}

template <typename Type>
bool LinkList<Type>::Iterator::operator!() const
{
    return Iptr == nullptr;
}

template <typename Type>
bool LinkList<Type>::Iterator::operator!=(const Iterator other) const
{
    return Iptr != other.Iptr;
}
template <typename Type>
bool LinkList<Type>::Iterator::operator==(const Iterator other) const
{
    return Iptr == other.Iptr;
}

template <typename Type>
typename LinkList<Type>::Iterator LinkList<Type>::Iterator::operator=(const Iterator& other)
{
    Iptr = other.Iptr;
    return *this;
}

template <typename Type>
Type& LinkList<Type>::Iterator::operator*()
{
    if (!Iptr)
    {
        throw runtime_error("Derefrencing a Null Pointer");
    }

    return Iptr->Data;
}

template <typename Type>
bool LinkList<Type>::Iterator::IsHead() const
{
    return Iptr == Head;
}

template <typename Type>
bool LinkList<Type>::Iterator::IsTail() const
{
    return Iptr == Tail;
}

template <typename Type>
bool LinkList<Type>::Iterator::IsNull() const
{
    return Iptr == nullptr;
}

template <typename Type>
bool LinkList<Type>::Iterator::IsNext() const
{
    return Iptr->Next != nullptr;
}

template <typename Type>
LinkList<Type>::Iterator::~Iterator()
{
    Iptr = nullptr;
}

template <typename Type>
typename LinkList<Type>::Node* LinkList<Type>::Iterator::GetNode()
{
    return Iptr;
}

//---------------------------------------------------------
//                Link List Declearation
//---------------------------------------------------------

template <typename Type>
LinkList<Type>::LinkList()
{
    Head = Tail = nullptr; 
    size = 0;
}

template <typename Type>
int LinkList<Type>::Getsize() const
{
    return size;
}

template <typename Type>
ostream& operator<<(ostream& out,LinkList<Type>& list)
{
    typename LinkList<Type>::ListIterator it = list.Begin();

    while(it != nullptr)
    {
        if(it != list.End())
            out << *it << "->";
        else
            out << *it;

        it++;
    }

    return out;
}

template <typename Type>
typename LinkList<Type>::ListIterator LinkList<Type>::ReturnPrevious(Iterator& it)
{
    if(it.IsNull())
        return nullptr;

    if(Head == Tail)
        return it;

    LinkList<Type>::ListIterator previous = Head;

    while(previous.IsNext())
    {
        if(previous.Iptr->Next == it.Iptr)
            break;
        
        previous++;
    }

    return previous;
}

template <typename Type>
typename LinkList<Type>::ListIterator LinkList<Type>::ReturnPrevious(const int& data)
{
    LinkList<Type>::ListIterator previous = Head,it = Head;

    if(previous.IsNull())
        return previous;

    it++;
    while(!it.IsNull())
    {
        if(*it == data)
            break;
        it++;
        previous++;
    }
    
    if(it != nullptr)
        return previous;
    else
        return nullptr;
}

template <typename Type>
typename LinkList<Type>::ListIterator LinkList<Type>::Find(const Type& key)
{
    LinkList<Type>::ListIterator it = Head;

    while(it != nullptr)
    {
        if(*it == key)
            break;
        
        it++;
    }

    return it;
}

template <typename Type>
typename LinkList<Type>::ListIterator LinkList<Type>::SearchByID(const int& key)
{
    LinkList<Type>::ListIterator it = Head;

    while(it != nullptr)
    {
        if(*it == key)
            break;
        
        it++;
    }

    return it;
}

template <typename Type>
void LinkList<Type>::AddtoHead(const Type& data)
{
    Node* NewNode = new Node(data,Head);

    if(Head)
    {
        Head = NewNode;
    }
    else
        Head = Tail = NewNode;

    size++;
}

template <typename Type>
void LinkList<Type>::AddtoTail(const Type& data)
{
    Node* NewNode = new Node(data);

    if(Head)
    {
        Tail->Next = NewNode;
        Tail = NewNode;
    }
    else
        Head = Tail = NewNode;

    size++;
}


template <typename Type>
void LinkList<Type>::DeleteAfter(Iterator& it)
{
    if(it != nullptr)
    {
        if(it.Iptr->Next == nullptr)
        {
            cout << "Error::Cannot Delete Null" << endl;
            return;
        }

        if(it.Iptr->Next == Tail)
            Tail = it.Iptr;
        
        Node* temp = it.Iptr->Next;
        it.Iptr->Next = it.Iptr->Next->Next;
        delete temp;
        size--;
    }
    else 
    {
        cout << "Error::Iterator Is Empty" << endl;
    }
}

template <typename Type>
void LinkList<Type>::DeleteTail()
{
    if(Head != Tail)
    {
        ListIterator it = Head;
    
        while(it.Iptr->Next != Tail);//to traverse

        Tail = it.Iptr;
        delete Tail->Next;

        Tail->Next = nullptr;
        size--;

    }
    else if(Head == Tail && Head != nullptr)
    {
        delete Tail;
        Tail = Head = nullptr;
        size--;
    }
    else
    {
        cout << "Error::No Node Exist" << endl;
    }
}

template <typename Type>
void LinkList<Type>::MovetoHead(Iterator& it)
{
    Iterator temp = it.Iptr->Next;

    if(it.IsNull())
    {
        cout << "Error::Iterator is Empty" << endl;
    }
    if(it.Iptr == Head)
        return;
    if(Head)
    {
        if(it.Iptr->Next == Tail)
        {
            Tail = it.Iptr;
            Tail->Next = nullptr;
        }
        else
        {
            it.Iptr->Next = it.Iptr->Next->Next;
        }

        temp.Iptr->Next = Head;
        Head = temp.Iptr;
    }
}

template <typename Type>
typename LinkList<Type>::ListIterator LinkList<Type>::Begin() const
{
    return ListIterator(Head);
}

template <typename Type>
typename LinkList<Type>::ListIterator LinkList<Type>::End() const
{
    return ListIterator(Tail);
}

template <typename Type>
LinkList<Type>::~LinkList()
{
    ListIterator it = Head;

    while(it != nullptr)
    {
        Node* temp = it.Iptr;
        it++;
        delete temp;
    }

    Head = Tail = nullptr;
}

#endif