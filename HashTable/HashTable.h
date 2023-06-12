#pragma once
#include <list>

namespace algs
{
	namespace src
	{
		template<class K, class V>
		struct Node
		{
			const K key;
			V value;

			explicit Node(const K &k, const V &vl) noexcept: key(k), value(vl) {}

			Node(const Node<K, V> &node) = default;
			~Node() = default;

			void operator=(const Node<K, V> &node) noexcept;


			bool operator== (const K &vl) const noexcept { return key == vl; }
			auto operator<=>(const K &vl) const noexcept { return key <=> vl; }
			bool operator== (const Node<K, V> &node) const noexcept { return key == node.key; }
			auto operator<=>(const Node<K, V> &node) const noexcept { return key <=> node.key; }


			Node(Node<K, V>&&) = delete;
			void operator= (Node<K, V>&&) = delete;
		};

	}


	using src::Node;


	template<class K, class V>
	class HashTable
	{
	private:

		typedef std::list<Node<K, V>*> List;

		static int defaultCapacity;
		static float redistCoeff;

		size_t capacity, count;
		List *array;


	public:

		explicit HashTable(int cpcty = defaultCapacity);

		void operator=(const HashTable&) noexcept;
		void operator=(HashTable&&) noexcept;

		HashTable(const HashTable&) noexcept;
		HashTable(HashTable&&) noexcept;

		~HashTable() noexcept;


	private:

		List::iterator find(const Node<K, V>&, List&) const noexcept;


		void reHash(const List*, const size_t) noexcept;
		void reWrite(const List*) noexcept;


		inline size_t Hash(const Node<K, V>*) const noexcept;
		inline size_t Hash(const K&) const noexcept;


		void DestroyArray(List*) const noexcept;


	public:

		size_t size() const noexcept { return count; }
		size_t volume() const noexcept { return capacity; }


		Node<K, V>* find(const K&) const noexcept;


		void insert(const K&, const V&) noexcept;
		void reserve(const int) noexcept;
		void erase(const K&) noexcept;
		void clear() noexcept;


		void outTable() const noexcept;
	};
}

#include "HashTable.inl"
