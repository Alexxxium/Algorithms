#pragma once
#include <queue>


namespace algs
{
	namespace src
	{
		template <class T>
		struct Node
		{
			const T data;
			Node *left, *right, *parent;

			explicit Node(const T &vl): data(vl)
			{
				parent = left = right = nullptr;
			}

			Node(Node&&) = delete;
			Node(const Node&) = delete;
			void operator= (Node&) = delete;
			void operator= (const Node&) = delete;
		};
	}



	using src::Node;

	template<class T>
	class Tree
	{
	private:

		Node<T> *top;

		void  DestroyNode(Node<T>*) noexcept;
		Node<T>* getNode(const T&) noexcept;
		Node<T>* getMinNode(Node<T>*);
		void print(Node<T>*) const noexcept;

		// Беды реализации
		void funck1(const Node<T>*, T);
		void funck2(Node<T>*, T);
		void funck3(Node<T>*, T);
		void funck4(Node<T>*, T);


		Tree(Tree<T>&&) = delete;
		Tree(const Tree<T>&) = delete;
		void operator = (Tree<T>&&) = delete;
		void operator = (const Tree<T>&) = delete;


	public:

		Tree(): top(nullptr) {}
		~Tree() noexcept;


		bool is_empty() const noexcept { return top == nullptr; }

		void insert(const T&) noexcept;
		void remove(const T &vl);


		void outTree() const noexcept;
	};



	template <typename T>
	void Tree<T>::DestroyNode(Node<T> *node) noexcept
	{
		if (node) {
			DestroyNode(node->left);
			DestroyNode(node->right);
			delete node;
		}
	}


	template <typename T>
	Node<T>* Tree<T>::getNode(const T &vl) noexcept
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
		if (!root) throw 1;

		while (root->left)
			root = root->left;

		return root;
	}



	template<class T>
	inline Tree<T>::~Tree() noexcept
	{
		DestroyNode(top);
	}

	template <typename T>
	void Tree<T>::insert(const T &vl) noexcept
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
	void Tree<T>::remove(const T &vl)
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
	void Tree<T>::print(Node<T> *curr) const noexcept
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
	void Tree<T>::outTree() const noexcept
	{
		std::cout << "\n\nRoot:";
		print(top);
		std::cout << std::endl;
	}


	template <typename T>
	void Tree<T>::funck1(const Node<T> *curr, T vl)
	{
		if (curr->left == curr->right)
		{
			if (curr->parent)
			{
				if (vl < curr->parent->data)
					curr->parent->left = nullptr;
				else
					curr->parent->right = nullptr;
				delete curr;
			}
			else {
				delete curr;
				top = nullptr;
			}
			return;
		}
	}
	template <typename T>
	void Tree<T>::funck2(Node<T> *curr, T vl)
	{
		if (curr == top)
		{
			curr->left->parent = nullptr;
			Node<T>* newTop = curr->left;
			delete top;
			top = newTop;
			return;
		}

		if (vl < curr->parent->data)
		{
			curr->parent->left = curr->left;
			curr->left->parent = curr->parent;
			delete curr;
		}
		else
		{
			curr->parent->right = curr->left;
			curr->left->parent = curr->parent;
			delete curr;
		}
	}
	template <typename T>
	void Tree<T>::funck3(Node<T> *curr, T vl)
	{
		if (curr == top)
		{
			curr->right->parent = nullptr;
			Node<T>* newTop = curr->right;
			delete top;
			top = newTop;
			return;
		}

		if (vl < curr->parent->data)
		{
			curr->parent->left = curr->right;
			curr->right->parent = curr->parent;
			delete curr;
		}
		else
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

		if (curr == top)
		{
			top->parent = new Node<T>(0);
			top->parent->left = top->parent->right = top;
		}

		if (curr->right->left) {

			if (minNode->right)
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

			if (vl < curr->parent->data)
				curr->parent->left = minNode;
			else
				curr->parent->right = minNode;

			delete curr;

		}
		else
		{
			if (vl < curr->parent->data)
				curr->parent->left = minNode;
			else
				curr->parent->right = minNode;

			minNode->parent = curr->parent;
			minNode->left = curr->left;
			minNode->right = nullptr;

			delete curr;
		}

		if (top->parent)
		{
			top = minNode;
			delete minNode->parent;
			minNode->parent = nullptr;
		}
	}
}
