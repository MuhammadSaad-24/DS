#include <iostream>
#include "LinkList.h"
#include "queue"
#include "stack"

using namespace std;
// class Place8QueensonBoard
// {
// private:
//     char board[8][9];
//     char queen;
//     char empty;
//     int currx,curry;
//     int rows,cols;
//     void PrintBoard(int i,int j)
//     {
//         if(board[i][j] == '\0')
//         {
//             cout << endl;
//             j = 0;
//             i++;
//         }
//         else if(i == 7 && board[i][j] == '\0')
//         {
//             cout << endl;
//             return;
//         }
//         else
//         {
//             cout << board[i][j] << ' ';
//             j++;
//         }
//         PrintBoard(i,j);
//     }
// public:
//     Place8QueensonBoard(char q = 'Q',char e = '0')
//     {
//         rows = cols = 8;
//         queen = q;
//         empty = e;
//         currx = curry = 0;

//         MakeBoard();
//     }
//     void MakeBoard()
//     {
//         if(currx < 7 && curry == 8)
//         {
//             board[currx][curry] = '\0';
//             curry = 0;
//             currx++;
//         }
//         else if(currx == 7 && curry == 8)
//         {
//             board[currx][curry] = '\0';
//             currx = curry = 0;
//             return;
//         }
//         else
//             curry++;
//         MakeBoard();
//     }
    
//     void Place_Queen_on_Index()
//     {
//         board[currx][curry] = queen;
//     }
//     void Replace_Queen_on_Index()
//     {
//         board[currx][curry] = empty;
//     }

//     bool CheckAvalability(int i ,int j,bool& flag)
//     {
//         if(i < 0 || i > rows - 1 || j < 0 || j > cols - 1)
//             flag = true;    
//         if(board[i][j] == queen)
//             flag = false;

//         if(!flag)
//             return false;

//         CheckAvalability(i,j + 1,flag);
//         CheckAvalability(i,j - 1,flag);
//         CheckAvalability(i + 1,j,flag);
//         CheckAvalability(i - 1,j,flag);
//         CheckAvalability(i + 1,j + 1,flag);
//         CheckAvalability(i - 1,j - 1,flag);
//     }
//     void Print()
//     {
//         PrintBoard(0,0);
//     }
    
// };

// void FabinachiSeries(int first,int second,int end)
// {
//     if(first == 0)
//         cout << 0 << ',' << 1;
//     else
//         cout << ',' << second;

//     if(second == end)
//         return;

//     int temp = second;
//     second += first;
//     first = temp;

//     FabinachiSeries(first,second,end);
// }

// void FabinachiSeries(int num)
// {
//     FabinachiSeries(0,1,num);
// }

// void Copy(char arr[],int& size,typename LinkList<char>::ListIterator it)
// {
//     if(!it)
//         return;

//     arr[size++] = *it;
//     it++;
//     Copy(arr,size,it);
// }

// bool IsPalindrome(char arr[],int high,int low)
// {
//     if(low >= high)
//         return true;

//     if(!(arr[low] == arr[high] || arr[low] - 32 == arr[high] || arr[low] == arr[high] - 32))
//         return false;

//     return IsPalindrome(arr,high - 1,low + 1);
// }

// bool IsPalindrome(LinkList<char>& list)
// {
//     int size = 0;
//     const int s = list.Getsize();
//     char arr[s];

//     Copy(arr,size,typename LinkList<char>::ListIterator(list.Begin()));
//     return IsPalindrome(arr,size - 1,0);
// }

// int main()
// {
//     FabinachiSeries(34);
//     cout << endl;
//     cout.put('s');
//     cout << endl;
//     int matrix[5][5] =
//     {
//         {1,2,3,4,5},
//         {6,7,8,9,10},
//         {11,12,13,14,15},
//         {16,17,18,19,20},
//         {21,22,23,24,25}
//     };

//     LinkList<char> list;
//     list.AddtoTail('A');
//     list.AddtoTail('B');
//     list.AddtoTail('C');
//     list.AddtoTail('b');
//     list.AddtoTail('a');

//     if(IsPalindrome(list))
//         cout << "Link List is Plaindrome\n";
//     else
//         cout << "Link List is not Palindrome\n";

//     return 0;
// }

// #include "list"
// #include "iterator"

// int main()
// {
//     list<int> l1;
//     stack<int> s1;
//     queue<int> q1;
//     l1.remove_if(1 > 0);
// }


template <class T>
class BSTree {
private:
class Bnode; // forward declaration
    Bnode * root;
    void visit(Bnode * ptr) { cout << ptr->data << " "; }
    void getPredecessor(Bnode * node, T & data);
    void deleteR(T d,Bnode*&);
    void deleteBnode(Bnode*&);
    void Destroy(Bnode *& node);
    bool searchR(Bnode* ,T d);
    void insertR(Bnode*& ,T d);
    void InOrder(Bnode*);
public:
    BSTree()
    {
        root = nullptr;

    }
    void insertR(T d) {insertR(root,d);}
    void insertI(T d);
    bool searchR(T d)
    {
        return searchR(root,d);
    }
    bool searchI(T d);
    void deleteR(T d);
    void deleteI(T d);
    void PrintR();
    void PrintI();
    ~BSTree() 
    { 
        Destroy(root);
        root = nullptr; 
    }
};

template <typename Type>
class BSTree<Type>::Bnode
{
public:
    Type data;
    Bnode* right;
    Bnode* left;
    Bnode(Type& d, Bnode* l = 0 , Bnode* r = 0 )
    {
        data = d;
        left = l;
        right = r;
    }
    ~Bnode()
    {
        left = nullptr;
        right = nullptr;
    }
};

template <class T>
bool BSTree<T>::searchR(Bnode* node,T d)
{
    if (node) 
    {
        if (node -> data > d)
            return searchR(node -> left, d);

        else if (node -> data < d)
            return searchR(node -> right, d);

        else
            return true;
    }
    else
        return false;

}

template <class T>
bool BSTree<T>::searchI(T key) 
{    
    Bnode* iter = root;
    bool flag = false;

    while (iter && !flag) 
    {
        if (iter ->data == key)
            flag = true;

        else if (iter->data > key)
            iter= iter->left;

        else
            iter= iter->right;

    }
    return flag;
}

template <class T>
void BSTree<T>::insertR(Bnode *& node,T d) 
{
    if (node == NULL)
        node = new Bnode(d);
    else if (node->data > d)
        insertR(node->left,d);
    else
        insertR(node->right,d);
}

template <class T>
void BSTree<T>::insertI(T d) 
{
    Bnode * newBnode = new Bnode(d);
    Bnode * parent = root;
    Bnode * child = root;

    while (child) 
    {
        parent = child;
        
        if (parent -> data > d)
            child = child -> left;
        else if (parent -> data <= d)
            child = child -> right;

    }

    if (parent == NULL)
        root = newBnode;
    else if (parent -> data > d)
        parent -> left = newBnode;
    else if (parent -> data <= d)
        parent -> right = newBnode;

}

template <class T>
void BSTree<T>::PrintR()
{
    InOrder(root);
}

template <class T>
void BSTree<T>::InOrder(Bnode *t)
{
    if (t) 
    {
        InOrder(t->left);
        visit(t);
        InOrder(t->right);
    }
}

template <class T>
void BSTree<T>::Destroy(Bnode *&t)
{
    if (t) 
    {
        InOrder(t->left);
        InOrder(t->right);
        delete t;
    }
}

template <typename T>
void BSTree<T>::deleteR(T d)
{
    deleteR(d, root);
}

template <class T>
void BSTree<T>::deleteR(T d, Bnode *& node) {
    
    if (node) 
    {
        if (d > node->data)    
            deleteR(d, node->right);
        else if (d < node->data)
            deleteR(d, node->left);
        else
            deleteBnode(node);
    }
}

template <class T>
void BSTree<T>::deleteBnode(Bnode *& node) 
{
    Bnode * tmp = node;
    if (node->left == NULL) // Bnode has no left child
        node = node->right;
    else if(node->right == NULL) // Bnode has no right child;
        node = node->left;
    else
    { // Bnode has both children
        tmp = node->left;
        previous = node;
        while(tmp->right != NULL){// locate predecessor
            previous = tmp;
            tmp=tmp->right;
        }
        
        node->data = tmp->data; // copy data
        if(previous == node)
            previous->left = tmp->left
        else
            previous -> right = tmp->left
    }
    delete tmp;
}

int main()
{
    BSTree<int> tree1;
    tree1.insertR(15);
    tree1.insertR(8);
    tree1.insertR(20);
    tree1.insertR(17);
    tree1.insertR(14);
    tree1.insertR(12);
    tree1.insertR(19);
    tree1.insertR(6);
    tree1.insertR(78);

    tree1.PrintR();

}