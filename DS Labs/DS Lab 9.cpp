#include<iostream>
#include "queue"
using namespace std;

template <typename T>
class AVL
{
private:
    class Bnode;
    Bnode* root;
    void insertR(T d, Bnode*& ptr);
    void deleteR(T d, Bnode*& ptr);
    void deleteBnode(Bnode*&);
    bool searchR(T d, Bnode*);
    void PrintR(Bnode* node);///inorder
    void Destroy(Bnode*&);
    int CountLeaveNodes(Bnode*);
    int CountHeight(Bnode*);
    int CountChildwithOneChild(Bnode*);
    void PostorderR(Bnode*);
    void PreorderR(Bnode*);
    void PrintNodeatLevel(int num, int count, Bnode*);
    void PrintInRange(int low, int high, Bnode* node);
    void rotateright(Bnode*&);
    void rotateleft(Bnode*&);
    void rotaterightleft(Bnode*&);
    void rotateleftright(Bnode*&);
    int height(Bnode* node)
    {
        if(!node)
            return 0;
        int left = -1, right = -1;
        if (node->left)
            left = node->left->height;
        if (node->right)
            right = node->right->height;

        if (left > right)
            return left + 1;
        else
            return right + 1;
    }
    void Balance(Bnode*&);
    Bnode* FindMax(Bnode* node)
    {
        if (node->right == nullptr)
            return node;
        else
            return FindMax(node->right);
    }
    void PrintNodeswithB1orneg1(Bnode*);
    Bnode FindMin(Bnode* node)
    {
        if (node->left == nullptr)
            return node;
        else
            return FindMin(node->left);
    }
    int CountBalanceFactorofnodes0(Bnode*);
    int CountNodeswithTwoChilds(Bnode*);
    T SumofAllNodes(Bnode*);
    void PrintHeightofAllNodesPreOrder(Bnode*);
public:
    AVL()
    {
        root = nullptr;
    }
    void insertR(T d)
    {
        insertR(d, root);
    }
    void deleteR(T d) { deleteR(d, root); }
    bool searchR(T d) { return searchR(d, root); }
    int CountLeaveNodes()
    {
        if (root == nullptr)
            return 0;
        else
            return CountLeaveNodes(root);
    }
    int CountChildwithOneChild()
    {
        return CountChildwithOneChild(root);
    }
    int CountHeight()
    {
        return CountHeight(root);
    }
    void InorderR()
    {
        PrintR(root);
        cout << endl;
    }
    void PostorderR()
    {
        PostorderR(root);
        cout << endl;
    }
    void PreorderR()
    {
        PreorderR(root);
        cout << endl;
    }
    void PrintNodeatLevel(int num)
    {
        if (CountHeight(root) >= num)
        {
            PrintNodeatLevel(num, 0, root);
            cout << endl;
        }
        else
            cout << "No Node Exist at Level " << num << endl;
    }
    void LevelorderI();
    void DeleteAllR()
    {
        Destroy(root);
    }
    void PrintInRange(int low, int high)
    {
        PrintInRange(low, high, root);
        cout << endl;
    }
    void PrintNodeswithB1orneg1() { PrintNodeswithB1orneg1(root); }
    T FindMax() 
    {
        if (root == nullptr)
            return -99999;
        return FindMax(root)->data;
    }
    T FindMin()
    {
        if (root == nullptr)
            return 999999;
        
        return FindMin(root)->data;

    }
    int CountNodeswithTwoChilds()
    {
        if(root == nullptr)
            return 0;

        return CountNodeswithTwoChilds(root);    
    }
    int CountBalanceFactorofnodes0()
    {
        return CountBalanceFactorofnodes0(root);
    }
    T SumofAllNodes(){ return SumofAllNodes(root); }
    void PrintHeightofAllNodes()
    {
        PrintHeightofAllNodesPreOrder(root);
        cout << endl; 
    }
    ~AVL()
    {
        Destroy(root);
    }
};

template <typename T>
class AVL<T>::Bnode
{
public:
    Bnode* left;
    Bnode* right;
    T data;
    int height;
    Bnode(T d, Bnode* r = 0, Bnode* l = 0)
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

template <typename T>
void AVL<T>::rotateleft(Bnode*& node)
{
    // node = X ,node->right = Y
    Bnode* temp = node->right->left;// take B
    node->right->left = node;// y->left = X
    node = node->right;//y->left = X
    node->left->right = temp;//y->X->right = temp
    // x = node -> left y = node

    //calculate height now
    node->left->height = height(node->left);
    node->height = height(node);

}

template <typename T>
void AVL<T>::rotateright(Bnode*& node)
{
    //node = X node->left = Y
    Bnode* temp = node->left->right;//copy B
    node->left->right = node;//y->right = X
    node = node->left;//X = Y
    node->right->left = temp; //X->left = temp B

    node->right->height = height(node->right);
    node->height = height(node);
}


template <typename T>
void AVL<T>::rotateleftright(Bnode*& node)
{
    rotateleft(node->left);
    rotateright(node);
}

template <typename T>
void AVL<T>::rotaterightleft(Bnode*& node)
{
    rotateright(node->right);
    rotateleft(node);
}

template <typename T>
void AVL<T>::Balance(Bnode*& node)
{
    if(!node)
        return;
    if (height(node->right) - height(node->left) < -1)
    {
        if (height(node->left->left) >= height(node->left->right))
            rotateright(node);
        else
            rotateleftright(node);
    }
    if (height(node->right) - height(node->left) > 1)
    {
        if (height(node->right->right) >= height(node->right->left))
            rotateleft(node);
        else
            rotaterightleft(node);
    }

    node->height = height(node);
}

template <typename T>
void AVL<T>::insertR(T d, Bnode*& ptr)
{
    if (ptr == nullptr)
        ptr = new Bnode(d);
    else
    {
        if (ptr->data >= d)
            insertR(d, ptr->left);
        else
            insertR(d, ptr->right);
    }

    Balance(ptr);

}

template <typename T>
void AVL<T>::deleteR(T d, Bnode*& node)
{
    if (node)
    {
        if (node->data > d)
            deleteR(d, node->left);
        else if (node->data < d)
            deleteR(d, node->right);
        else // if d == ptr->data
            deleteBnode(node);

        Balance(node);
    }
}

template <typename T>
void AVL<T>::deleteBnode(Bnode*& node)
{
    Bnode* temp = node;

    if (node->left == nullptr)
    {
        node = node->right;
    }
    else if (node->right == nullptr)
    {
        node = node->left;
    }
    else
    {
        temp = nullptr;
        node->data = FindMax(node->left)->data;
        deleteR(node->data, node->left);
    }

    if (temp)
    {
        delete temp;
        temp = nullptr;
    }
        
}

template <typename T>
bool AVL<T>::searchR(T d, Bnode* node)
{
    if (node)
    {
        if (node->data > d)
            return searchR(d, node->left);
        else if (node->data < d)
            return searchR(d, node->right);
        else // if d == ptr->data
            return 1;
    }
    else
        return 0;
}

template <typename T>
void AVL<T>::PrintR(Bnode* node)
{
    if (node)
    {
        PrintR(node->left);
        cout << node->data << " ";
        PrintR(node->right);
    }
}

template <typename T>
void AVL<T>::Destroy(Bnode*& node)
{
    if (node)
    {
        Destroy(node->left);
        Destroy(node->right);
        delete node;
        node = nullptr;
    }
}

template <typename T>
void AVL<T>::PostorderR(Bnode* node)
{
    if (node)
    {
        PostorderR(node->left);
        PostorderR(node->right);
        cout << node->data << " ";
    }
}

template <typename T>
void AVL<T>::PreorderR(Bnode* node)
{
    if (node)
    {
        cout << node->data << " ";
        PreorderR(node->left);
        PreorderR(node->right);
    }
}

template <typename T>
void AVL<T>::PrintNodeatLevel(int num, int count, Bnode* node)
{
    if (node)
    {
        if (num == count)
        {
            cout << node->data << " ";
            return;
        }
        PrintNodeatLevel(num, count + 1, node->left);
        PrintNodeatLevel(num, count + 1, node->right);
    }


}

template <typename T>
int AVL<T>::CountLeaveNodes(Bnode* node)
{
    if (node == nullptr)
        return 0;

    if (node->left == nullptr && node->right == nullptr)
        return 1;

    return CountLeaveNodes(node->left) + CountLeaveNodes(node->right);

}

template <typename T>
int AVL<T>::CountHeight(Bnode* node)
{
    return height(root);
}


template <typename T>
int AVL<T>::CountChildwithOneChild(Bnode* node)
{
    if (node == nullptr)
        return 0;

    if ((node->left == nullptr) != (node->right == nullptr))
        return 1 + CountChildwithOneChild(node->left) + CountChildwithOneChild(node->right);

    return CountChildwithOneChild(node->left) + CountChildwithOneChild(node->right);


}

template <typename T>
void AVL<T>::PrintInRange(int low, int high, Bnode* node)
{
    if (node)
    {
        PrintInRange(low, high, node->left);
        if (low <= node->data && node->data <= high)
            cout << node->data << " ";
        PrintInRange(low, high, node->right);
    }
}

template <typename T>
void AVL<T>::PrintNodeswithB1orneg1(Bnode* node)
{
    if (node)
    {
        PrintNodeswithB1orneg1(node->left);
        if (height(node->right) - height(node->left) == 1 || height(node->right) - height(node->left) == -1)
            cout << node->data << ' ';
        PrintNodeswithB1orneg1(node->right);

    }
    cout << endl;
}

template <typename T>
int AVL<T>::CountBalanceFactorofnodes0(Bnode* node)
{
    if (node)
    {
        if (height(node->right) - height(node->left) == 0)
        {
            return 1 + CountBalanceFactorofnodes0(node->left) + CountBalanceFactorofnodes0(node->right);
        }
        else
            return CountBalanceFactorofnodes0(node->left) + CountBalanceFactorofnodes0(node->right);
    }
    else
        return 0;
}


template <typename T>
int AVL<T>::CountNodeswithTwoChilds(Bnode* node)
{
    if (node)
    {
        if (node->right != nullptr &&  node->left != nullptr)
        {
            return 1 + CountNodeswithTwoChilds(node->left) + CountNodeswithTwoChilds(node->right);
        }
        else
            return CountNodeswithTwoChilds(node->left) + CountNodeswithTwoChilds(node->right);
    }
    else
        return 0;
}


template <typename T>
void AVL<T>::LevelorderI()
{
    int nodesatpreviouslevel = -1;
    int nodesatlevel = 0;
    Bnode* node = root;
    queue<typename AVL<T>::Bnode*> q;
    if(root)
    {
        q.push(root);
        nodesatlevel++;
        nodesatpreviouslevel = 1;
    }
    while(!q.empty())
    {
        node = q.front();
        q.pop();
        nodesatpreviouslevel--;
        
        if(nodesatpreviouslevel == 0)
        {
            nodesatpreviouslevel = nodesatlevel;
            nodesatlevel = 0;
            cout << endl;
        }
        if(node->left)
        {
            q.push(node->left);
            nodesatlevel++;
        }
        if(node->right)
        {
            q.push(node->right);
            nodesatlevel++;
        }        
        cout << node->data << " ";    
        
    }
    cout << endl;
}

template <typename T>
T AVL<T>::SumofAllNodes(Bnode* node)
{
    if(node)
    {
        return node->data + SumofAllNodes(node->right) + SumofAllNodes(node->left);
    }
    else 
        return 0;
}

template <typename T>
void AVL<T>::PrintHeightofAllNodesPreOrder(Bnode* node)
{
    if(node)
    {
        cout << node->height << " ";
        PrintHeightofAllNodesPreOrder(node->left);
        PrintHeightofAllNodesPreOrder(node->right);
    }
}

int main()
{
    AVL<int> avl;
    avl.insertR(50);
    avl.insertR(30);
    avl.insertR(20);
    avl.insertR(10);
    avl.insertR(70);
    avl.insertR(90);
    avl.insertR(14);

    cout << "Avl Tree ::\n";
    avl.LevelorderI();
    avl.PrintHeightofAllNodes();

	cout << "Detete Leaf Case 1 ::\n";
    avl.deleteR(14);
    avl.InorderR();
    avl.PrintHeightofAllNodes();
    
	cout << "Detete Bnode with 1 child Case 2 ::\n";
	avl.deleteR(20);
	avl.InorderR();
    avl.PrintHeightofAllNodes();

	cout << "Detete Bnode with 2 child Case 3 ::\n";
	avl.deleteR(70);
	avl.InorderR();
    avl.PrintHeightofAllNodes();
    cout << endl << endl;

    cout << "Inorder Recursive :: \n";
    avl.InorderR();
    cout << endl << endl;

    cout << "PreOrder Recursive :: \n";
    avl.PreorderR();
    cout << endl << endl;
    
    cout << "Postorder Recursive :: \n";
    avl.PostorderR();
    cout << endl << endl;
	
    cout << "Level Order Iterative :: \n";
    avl.LevelorderI();
    cout << endl << endl;

    cout << "Node at Level " << 3 << " :: ";
    avl.PrintNodeatLevel(3);
    cout << "Leave Node Count :: " << avl.CountLeaveNodes() << endl;
	cout << "Height of Tree :: " << avl.CountHeight() << endl;
	cout << "Nodes With One Child :: " << avl.CountChildwithOneChild() << endl;
    cout << "Count Nodes with One Child :: " << avl.CountNodeswithTwoChilds() << endl;
    cout << "Nodes with Balance Factor 0 :: " << avl.CountBalanceFactorofnodes0() << endl;
    cout << "Sum of All Nodes :: \n" << avl.SumofAllNodes() << endl;

    cout << endl << endl;
	
    cout << "Print Nodes with Balance Factor 1 or -1 :: " << endl;
    avl.PrintNodeswithB1orneg1();
    cout << endl << endl;

    cout << "Print In Range 12-51 :: \n";
    avl.PrintInRange(12,51);
    cout << endl << endl;

    cout << endl << endl;


}