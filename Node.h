
#ifndef _NODE
#define _NODE
template <typename T>
class Node
{
private:
	T item; // A data item
	Node<T>* next; // Pointer to next node
	Node<T>* pre;
public:
	Node();
	Node(const T& r_Item);
	Node(const T& r_Item, Node<T>* nextNodePtr);
	Node(const T& r_Item, Node<T>* nextNodePtr, Node<T>* preNodePtr);
	void setItem(const T& r_Item);
	void setNext(Node<T>* nextNodePtr);
	void setPre(Node<T>* preNodePtr);
	T getItem() const;
	Node<T>* getNext() const;
	Node<T>* getPrevious()const;
}; // end Node
#endif

template < typename T>
Node<T>::Node()
{
	next = nullptr;
	pre = nullptr;
}

template < typename T>
Node<T>::Node(const T& r_Item)
{
	item = r_Item;
	next = nullptr;
	pre = nullptr;
}

template < typename T>
Node<T>::Node(const T& r_Item, Node<T>* nextNodePtr)
{
	item = r_Item;
	next = nextNodePtr;
}
template < typename T>
Node<T>::Node(const T& r_Item, Node<T>* nextNodePtr,Node<T>* preNodePtr)
{
	item = r_Item;
	next = nextNodePtr;
	pre = preNodePtr;
}

template < typename T>
void Node<T>::setItem(const T& r_Item)
{
	item = r_Item;
}

template < typename T>
void Node<T>::setNext(Node<T>* nextNodePtr)
{
	next = nextNodePtr;
}
template < typename T>
void Node<T>::setPre(Node<T>* preNodePtr)
{
	pre = preNodePtr;
}
template < typename T>
T Node<T>::getItem() const
{
	return item;
}

template < typename T>
Node<T>* Node<T>::getNext() const
{
	return next;
}
template <typename T>
Node<T>* Node<T>::getPrevious()const {
	return pre;
}