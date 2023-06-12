#pragma once
#include <iostream>


namespace algs
{
	namespace src
	{
		template<class T>
		struct Node
		{
			Node *left, *right;
			const T key;
			size_t hight;

			explicit Node(const T &vl): key(vl), hight(1) { right = left = nullptr; }
			~Node() = default;

			Node(Node<T>&&) = delete;
			Node(const Node<T>&) = delete;
			void operator = (Node<T>&&) = delete;
			void operator = (const Node<T>&) = delete;
		};
	}


	using src::Node;


	template<class T>
	class AvlTree
	{
	private:

		mutable Node<T> *root;
		mutable size_t lenght;


	public:

		AvlTree(): root(nullptr), lenght(0) {};

		AvlTree(AvlTree&&) noexcept;
		AvlTree(const AvlTree&) noexcept;

		void operator = (const AvlTree&) noexcept;
		void operator = (AvlTree&&) noexcept;

		~AvlTree() noexcept;


	private:

		inline void fixedHight(Node<T>*) const noexcept;
		void pushNewTree(const Node<T>*) const noexcept;
		void DestroyNode(const Node<T>*) const noexcept;
		void print(const Node<T>*) const noexcept;


		Node<T>* removeRoot();
		Node<T>* getMin(Node<T>*);
		Node<T>* removeMin(Node<T>*);
		Node<T>* removeNode(Node<T>*, const T&);


		Node<T>* insert(const T&, Node<T>*) const noexcept;


		Node<T>* leftRotate(Node<T>*) const;
		Node<T>* rightRotate(Node<T>*) const;
		Node<T>* balance(Node<T>*) const;


		int balanceFact(Node<T> *node) const noexcept { return (getHight(node->right) - getHight(node->left)); }
		size_t getHight(Node<T> *node) const noexcept { return node ? node->hight : 0; }


	public:

		void insert(const T&) noexcept;
		void remove(const T&);

		const T& find(const T&) const noexcept;


		void outTree() const noexcept;

		bool isEmpty() const noexcept { return root == nullptr; }
		size_t size()  const noexcept { return lenght; }
	};
}

#include "AvlTree.inl"
