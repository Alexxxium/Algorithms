
namespace algs
{
	template<typename K, typename V>
	int HashTable<K, V>::defaultCapacity = 10;
	template<typename K, typename V>
	float HashTable<K, V>::redistCoeff = 0.75;



	template<typename K, typename V>
	void Node<K, V>::operator=(const Node<K, V> &node) noexcept 
	{
		if (this == &node) return;
		key = node.key;
		value = node.value;
	}



	template<typename K, typename V>
	HashTable<K, V>::~HashTable() noexcept
	{
		DestroyArray(array);
	}

	template<typename K, typename V>
	HashTable<K, V>::HashTable(int cpcty): count(0), capacity(cpcty)
	{
		if (cpcty < 0) throw 1;
		if (!cpcty) capacity = defaultCapacity;

		array = new std::list<Node<K, V>*>[capacity];
	}
	template<typename K, typename V>
	HashTable<K, V>::HashTable(const HashTable<K, V> &copy) noexcept:
		count(copy.count)
	{
		DestroyArray(array);
		capacity = copy.capacity;
		array = new List[capacity];

		reWrite(copy.array);
	}

	template<typename K, typename V>
	HashTable<K, V>::HashTable(HashTable<K, V> &&copy) noexcept:
		count(copy.count)
	{
		DestroyArray(array);
		capacity = copy.capacity;
		array = copy.array;

		copy.array = nullptr;
		copy.capacity = 0;
		copy.count = 0;
	}

	template<typename K, typename V>
	void HashTable<K, V>::operator=(const HashTable<K, V> &copy) noexcept
	{
		if (&copy == this) return;

		DestroyArray(array);
		capacity = copy.capacity;
		count = copy.count;
		array = new List[capacity];

		reWrite(copy.array);
	}

	template<typename K, typename V>
	void HashTable<K, V>::operator=(HashTable<K, V> &&copy) noexcept
	{
		if (&copy == this) return;

		DestroyArray(array);
		capacity = copy.capacity;
		count = copy.count;
		array = copy.array;

		copy.array = nullptr;
		copy.capacity = 0;
		copy.count = 0;
	}
	template<typename K, typename V>
	void HashTable<K, V>::DestroyArray(List *arr) const noexcept
	{
		for (size_t i = 0; i < capacity; ++i)
			for (const auto &it : arr[i])
				delete it;
		delete[] arr;
	}




	template<typename K, typename V>
	size_t HashTable<K, V>::Hash(const Node<K, V> *node) const noexcept
	{
		return Hash(node->key);
	}
	template<typename K, typename V>
	size_t HashTable<K, V>::Hash(const K &key) const noexcept
	{
		return ((key + 31)% capacity);
	}



	template<typename K, typename V>
	void HashTable<K, V>::reHash(const List *copy, const size_t lenght) noexcept
	{
		for (int i = 0; i < lenght; ++i)
			for (const auto &it : copy[i])
				array[Hash(it)].push_back(it);
	}
	template<typename K, typename V>
	void HashTable<K, V>::reWrite(const List *copy) noexcept
	{
		for (int i = 0; i < capacity; ++i)
			for (const auto &it : copy[i])
				array[i].push_back(new Node<K, V>(*it));
	}
	template<typename K, typename V>
	void HashTable<K, V>::reserve(const int newCapacity) noexcept
	{
		if (newCapacity <= capacity) return;

		List *tempArr = array;
		size_t tempSz = capacity;

		capacity = newCapacity;
		array = new List[capacity];

		reHash(tempArr, tempSz);
	}
	template<typename K, typename V>
	void HashTable<K, V>::insert(const K &key, const V &value) noexcept
	{
		Node<K, V> *newData = new Node(key, value);
		array[Hash(key)].push_back(newData);

		if (++count * 1.0 / capacity >= redistCoeff)
			reserve(capacity * 2);
	}
	template<typename K, typename V>
	void HashTable<K, V>::erase(const K &key) noexcept
	{
		List &ref = array[Hash(key)];
		auto it = find(Node(key, V()), ref);

		if (it != ref.end()) {
			ref.erase(it);
			--count;
		}
	}
	template<typename K, typename V>
	void HashTable<K, V>::clear() noexcept
	{
		DestroyArray(array);
		array = new List[capacity];
		count = 0;
	}



	template<typename K, typename V>
	Node<K, V>* HashTable<K, V>::find(const K &key) const noexcept
	{
		List &ref = array[Hash(key)];

		for (const auto &i : ref)
			if (i->key == key)
				return i;

		return nullptr;
	}

	template<typename K, typename V>
	HashTable<K, V>::List::iterator HashTable<K, V>::find(const Node<K, V> &node, List &list) const noexcept
	{

		for (auto i = list.begin(); i != list.end(); ++i)
			if ((*i)->key == node.key)
				return i;

		return list.end();
	}

	template<typename K, typename V>
	void HashTable<K, V>::outTable() const noexcept
	{
		for (int i = 0; i < capacity; ++i) {
			for (const auto &it : array[i])
				std::cout << '(' << it->key << " ; " << it->value << ")\t";
			std::cout << std::endl;
		}
	}
}