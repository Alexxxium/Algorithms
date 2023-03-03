#pragma once
#include <iostream>


template<class T>
struct Node
{
	Node *left, *right;
	T key;
	size_t hight;

	Node(T vl): key(vl), hight(1) { right = left = nullptr; }
};




template<class T>
class AvlTree
{
private:

	Node<T> *root;
	size_t lenght;

public:

	 AvlTree(): root(nullptr), lenght(0) {}
	~AvlTree() { DestroyNode(root); }

private:

	void DestroyNode(Node<T>*);
	void fixedHight(Node<T>*);
	void print(Node<T>*);


	Node<T>* removeRoot();
	Node<T>* getMin    (Node<T>*);
	Node<T>* removeMin (Node<T>*); 
	Node<T>* remove    (Node<T>*, T vl);
	Node<T>* insert    (T, Node<T>*);


	int balanceFact(Node<T> *node) { return (getHight(node->right) - getHight(node->left)); }
	size_t getHight(Node<T> *node) { return node ? node->hight : 0; }

	Node<T>* leftRotate (Node<T>*);
	Node<T>* rightRotate(Node<T>*);
	Node<T>* balance    (Node<T>*);

public:	
	
	bool isEmpty() { return root == nullptr;}
	size_t size () { return lenght; }

	void push(const T&);
	void pop(const T&);

	const T& find(const T&);

	void outTree();
};


template<typename T>
void AvlTree<T>::DestroyNode(Node<T> *node)
{
	if (!node) return;
	DestroyNode(node->left);
	DestroyNode(node->right);
	delete node;
}


template<typename T>
void AvlTree<T>::print(Node<T> *curr)
{
	if (!curr) return;

	static int tabs(0);
	tabs += 5;

	print(curr->left);

	for (int i = 0; i < tabs; ++i)
		std::cout << ' ';

	std::cout << curr->key << '\n';

	print(curr->right);

	tabs -= 5;
}
template<typename T>
Node<T>* AvlTree<T>::removeRoot()
{
	if (root->left == root->right)					
	{
		delete root;
		root = nullptr;
	}
	else if (root->left && root->right)				
	{
		Node<T> *lt = root->left;						
		Node<T> *rt = root->right;

		delete root;								

		Node<T> *min = getMin(rt);						
		min->right = removeMin(rt);					
		min->left = lt;								

		root = min;									

		return balance(root);						
	}
	else if (root->left)							
	{
		Node<T> *lt = root->left;						
		delete root;
		root = lt;									
		balance(root);
	}
	else											
	{
		Node<T> *rt = root->right;						
		delete root;
		root = rt;
		balance(root);
	}
}
template<typename T>
Node<T>* AvlTree<T>::getMin(Node<T> *node)
{
	while (node->left)
		node = node->left;

	return node;
}
template<typename T>
Node<T>* AvlTree<T>::removeMin(Node<T> *node)
{
	if (!node->left)
		return node->right;

	node->left = removeMin(node->left);				
	return balance(node);
}
template<typename T>
Node<T>* AvlTree<T>::remove(Node<T> *node, T vl)
{
	if (!node) return nullptr;


	if (vl < node->key)
		node->left = remove(node->left, vl);		
	else if (vl > node->key)
		node->right = remove(node->right, vl);		
	else
	{
		if (node == root)							
		{
			removeRoot();
			return nullptr;
		}

		Node<T> *lt = node->left;
		Node<T> *rt = node->right;

		delete node;

		if (!rt) return lt;							

		Node<T> *min = getMin(rt);						
		min->right = removeMin(rt);					
		min->left = lt;

		return balance(min);
	}
	return balance(node);
}
template<typename T>
Node<T>* AvlTree<T>::insert(T vl, Node<T> *curr)
{
	if (!curr)
		return new Node<T>(vl);

	if (vl < curr->key)
		curr->left = insert(vl, curr->left);
	else
		curr->right = insert(vl, curr->right);

	return balance(curr);
}


template<typename T>
void   AvlTree<T>::fixedHight(Node<T> *node)
{
	size_t l_h = getHight(node->left);
	size_t r_h = getHight(node->right);

	node->hight = (l_h > r_h ? l_h : r_h) + 1;
}


template<typename T>
Node<T>* AvlTree<T>::leftRotate(Node<T> *node)
{
	Node<T> *newNode = node->right;
	node->right = newNode->left;
	newNode->left = node;
	if (node == root)
		root = newNode;

	fixedHight(node);
	fixedHight(newNode);

	return newNode;
}
template<typename T>
Node<T>* AvlTree<T>::rightRotate(Node<T> *node)
{
	Node<T> *newNode = node->left;
	node->left = newNode->right;
	newNode->right = node;
	if (node == root)
		root = newNode;

	fixedHight(node);
	fixedHight(newNode);

	return newNode;
}
template<typename T>
Node<T>* AvlTree<T>::balance(Node<T> *node)
{

	fixedHight(node);

	if (balanceFact(node) == 2)
	{
		if (balanceFact(node->right) < 0)
			node->right = rightRotate(node->right);		
		return leftRotate(node);							
	}
	if (balanceFact(node) == -2)
	{
		if (balanceFact(node->left) > 0)
			node->left = leftRotate(node->left);
		return rightRotate(node);
	}

	return node;
}


template<typename T>
void AvlTree<T>::push(const T &vl)
{
	Node<T> *newNode = insert(vl, root);		
	root = newNode;								
	++lenght;
}
template<typename T>
void AvlTree<T>::pop(const T &vl)
{
	remove(root, vl);
	--lenght;
}


template<typename T>
const T& AvlTree<T>::find(const T &vl)
{
	Node<T> *curr(root);

	while (curr)
	{
		if (curr->key == vl)
			break;
		if (vl < curr->key)
			curr = curr->left;
		else
			curr = curr->right;
	}
	//if (!curr) throw 1;				
	//return curr->key;

	return curr ? curr->key : T();		
}


template <typename T>
void AvlTree<T>::outTree()
{
	if (isEmpty()) return;

	std::cout << "\n\nRoot:";
	print(root);
	std::cout << "\n" << std::endl;
}
