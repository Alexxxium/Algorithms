#pragma once
#include <list>



template<class K, class V>
struct Node
{
	K key;
	V value;

	explicit Node(const K &k, const V &vl): key(k), value(vl) {}

	Node(const Node<K, V> &node): key(node.key), value(node.value) {}

	void operator=(const Node<K, V> &node) {
		key = node.key;
		value = node.value;
	}

	bool operator== (const K &vl) const { return key == vl; }
	auto operator<=>(const K &vl) const { return key <=> vl; }
	bool operator== (const Node<K, V> &node) const { return key == node.key; }
	auto operator<=>(const Node<K, V> &node) const { return key <=> node.key; }
};


template<class K, class V>
class HashTable
{
private:

	typedef std::list<Node<K, V>*> List;

	static int defailtCapacity;
	static float redistCoeff;

	size_t capacity, count;

	List *array;

	size_t Hash(const Node<K, V> *node) const;
	size_t Hash(const K &key)   const;

	void DestroyArray(List*);

	void reHash (const List*, const size_t);
	void reWrite(const List*);

	List::iterator find(const Node<K, V>&, List&);

	

public:

	explicit HashTable(int cpcty = defailtCapacity);
	HashTable(const HashTable&);

	void operator=(const HashTable&);

	~HashTable ()   { DestroyArray(array); }
	size_t size()   { return count; }
	size_t volume() { return capacity; }

	Node<K, V>* find(const K&);

	void reserve(const int);
	void insert (const K&, const V&);
	void erase  (const K&);
	void clear  ();

	void outTable();
};


template<typename K, typename V>
int HashTable<K, V>::defailtCapacity = 10;
template<typename K, typename V>
float HashTable<K, V>::redistCoeff = 0.75;



template<typename K, typename V>
HashTable<K, V>::HashTable(int cpcty): count(0), capacity(cpcty)
{
	if (cpcty < 0) throw 1;
	if (!cpcty) capacity = defailtCapacity;

	array = new std::list<Node<K, V>*>[capacity];
}
template<typename K, typename V>
HashTable<K, V>::HashTable(const HashTable<K, V> &copy):
	count(copy.count),
	capacity(copy.capacity)
{
	array = new List[capacity];

	reWrite(copy.array);
}


template<typename K, typename V>
void HashTable<K, V>::operator=(const HashTable<K, V> &copy)
{
	if (&copy == this) return;

	count = copy.count;
	capacity = copy.capacity;

	DestroyArray(array);
	array = new List[capacity];

	reWrite(copy.array);
}
template<typename K, typename V>
void HashTable<K, V>::DestroyArray(List *arr)
{
	for (size_t i = 0; i < capacity; ++i)
		for (const auto &it : arr[i])
			delete it;
	delete[] arr;
}


template<typename K, typename V>
size_t HashTable<K, V>::Hash(const Node<K, V> *node) const
{
	return Hash(node->key);
}
template<typename K, typename V>
size_t HashTable<K, V>::Hash(const K &key)   const
{
	return (key % capacity);
}


template<typename K, typename V>
void HashTable<K, V>::reHash  (const List *copy, const size_t lenght)
{
	for (int i = 0; i < lenght; ++i)
		for (const auto &it : copy[i])
			array[Hash(it)].push_back(it);
}
template<typename K, typename V>
void HashTable<K, V>::reWrite (const List *copy)
{
	for (int i = 0; i < capacity; ++i)
		for (const auto &it : copy[i])
			array[i].push_back(it);
}
template<typename K, typename V>
void HashTable<K, V>::reserve (const int newCapacity)
{
	if (newCapacity <= capacity) return;
	
	List *tempArr = array;
	size_t tempSz = capacity;

	capacity = newCapacity;
	array = new List[capacity];
	
	reHash(tempArr, tempSz);
}
template<typename K, typename V>
void HashTable<K, V>::insert  (const K &key, const V &value)
{
	Node<K, V> *newData = new Node(key, value);
	array[Hash(key)].push_back(newData);
	
	if (++count * 1.0 / capacity >= redistCoeff)
		reserve(capacity * 2);
}
template<typename K, typename V>
void HashTable<K, V>::erase   (const K &key)
{
	List &ref = array[Hash(key)];
	auto it = find(Node(key, V()), ref);
	
	if (it != ref.end()) {
		ref.erase(it);
		--count;
	}	
}
template<typename K, typename V>
void HashTable<K, V>::clear   ()
{
	DestroyArray(array);
	array = new List[capacity];
	count = 0;
}


template<typename K, typename V>
Node<K, V>* HashTable<K, V>::find(const K &key)
{
	List &ref = array[Hash(key)];

	for (const auto &i : ref)
		if (i->key == key)
			return i;

	return nullptr;
}

template<typename K, typename V>
HashTable<K, V>::List::iterator HashTable<K, V>::find(const Node<K, V> &node, List &list)
{
	
	for (auto i = list.begin(); i != list.end(); ++i)
		if ((*i)->key == node.key)
			return i;

	return list.end();		
}

template<typename K, typename V>
void HashTable<K, V>::outTable()
{
	for (int i = 0; i < capacity; ++i) {
		for (const auto &it : array[i])
			std::cout << '(' << it->key << " ; " << it->value << ")\t";
		std::cout << std::endl;
	}	
}