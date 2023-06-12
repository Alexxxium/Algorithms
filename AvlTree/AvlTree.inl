
namespace algs
{
	template<typename T>
	void AvlTree<T>::DestroyNode(const Node<T> *node) const noexcept
	{
		if (!node) return;
		DestroyNode(node->left);
		DestroyNode(node->right);
		delete node;
		//node = nullptr;
	}

	template<typename T>
	void AvlTree<T>::pushNewTree(const Node<T> *node) const noexcept
	{
		if (!node) return;
		root = insert(node->key, root);
		++lenght;
		pushNewTree(node->left);
		pushNewTree(node->right);
	}

	template<typename T>
	AvlTree<T>::AvlTree(const AvlTree<T> &tree) noexcept
	{
		DestroyNode(root);
		pushNewTree(tree.root);
	}

	template<typename T>
	AvlTree<T>::AvlTree(AvlTree<T> &&tree) noexcept: lenght(tree.lenght)
	{
		DestroyNode(root);
		root = tree.root;
		tree.root = nullptr;
	}

	template<typename T>
	void AvlTree<T>::operator = (const AvlTree<T> &tree) noexcept
	{
		if (this == &tree) return;

		DestroyNode(root);
		pushNewTree(tree.root);
	}

	template<typename T>
	void AvlTree<T>::operator = (AvlTree<T> &&tree) noexcept
	{
		if (this == &tree) return;

		DestroyNode(root);
		root = tree.root;
		tree.root = nullptr;
	}

	template<typename T>
	AvlTree<T>::~AvlTree() noexcept
	{
		DestroyNode(root);
	}


	template<typename T>
	void AvlTree<T>::print(const Node<T> *curr) const noexcept
	{
		if (!curr) return;

		static int tabs(0);
		tabs += 5;

		print(curr->left);

		for (int i = 0; i < tabs; ++i)
			std::cout << ' ';

		std::cout << curr->key << '\n';

		print(curr->right);

		tabs -= 5;
	}
	template<typename T>
	Node<T>* AvlTree<T>::removeRoot()
	{
		if (root->left == root->right)
		{
			delete root;
			root = nullptr;
		}
		else if (root->left && root->right)
		{
			Node<T> *lt = root->left;
			Node<T> *rt = root->right;

			delete root;

			Node<T> *min = getMin(rt);
			min->right = removeMin(rt);
			min->left = lt;

			root = min;

			return balance(root);
		}
		else if (root->left)
		{
			Node<T> *lt = root->left;
			delete root;
			root = lt;
			balance(root);
		}
		else
		{
			Node<T> *rt = root->right;
			delete root;
			root = rt;
			balance(root);
		}
	}
	template<typename T>
	Node<T>* AvlTree<T>::getMin(Node<T> *node)
	{
		if (!node) throw 1;

		while (node->left)
			node = node->left;

		return node;
	}
	template<typename T>
	Node<T>* AvlTree<T>::removeMin(Node<T> *node)
	{
		if (!node) throw 1;

		if (!node->left)
			return node->right;

		node->left = removeMin(node->left);
		return balance(node);
	}
	template<typename T>
	Node<T>* AvlTree<T>::removeNode(Node<T> *node, const T &vl)
	{
		if (!node) return nullptr;


		if (vl < node->key)
			node->left = removeNode(node->left, vl);
		else if (vl > node->key)
			node->right = removeNode(node->right, vl);
		else
		{
			if (node == root)
			{
				removeRoot();
				return nullptr;
			}

			Node<T> *lt = node->left;
			Node<T> *rt = node->right;

			delete node;

			if (!rt) return lt;

			Node<T> *min = getMin(rt);
			min->right = removeMin(rt);
			min->left = lt;

			return balance(min);
		}
		return balance(node);
	}
	template<typename T>
	Node<T>* AvlTree<T>::insert(const T &vl, Node<T> *curr) const noexcept
	{
		if (!curr)
			return new Node<T>(vl);

		if (vl < curr->key)
			curr->left = insert(vl, curr->left);
		else
			curr->right = insert(vl, curr->right);

		return balance(curr);
	}


	template<typename T>
	void AvlTree<T>::fixedHight(Node<T> *node) const noexcept
	{
		size_t l_h = getHight(node->left);
		size_t r_h = getHight(node->right);

		node->hight = (l_h > r_h ? l_h : r_h) + 1;
	}


	template<typename T>
	Node<T>* AvlTree<T>::leftRotate(Node<T> *node) const
	{
		if (!node) throw 1;

		Node<T> *newNode = node->right;
		node->right = newNode->left;
		newNode->left = node;
		if (node == root)
			root = newNode;

		fixedHight(node);
		fixedHight(newNode);

		return newNode;
	}
	template<typename T>
	Node<T>* AvlTree<T>::rightRotate(Node<T> *node) const
	{
		if (!node) throw 1;

		Node<T> *newNode = node->left;
		node->left = newNode->right;
		newNode->right = node;
		if (node == root)
			root = newNode;

		fixedHight(node);
		fixedHight(newNode);

		return newNode;
	}
	template<typename T>
	Node<T>* AvlTree<T>::balance(Node<T> *node) const
	{
		fixedHight(node);

		if (balanceFact(node) == 2)
		{
			if (balanceFact(node->right) < 0)
				node->right = rightRotate(node->right);
			return leftRotate(node);
		}
		if (balanceFact(node) == -2)
		{
			if (balanceFact(node->left) > 0)
				node->left = leftRotate(node->left);
			return rightRotate(node);
		}

		return node;
	}


	template<typename T>
	void AvlTree<T>::insert(const T &vl) noexcept
	{
		root = insert(vl, root);
		++lenght;
	}
	template<typename T>
	void AvlTree<T>::remove(const T &vl)
	{
		removeNode(root, vl);
		--lenght;
	}


	template<typename T>
	const T& AvlTree<T>::find(const T &vl) const noexcept
	{
		Node<T> *curr(root);

		while (curr)
		{
			if (curr->key == vl)
				break;
			if (vl < curr->key)
				curr = curr->left;
			else
				curr = curr->right;
		}
		//if (!curr) throw 1;				
		//return curr->key;

		return curr ? curr->key : T();
	}


	template <typename T>
	void AvlTree<T>::outTree() const noexcept
	{
		if (isEmpty()) {
			std::cout << "\nTree is empty!\n";
			return;
		}

		std::cout << "\n\nRoot:";
		print(root);
		std::cout << "\n" << std::endl;
	}
}
