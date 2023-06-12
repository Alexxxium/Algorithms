
namespace algs
{
	template<typename T>
	Node<T>* LinkList<T>::getNode(const int index) const
	{
		if (is_empty() || index < 0 || index >= lenght)
			throw 1;


		if (index > lenght / 2)
		{
			Node<T> *ptr = last;
			for (int i = 0; i < (lenght - 1 - index); ++i)
				ptr = ptr->prev;

			return ptr;
		}
		else
		{
			Node<T> *ptr = first;
			for (int i = 0; i < index; ++i)
				ptr = ptr->next;

			return ptr;
		}
	}




	template<typename T>
	LinkList<T>::LinkList(const LinkList<T> &list) noexcept :
		lenght(0)
	{
		first = last = nullptr;

		for (int i = 0; i < list.lenght; ++i)
			push_back(list[i]);
	}
	template<typename T>
	LinkList<T>::LinkList(LinkList<T> &&list) noexcept :
		first(list.first),
		last(list.last),
		lenght(list.lenght)
	{
		list.first = list.last = nullptr;
		list.lenght = 0;
	}

	template<typename T>
	void LinkList<T>::operator = (const LinkList<T> &list) noexcept
	{
		if (this == &list) return;

		auto *ptr = first;
		while (ptr)
		{
			auto buff = ptr->next;
			delete ptr;
			ptr = buff;
		}

		lenght = 0;
		first = last = nullptr;

		for (int i = 0; i < list.lenght; ++i)
			push_back(list[i]);
	}
	template<typename T>
	void LinkList<T>::operator = (LinkList<T> &&list) noexcept
	{
		if (this == &list) return;
					
		auto *ptr = first;
		while (ptr)
		{
			auto buff = ptr->next;
			delete ptr;
			ptr = buff;
		}

		first = list.first;
		last = list.last;
		lenght = list.lenght;

		list.last = list.first = nullptr;
		list.lenght = 0;
	}

	template<typename T>
	LinkList<T>::~LinkList() noexcept
	{
		Node<T> *ptr = first;
		Node<T> *buff;
		while (ptr)
		{
			buff = ptr;
			ptr = ptr->next;
			delete buff;
		}
	}




	template<typename T>
	T& LinkList<T>::operator[] (const int &index)
	{
		return getNode(index)->data;
	}
	template<typename T>
	const T& LinkList<T>::operator[] (const int &index) const
	{
		return getNode(index)->data;
	}




	template<typename T>
	void LinkList<T>::push_front(const T &vl) noexcept
	{
		Node<T> *newData = new Node<T>(vl);

		if (is_empty())
			first = last = newData;
		else
		{
			first->prev = newData;
			newData->next = first;
			first = newData;
		}
		++lenght;
	}
	template<typename T>
	void LinkList<T>::push_back(const T &vl) noexcept
	{
		Node<T> *newData = new Node<T>(vl);

		if (is_empty())
			first = last = newData;
		else
		{
			last->next = newData;
			newData->prev = last;
			last = newData;
		}
		++lenght;

	}
	template<typename T>
	void LinkList<T>::pop_front() noexcept
	{
		if (is_empty())
			return;

		Node<T> *buff = first->next;

		delete first;
		if (!buff)
			first = last = nullptr;
		else
		{
			first = buff;
			first->prev = nullptr;
		}


		--lenght;
	}
	template<typename T>
	void LinkList<T>::pop_back() noexcept
	{
		if (is_empty())
			return;

		Node<T> *buff = last->prev;

		delete last;
		if (!buff)
			last = first = nullptr;
		else
		{
			last = buff;
			last->next = nullptr;
		}

		--lenght;
	}
	template<typename T>
	void LinkList<T>::insert(const int index, const T &vl)
	{
		Node<T> *indexNode = getNode(index);

		if (index == 0)
		{
			push_front(vl);
			return;
		}

		Node<T> *newData = new Node<T>(vl);

		Node<T> *buff = indexNode->prev;

		buff->next = newData;
		newData->prev = buff;
		newData->next = indexNode;
		indexNode->prev = newData;

		++lenght;
	}
	template<typename T>
	void LinkList<T>::pop_insert(const int index)
	{
		Node<T> *del = getNode(index);

		if (index == 0)
		{
			pop_front();
			return;
		}
		if (index == lenght - 1)
		{
			pop_back();
			return;
		}

		del->prev->next = del->next;
		del->next->prev = del->prev;
		delete del;

		--lenght;
	}




	template<typename T>
	void LinkList<T>::outLinkList() const noexcept
	{
		int it(0);
		std::cout << "\n";

		if (is_empty())
		{
			std::cout << "List is empty!\n\n";
			return;
		}
		Node<T> *ptr = first;
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