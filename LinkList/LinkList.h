
#pragma once
#include <iostream>


namespace algs
{
	namespace src
	{
		template <class T>
		struct Node
		{
			T data;
			Node *prev, *next;

			explicit Node(const T &vl) : data(vl) { prev = next = nullptr; }

			Node(Node&&) = delete;
			Node(const Node&) = delete;
			void operator = (Node&&) = delete;
			void operator = (const Node&) = delete;
		};
	}



	using src::Node;

	template <class T>
	class LinkList
	{
	private:

		Node<T> *first, *last;
		int lenght;

		Node<T>* getNode(const int) const;


	public:

		LinkList() : lenght(0) { first = last = nullptr; }

		LinkList(LinkList&&) noexcept;
		LinkList(const LinkList&) noexcept;

		void operator = (LinkList&&) noexcept;
		void operator = (const LinkList&) noexcept;

		~LinkList() noexcept;


		int size() const noexcept { return lenght; }
		bool is_empty() const noexcept { return first == nullptr; }


		T& operator[](const int&);
		const T& operator[](const int&) const;


		void push_front(const T&) noexcept;
		void push_back(const T&) noexcept;
		void pop_front() noexcept;
		void pop_back() noexcept;

		void insert(const int, const T&);
		void pop_insert(const int);

		void outLinkList() const noexcept;
	};
}

#include "LinkList.inl"
