#include<iostream>
#include "stack"
#include "queue"

using namespace std;

template <typename T>
class BSTree
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
    void PrintNodeatLevel(int num,int count,Bnode*);
    void PrintInRange(int low,int high,Bnode* node);
public:
	BSTree()
	{
		root = nullptr;
	}
	void insertR(T d)
	{
		insertR(d, root);
	}
	void insertI(T d);
	void deleteR(T d) { deleteR(d, root); }
	void deleteI(T d);
	bool searchR(T d) { return searchR(d, root); }
	bool searchI(T d);
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
	void InorderI();
    void PostorderR()
    {
        PostorderR(root);
        cout << endl;
    }
    void PostorderI();
    void PreorderR()
    {
        PreorderR(root);
        cout << endl;
    }
    void PreorderI();
    void PrintNodeatLevel(int num)
    {
        if(CountHeight(root) >= num)
        {
            PrintNodeatLevel(num,0,root);
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
    void PrintInRange(int low,int high)
    {
        PrintInRange(low,high,root);
        cout << endl;
    }
	~BSTree()
	{
		Destroy(root);
	}
};

template <typename T>
class BSTree<T>::Bnode
{
public:
	Bnode* left;
	Bnode* right;
	T data;
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
void BSTree<T>::insertR(T d, Bnode*& ptr)
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
}

template <typename T>
void BSTree<T>::insertI(T d)
{
	Bnode* parent = nullptr, * child = root,
	*NBnode = new Bnode(d);
	
	while (child != nullptr)
	{
		parent = child;
		if (child->data >= d)
			child = child->left;
		else
			child = child->right;
	}

	if (parent == nullptr)
		root = NBnode;
	else if (parent->data >= d)
		parent->left = NBnode;
	else
		parent->right = NBnode;


}

template <typename T>
void BSTree<T>::deleteR(T d, Bnode*& node)
{
	if (node)
	{
		if (node->data > d)
			deleteR(d, node->left);
		else if (node->data < d)
			deleteR(d, node->right);
		else // if d == ptr->data
			deleteBnode(node);

	}
}

template <typename T>
void BSTree<T>::deleteI(T d)
{
	Bnode* node = root;

    if(root->data == d)
    {
        deleteBnode(root);
        return;
    }

    while(node)
    {
        if(node->left)     
            if(node->left->data == d)
                deleteBnode(node->left);
        if(node->right)
            if(node->right->data == d)
                deleteBnode(node->right);

        if(node->data > d)
            node = node->left;
        else
            node = node->right;        
    }
}

template <typename T>
void BSTree<T>::deleteBnode(Bnode*& node)
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
		Bnode* temp2 = node->left,* previous = node;

		while (temp2->right != nullptr)
		{
			previous = temp2;
			temp2 = temp2->right;
		}

		if (temp2 == node->left)
		{
			temp2->right = node->right;
			node = temp2;
		}
		else
		{
			previous->right = temp2->left;
			temp2->right = node->right;
			temp2->left = node->left;
			node = temp2;
		}

	}

    delete temp;
	temp = nullptr;

}

template <typename T>
bool BSTree<T>::searchR(T d, Bnode* node)
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
bool BSTree<T>::searchI(T d)
{
	Bnode* node = root;

	while (node)
	{
		if (node->data > d)
			node = node->left;
		else if (node->data < d)
			node = node->right;
		else // if d == ptr->data
			return 1;
	}
	
	return 0;
}

template <typename T>
void BSTree<T>::PrintR(Bnode* node)
{
	if (node)
	{
		PrintR(node->left);
		cout << node->data << " ";
		PrintR(node->right);
	}
}

template <typename T>
void BSTree<T>::Destroy(Bnode*& node)
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
void BSTree<T>::InorderI()
{
    Bnode* node = root;
    stack<typename BSTree<T>::Bnode*> st;
    while(node)
    {
        while(node)
        {
            if(node->right)
                st.push(node->right);
            st.push(node);
            
            node = node->left;
        }

        if(!st.empty())
        {
            node = st.top();
            st.pop();
        }    


        while(!st.empty() && node->right == nullptr)
        {
            cout << node->data << " ";
            if(!st.empty())
            {
               node = st.top();
               st.pop(); 
            }   
        } 
        cout << node->data << " ";
        
        if(!st.empty())
        {
            node = st.top();
            st.pop();
        }
        else 
            node = nullptr; 
    }

    cout << endl;
}

template <typename T>
void BSTree<T>::PostorderR(Bnode* node)
{
    if(node)
    {
        PostorderR(node->left);
        PostorderR(node->right);
        cout << node->data << " ";
    }
}

template <typename T>
void BSTree<T>::PostorderI()
{
    Bnode* node = root,*previous = nullptr;
    stack<typename BSTree<T>::Bnode*> st;

    while(node)
    {
        while(node)
        {
            st.push(node);
            if(node->right)
                st.push(node->right);
            node = node->left;            
        }

        previous = node;

        if(!st.empty())
        {
            node = st.top();
            st.pop();
        }

        while(!st.empty() && node->left == nullptr)
        {
            
            if(node->right && previous->data < node->data)
            {
                st.push(node);
                st.push(node->right);
            }
            else
                cout << node->data << " ";

            previous = node;
            if(!st.empty())
            {
                node = st.top();
                st.pop();
            }
        }
        do
        {
            previous = node;
            cout << node->data << " ";
            if(!st.empty())
            {
                node = st.top();
                st.pop();
            }
        }while(!st.empty() && previous->data > node->data);

        if(st.empty())
        {
            cout << node->data << " ";
            node = nullptr;
        }
    }

    cout << endl;
}

template <typename T>
void BSTree<T>::PreorderR(Bnode* node)
{
    if(node)
    {
        cout << node->data << " ";
        PreorderR(node->left);
        PreorderR(node->right);
    }
}

template <typename T>
void BSTree<T>::PreorderI()
{
    Bnode* node = root;
    stack<typename BSTree<T>::Bnode*> st;
    if(root)
        st.push(root);

    while(!st.empty())
    {
        node = st.top();
        st.pop();
        cout << node->data << " ";
        if(node->right)
            st.push(node->right);
        if(node->left)
            st.push(node->left);
    }

    cout << endl;
}

template <typename T>
void BSTree<T>::LevelorderI()
{
    int nodesatpreviouslevel = -1;
    int nodesatlevel = 0;
    Bnode* node = root;
    queue<typename BSTree<T>::Bnode*> q;
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
}

template <typename T>
void BSTree<T>::PrintNodeatLevel(int num,int count,Bnode* node)
{
    if(node)
    {
        if(num == count)
        {
            cout << node->data << " ";
            return;
        }
        PrintNodeatLevel(num,count + 1,node->left);
        PrintNodeatLevel(num,count + 1,node->right);
    }
        

}

template <typename T>
int BSTree<T>::CountLeaveNodes(Bnode* node)
{
	if (node == nullptr)
		return 0;
	
	if (node->left == nullptr && node->right == nullptr)
		return 1;

	return CountLeaveNodes(node->left) + CountLeaveNodes(node->right);

}

template <typename T>
int BSTree<T>::CountHeight(Bnode* node)
{
	if (node == nullptr)
		return -1;

	int left = CountHeight(node->left);
	int right = CountHeight(node->right);
	
	if (left > right)
		return 1 + left;
	else
		return 1 + right;
}

template <typename T>
int BSTree<T>::CountChildwithOneChild(Bnode* node)
{
	if (node == nullptr)
		return 0;

    if ((node->left == nullptr) != (node->right == nullptr))
		return 1;
    
	return CountChildwithOneChild(node->left) + CountChildwithOneChild(node->right);


}

template <typename T>
void BSTree<T>::PrintInRange(int low,int high,Bnode* node)
{
    if(node)
    {
        PrintInRange(low,high,node->left);
        if(low <= node->data && node->data <= high)
            cout << node->data << " ";
        PrintInRange(low,high,node->right);
    }
}

int main()
{
	BSTree<int> tree;
	tree.insertI(50);
	tree.insertR(25);
	tree.insertI(75);
	tree.insertR(12);
	tree.insertI(37);
	tree.insertR(7);
	tree.insertI(20);
	tree.insertR(30);
	tree.insertI(45);
	tree.insertR(60);
	tree.insertI(80);
    tree.insertR(90);
	tree.insertR(51);
	tree.insertI(23);
	tree.insertR(21);

	cout << "Tree ::\n";
	tree.InorderR();
    cout << endl << endl;

	cout << "Detete Leaf Case 1 ::\n";
	tree.deleteI(21);
	tree.InorderI();

	cout << "Detete Bnode with 1 child Case 2 ::\n";
	tree.deleteI(60);
	tree.InorderR();

	cout << "Detete Bnode with 2 child Case 3 ::\n";
	tree.deleteR(25);
	tree.InorderR();

    cout << endl << endl;

    cout << "Inorder Recursive :: \n";
    tree.InorderR();
    cout << "Inorder Iterative :: \n";
    tree.InorderI();
    cout << endl << endl;

    cout << "PreOrder Recursive :: \n";
    tree.PreorderR();
    cout << "PreOrder Iterative :: \n";
    tree.PreorderI();    
    cout << endl << endl;
    
    cout << "Postorder Recursive :: \n";
    tree.PostorderR();
    cout << "Postorder Iterative :: \n";
    tree.PostorderI();
    cout << endl << endl;
	
    cout << "Level Order Iterative :: \n";
    tree.LevelorderI();
    cout << endl << endl;

    cout << "Node at Level " << 3 << " :: ";
    tree.PrintNodeatLevel(3);
    cout << "Leave Node Count :: " << tree.CountLeaveNodes() << endl;
	cout << "Height of Tree :: " << tree.CountHeight() << endl;
	cout << "Nodes With One Child :: " << tree.CountChildwithOneChild() << endl;
    cout << endl << endl;
	
    cout << "Print In Range 12-51 :: \n";
    tree.PrintInRange(12,51);
    cout << endl << endl;

    tree.InorderR();

}
