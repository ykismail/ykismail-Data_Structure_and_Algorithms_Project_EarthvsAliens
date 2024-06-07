#include <iostream>

/*This is a program that implements the queue abstract data type using a linked list.
The queue is implemented as a chain of linked nodes that has two pointers,
a frontPtr pointer for the front of the queue and a backPtr pointer for the back of the queue.
*/

/*

				The Node: item of type T and a "next" pointer
					-------------
					| item| next | --->
					-------------
General Queue case:

				 frontPtr																backPtr
					\											   						/
					 \											  					   /
					------------- 	  ------------- 	  ------------- 	  -------------
					| item| next |--->| item| next |--->  | item| next |--->  | item| next |---> NULL
					------------- 	  ------------- 	  ------------- 	  -------------

Empty Case:

				 frontptr	 backptr
						\	 /
						 \	/
					---- NULL ------


Single Node Case:
				 frontPtr	 backPtr
					\		/
					 \	   /
					-----------
					|item| next| -->NULL
					-----------

*/

#ifndef LINKED_QUEUE_
#define LINKED_QUEUE_

#include "Node.h"
#pragma once


template <typename T>
class LinkedQueue
{
protected:
	Node<T>* backPtr;
	Node<T>* frontPtr;
public:
	LinkedQueue();
	bool isEmpty() const;
	bool enqueue(const T& newEntry);
	bool dequeue(T& frntEntry);
	bool peek(T& frntEntry)  const;
	bool insertfirst(const T& newEntry);
	bool removeend(T&backEntry);
	~LinkedQueue();
	Node<T>* GetfrontPtr();
	Node<T>* GetbackPtr();
};
/////////////////////////////////////////////////////////////////////////////////////////

/*
Function: Queue()
The constructor of the Queue class.

*/

template <typename T>
LinkedQueue<T>::LinkedQueue()
{
	backPtr = nullptr;
	frontPtr = nullptr;

}
/////////////////////////////////////////////////////////////////////////////////////////

/*
Function: isEmpty
Sees whether this queue is empty.

Input: None.
Output: True if the queue is empty; otherwise false.
*/
template <typename T>
bool LinkedQueue<T>::isEmpty() const
{
	return (frontPtr == nullptr);
}

/////////////////////////////////////////////////////////////////////////////////////////

/*Function:enqueue
Adds newEntry at the back of this queue.

Input: newEntry .
Output: True if the operation is successful; otherwise false.
*/
template <class T>
Node<T>* LinkedQueue<T>::GetfrontPtr() {
	return frontPtr;
}
template <class T>
Node<T>* LinkedQueue<T>::GetbackPtr() {
	return backPtr;
}
template <typename T>
bool LinkedQueue<T>::enqueue(const T& newEntry)
{
	Node<T>* newNodePtr = new Node<T>(newEntry);
	// Insert the new node
	if (isEmpty())	//special case if this is the first node to insert
		frontPtr = newNodePtr; // The queue is empty
	else
		backPtr->setNext(newNodePtr); // The queue was not empty

	backPtr = newNodePtr; // New node is the last node now
	return true;
} // end enqueue
template <typename T>
bool LinkedQueue<T>::insertfirst(const T& newEntry) {
	Node<T>* newNodePtr = new Node<T>(newEntry);
	// Insert the new node
	if (isEmpty())	//special case if this is the first node to insert
		backPtr = newNodePtr; // The queue is empty
	else
		newNodePtr->setNext(frontPtr); // The queue was not empty

	frontPtr = newNodePtr; // New node is the first node now
	return true;
}
	/*Node<T>* newnode = new Node<T>;
	if (frontPtr == NULL) {
		frontPtr = backPtr = newnode;
	}
	else {
		newnode->setNext(frontPtr);
		frontPtr = newnode;
	}
	return true;*/

template <typename T>
bool LinkedQueue<T>::removeend(T& backEntry)
{
	if (isEmpty()) {
		std::cout << "ERROR" << std::endl;
		return false;
	}



	if (frontPtr == backPtr) {

		frontPtr = backPtr = nullptr;
	}
	Node<T>* currnode = frontPtr;
	while (currnode->getNext() != backPtr) {
		currnode = currnode->getNext();
	}
	delete backPtr;
	backPtr = currnode;
	currnode->getNext() = nullptr;
	return true;
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////

/*Function: dequeue
Removes the front of this queue. That is, removes the item that was added
earliest.

Input: None.
Output: True if the operation is successful; otherwise false.
*/

template <typename T>
bool LinkedQueue<T>::dequeue(T& frntEntry)
{
	if (isEmpty())
		return false;

	Node<T>* nodeToDeletePtr = frontPtr;
	frntEntry = frontPtr->getItem();
	frontPtr = frontPtr->getNext();
	// Queue is not empty; remove front
	if (nodeToDeletePtr == backPtr)	 // Special case: last node in the queue
		backPtr = nullptr;

	// Free memory reserved for the dequeued node
	delete nodeToDeletePtr;

	return true;
}



/////////////////////////////////////////////////////////////////////////////////////////

/*
Function: peek
copies the front of this queue to the passed param. The operation does not modify the queue.

Input: None.
Output: The front of the queue.
*/

template <typename T>
bool LinkedQueue<T>::peek(T& frntEntry) const
{
	if (isEmpty())
		return false;

	frntEntry = frontPtr->getItem();
	return true;

}
///////////////////////////////////////////////////////////////////////////////////

template <typename T>
LinkedQueue<T>::~LinkedQueue()
{
	//Note that the cout statements here is just for learning purpose
	//They should be normally removed from the destructor
	//std::cout << "\nStarting LinkedQueue destructor...";
	//std::cout << "\nFreeing all nodes in the queue...";

	//Free all nodes in the queue
	T temp;
	while (dequeue(temp));

	//std::cout << "\n Is LinkedQueue Empty now?? ==> " << std::boolalpha << isEmpty();
	//std::cout << "\nEnding LinkedQueue destructor..." << std::endl;
} 
#endif