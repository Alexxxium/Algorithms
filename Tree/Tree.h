#pragma once


template <class T>
struct Node
{
	const T data;
	Node *left, *right, *parent;

	Node(T vl): data(vl)
	{
		parent = left = right = nullptr;
	}
};



template<class T>
class Tree
{
private:

	Node<T> *top;

	void  DestroyNode(Node<T>*);
	Node<T>* getNode(T);
	Node<T>* getMinNode(Node<T>*);
	void  print(Node<T>*);
	
	// Беды реализации:
	void funck1(Node<T>*, T);	// удаление, если дочерних объектов нет
	void funck2(Node<T>*, T);	// удаление, если есть левый дочерний объект
	void funck3(Node<T>*, T);	// удаление, если есть правый дочерний объект
	void funck4(Node<T>*, T);	// удаление, если есть оба дочерних объекта
	
public:

	 Tree():top(nullptr) { /********************/ }
	~Tree()				 { DestroyNode(top);	  }
	bool is_empty()		 { return top == nullptr; }

	void insert(T);
	void pop(T vl);

	
	void outTree();
};



template <typename T>
void Tree<T>::DestroyNode(Node<T> *node)
{
	if (node) {
		DestroyNode(node->left);
		DestroyNode(node->right);
		delete node;
	}
}


template <typename T>
Node<T>* Tree<T>::getNode(T vl)
{
	Node<T> *curr = top;

	while (curr && curr->data != vl)
	{
		if (vl < curr->data)
			curr = curr->left;
		else
			curr = curr->right;
	}

	return curr;		// (nullptr!!!)
}
template <typename T>
Node<T>* Tree<T>::getMinNode(Node<T> *root)
{
	while (root->left)
		root = root->left;

	return root;
}



template <typename T>
void Tree<T>::insert(T vl)
{
	Node<T> **curr = &top;
	Node<T> *prev = nullptr;

	while (*curr) {
		prev = *curr;
		Node<T> &node = **curr;
		if (vl < node.data) {
			curr = &node.left;
		}
		else if (vl > node.data) {
			curr = &node.right;
		}
		else {
			return;
		}
	}
	*curr = new Node<T>(vl);
	(*curr)->parent = prev;
}
template <typename T>
void Tree<T>::pop(T vl)
{
	/*
		1. нет детей
		2. 1 ребенок (left or right)
		3. 2 ребенка
		*/
	Node<T> *curr = getNode(vl);

	if (is_empty() || !curr) return;

	if (curr->left == curr->right)
		funck1(curr, vl);
	else if (curr->left && !curr->right)
		funck2(curr, vl);
	else if (!curr->left && curr->right)
		funck3(curr, vl);
	else if (curr->left && curr->right)
		funck4(curr, vl);
}
template <typename T>
void Tree<T>::print(Node<T> *curr)
{
	if (!curr) return;

	static int tabs(0);
	tabs += 5;

	print(curr->left);

	for (int i = 0; i < tabs; ++i)
		std::cout << ' ';
	std::cout << curr->data << '\n';

	print(curr->right);

	tabs -= 5;
	return;
}
template <typename T>
void Tree<T>::outTree()
{
	std::cout << "\n\nRoot:";
	print(top);
	std::cout << std::endl;
}


// Беды реализации:
template <typename T>
void Tree<T>::funck1(Node<T> *curr, T vl)
{
	if (curr->left == curr->right)
	{
		if (curr->parent)							// если есть родитель
		{
			if (vl < curr->parent->data)
				curr->parent->left = nullptr;
			else
				curr->parent->right = nullptr;
			delete curr;
		}
		else {										// если родителя нет (вершина дерева)
			delete curr;
			top = nullptr;
		}
		return;
	}
}
template <typename T>
void Tree<T>::funck2(Node<T> *curr, T vl)
{
	if (curr == top)								// код удаления специально для вершины
	{
		curr->left->parent = nullptr;
		Node<T>* newTop = curr->left;
		delete top;
		top = newTop;
		return;
	}

	if (vl < curr->parent->data)					// если мы наследовались слева
	{
		curr->parent->left = curr->left;
		curr->left->parent = curr->parent;
		delete curr;
	}
	else											// если мы наследовались справа
	{
		curr->parent->right = curr->left;
		curr->left->parent = curr->parent;
		delete curr;
	}
}
template <typename T>
void Tree<T>::funck3(Node<T> *curr, T vl)
{
	if (curr == top)								// код удаления специально для вершины
	{
		curr->right->parent = nullptr;
		Node<T>* newTop = curr->right;
		delete top;
		top = newTop;
		return;
	}

	if (vl < curr->parent->data)					// если мы наследовались слева
	{
		curr->parent->left = curr->right;
		curr->right->parent = curr->parent;
		delete curr;
	}
	else											// если мы наследовались справа
	{
		curr->parent->right = curr->right;
		curr->right->parent = curr->parent;
		delete curr;
	}
}
template <typename T>
void Tree<T>::funck4(Node<T> *curr, T vl)
{
	Node<T> *minNode = getMinNode(curr->right);

	if (curr == top)								// если удаляем вершину, то создаем ей временного родителя
	{
		top->parent = new Node<T>(0);
		top->parent->left = top->parent->right = top;
	}

	if (curr->right->left) {						// если у удаляемого правого ребенка есть дети/ребенок слева

		if (minNode->right)							// ситуация, если у минимального объекта в правой ветке есть еще дети справа
		{
			minNode->parent->left = minNode->right;
			minNode->right->parent = minNode->parent;
		}
		else
		{
			minNode->parent->left = nullptr;
		}

		minNode->parent = curr->parent;
		minNode->left = curr->left;
		minNode->right = curr->right;

		if (vl < curr->parent->data)				// для родителя
			curr->parent->left = minNode;
		else
			curr->parent->right = minNode;

		delete curr;

	}
	else
	{
		if (vl < curr->parent->data)				// для родителя
			curr->parent->left = minNode;
		else
			curr->parent->right = minNode;

		minNode->parent = curr->parent;
		minNode->left = curr->left;
		minNode->right = nullptr;

		delete curr;
	}

	if (top->parent)								// если мы добавили корню дерева временного родителя, то удаляем
	{
		top = minNode;
		delete minNode->parent;
		minNode->parent = nullptr;
	}
}