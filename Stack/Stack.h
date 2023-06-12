#pragma once
#include <iostream>

namespace algs
{
	namespace src
	{
		template<typename T>
		struct Node
		{
			T data;
			Node *next;

			explicit Node(const T &vl) : next(nullptr), data(vl) {}

			Node(Node&&) = delete;
			Node(const Node&) = delete;
			void operator = (Node&&) = delete;
			void operator = (const Node&) = delete;
		};
	}



	using src::Node;


	template <class T>
	class Stack
	{
	private:

		Node<T> *Top;
		int lenght;

		void setNodes(const Node<T>*) noexcept;


	public:

		Stack() noexcept : Top(nullptr), lenght(0) {}

		Stack(Stack<T>&&) noexcept;
		Stack(const Stack<T>&) noexcept;

		void operator = (Stack<T>&&) noexcept;
		void operator = (const Stack<T>&) noexcept;

		~Stack() noexcept;


		bool is_empty() const noexcept { return Top == nullptr; }
		int size() const noexcept { return lenght; }

		inline const T& top() const;


		void push(const T&) noexcept;
		void remove() noexcept;


		void outStack() const noexcept;
	};
}

#include "Stack.inl"
