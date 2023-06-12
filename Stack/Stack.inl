
namespace algs
{
	template<typename T>
	Stack<T>::~Stack() noexcept
	{
		Node<T> *ptr = Top, *del;
		while (ptr)
		{
			del = ptr;
			ptr = ptr->next;
			delete del;
		}
	}



	template<typename T>
	void Stack<T>::setNodes(const Node<T>* node) noexcept
	{
		if (!node) return;
		setNodes(node->next);
		push(node->data);
	}



	template<typename T>
	Stack<T>::Stack(const Stack<T> &stack) noexcept :
		lenght(0)
	{
		setNodes(stack.Top);
	}
	template<typename T>
	Stack<T>::Stack(Stack<T> &&stack) noexcept :
		Top(stack.Top),
		lenght(stack.lenght)
	{
		stack.Top = nullptr;
		stack.lenght = 0;
	}

	template<typename T>
	void Stack<T>::operator = (const Stack<T> &stack) noexcept
	{
		if (this == &stack) return;

		auto *ptr = Top;
		while (ptr)
		{
			auto buff = ptr->next;
			delete ptr;
			ptr = buff;
		}

		lenght = 0;
		setNodes(stack.Top);
	}
	template<typename T>
	void Stack<T>::operator = (Stack<T> &&stack) noexcept
	{
		if (this == &stack) return;

		auto *ptr = Top;
		while (ptr)
		{
			auto buff = ptr->next;
			delete ptr;
			ptr = buff;
		}

		Top = stack.Top;
		lenght = stack.lenght;

		stack.Top = nullptr;
		stack.lenght = 0;
	}



	template<typename T>
	const T& Stack<T>::top() const
	{
		if (is_empty()) throw 1;
		return Top->data;
	}



	template<typename T>
	void Stack<T>::push(const T &vl) noexcept
	{
		Node<T> *newData = new Node<T>(vl);

		if (is_empty())
			Top = newData;
		else
		{
			newData->next = Top;
			Top = newData;
		}

		++lenght;
	}
	template<typename T>
	void Stack<T>::remove() noexcept
	{
		if (is_empty())
			return;

		Node<T>* buff = Top->next;
		delete Top;
		Top = buff;

		--lenght;
	}
	template<typename T>
	void Stack<T>::outStack() const noexcept
	{
		Node<T> *ptr = Top;

		std::cout << '\n';
		if (is_empty())
		{
			std::cout << "Stack is empty!\n\n";
			return;
		}

		int it(0);
		std::cout << "Top ->:\t";

		while (ptr)
		{
			++it;
			std::cout << ptr->data << '\t';
			ptr = ptr->next;
			if (it % 10 == 0)
				std::cout << '\n';
		}
		std::cout << "\n\n" << std::endl;
	}
}