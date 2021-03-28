#pragma once

/**
* @class LinkedList. Implements a double linked list with basic insertion, deletion, and search functions. Requires a type with comparison operators in order to function properly.
*/
template <class T>
class LinkedList {
	
public:
	/**
	* @brief Constructor. 
	*/
	LinkedList() {
		this->m_count = 0;
	}

	/**
	* @brief Constructor.
	* @param data Data that will be placed in the first node of the list.
	*/
	LinkedList(const T& data) {
		this->first = new Node(data);
		this->last = first;
		this->m_count = 1;
	}

	/********** Insertion **********/

	/**
	* @brief Inserts node with specified data and at the designated index. Indices >= the amount of nodes will be placed at the end of the list and indices <= 0 will be placed at the start. Default value is 0.
	* @param data Data that will be inserted into the list.
	* @param index At which index the node should be inserted.
	*/
	void insert(const T& data, int index = 0);

	/**
	* @brief Inserts node with specified data at the start of the list.
	* @param data Data that will be inserted into the list.
	*/
	void insertAtStart(const T& data);

	/**
	* @brief Inserts node with specified data at the end of the list.
	* @param data Data that will be inserted into the list.
	*/
	void insertAtEnd(const T& data);


	/********** Deletion **********/

	/**
	* @brief Removes node at the designated index. Indices >= the amount of nodes will remove the last node of the list and indices <= 0 will remove the first node of the list.
	* @param index The index of the node to be removed from the list.
	*/
	void removeByIndex(int index);

	/**
	* @brief Removes node with the speficied data.
	* @param data Data that should be removed from the list.
	*/
	void removeByData(const T& data);

	/**
	* @brief Removes all nodes from the list.
	*/
	void clear();

	/********** Search **********/

	/**
	* @brief Retrieves the data of the node at the designated index.
	* @param index integer that indicates which node in the list is selected.
	* @returns Object of specified data type.
	*/
	T* findByIndex(int index);

	/**
	* @brief Identifies whether the specified data is contained in the list or not.
	* @params data The data to be checked.
	* @returns True if the list contains the data and False if it does not.
	*/
	bool contains(const T& data);

	/**
	* @brief Returns the amount of nodes in the list.
	* @returns int with the amount of nodes.
	*/
	int count() { return m_count; }

	/**
	* @struct Node.
	* @attribute data Data with specified type.
	* @attribute prev Node* that precedes the current Node* in the list.
	* @attribute next Node* that succeeds the current Node* in the list.
	*/
	struct Node {
		Node() {
			this->data = nullptr;
			this->prev = nullptr;
			this->next = nullptr;
		}

		Node(const T& data) {
			this->data = &data;
			this->prev = nullptr;
			this->next = nullptr;
		}

		bool isValid() {
			return ((this->prev || this->next) && this->data);
		}

		const T* data;
		Node* prev;
		Node* next;
	};

private:
	// First node of the list.
	Node* first;

	// Last node of the list.
	Node* last;

	// Amount of nodes in the list.
	int m_count;

	/**
	* @brief Internal function that finds a node at a designated index. 
	* @param index integer that indicates which node in the list is selected.
	* @returns The node at the designated index.
	*/
	Node* findNodeByIndex(int index) {
		if (index <= 0)
			return first;

		if (index >= m_count)
			return last;

		Node* aux = first->next;
		int i = 1;
		while (aux->next) {
			if (i == index) 
				return aux;

			i++;
		}
	}

	/**
	* @brief Internal function that removes a specified node.
	* @param node The node that should be removed from the list.
	*/
	void removeNode(Node* node) {
		Node* prev = node->prev;
		Node* next = node->next;
		prev->next = next;
		next->prev = prev;
		delete node;
		m_count--;
	}
};

template<class T>
inline void LinkedList<T>::insert(const T& data, int index) {
	Node* newNode = new Node(data);
	if (m_count == 0) {
		this->first = newNode;
		this->last = newNode;
	}
	else {
		
		if (index <= 0) {
			newNode->next = this->first;
			newNode->prev = this->first->prev;
			this->first->prev = newNode;
			this->first = newNode;
		}
		else if (index < m_count) {
			Node* original = findNodeByIndex(index);
			Node* prev = original->prev;
			Node* next = original->next;
			prev->next = newNode;
			newNode->prev = prev;
			newNode->next = original;
			original->prev = newNode;
		}
		else {
			newNode->prev = this->last;
			newNode->next = this->last->next;
			this->last->next = newNode;
			this->last = newNode;
		}
		
	}	
	m_count++;
}

template<class T>
inline void LinkedList<T>::insertAtStart(const T& data) {
	insert(data, 0);
}

template<class T>
inline void LinkedList<T>::insertAtEnd(const T& data) {
	insert(data, m_count);
}

template<class T>
inline void LinkedList<T>::removeByIndex(int index) {
	if (m_count == 0)
		return;

	Node* node = findNodeByIndex(index);
	removeNode(node);
}

template<class T>
inline void LinkedList<T>::removeByData(const T& data) {
	if (m_count == 0)
		return;

	Node* node = findByData(data);
	removeNode(node);
}

template<class T>
inline void LinkedList<T>::clear() {
	if (m_count == 0) 
		return;

	while (m_count != 0) {
		removeByIndex(0);
	}
}

template<class T>
inline T* LinkedList<T>::findByIndex(int index) {
	Node* node = findNodeByIndex(index);
	return node ? node->data : nullptr;
}

template<class T>
inline bool LinkedList<T>::contains(const T& data) {
	if (!data)
		return false;

	if (m_count == 0) {
		return false;
	}

	Node* aux = first;
	while (aux) {
		if ((aux->data) && data == aux->data)
			return true;

		aux = aux->next;
	}

	return false;
}