#ifndef ARRAYOFPOINTERS
#define ARRAYOFPOINTERS
#include <iostream>
constexpr auto MAXSIZE=100;
template <class T>
class ArrayofPointers
{
protected:
	T* Array;
	int size;
public:

	ArrayofPointers();
	~ArrayofPointers();
	int GetSize();
	bool AddtoArray(T data);
	T* RemovefromArray(int index);
	T* getItem(int index);
	bool isEmpty();
	bool check(int index);

};
 template <class T>
 bool ArrayofPointers<T>::check(int index) {
	 if (Array[index] == nullptr) {
		 std::cout << "Element not in array!\n";
		 return false;
	 }
	 else {
		 std::cout << "element in array\n"; 
		 return true;
	 }
 }
	template <class T>
	ArrayofPointers<T>::ArrayofPointers() {
		Array = new T [MAXSIZE];
		size = 0;
	}
	template<class T>
	ArrayofPointers<T>::~ArrayofPointers() {
		for (int i = 0; i < size; i++) {
			delete Array[i];
		}
		delete[]Array;
	}
	template <class T>
	int ArrayofPointers<T>::GetSize() {
		return size;
	}
	template<class T>
	T* ArrayofPointers<T>::getItem(int index) {
		T* item = &Array[index];
		return item;
	}
	template <class T>
	bool ArrayofPointers<T>::AddtoArray(T data) {
		if (size == MAXSIZE) return false;
		data = Array[size+1];
		size++; return true;
	}
	template <class T>
	T* ArrayofPointers<T>::RemovefromArray(int index) {
		if (size == 0 || index > MAXSIZE|| index>size) {
			T* removed = NULL;
			return removed;
		}
		T* removed =&Array[index];
		Array[index] = Array[size];
		size--;
		return removed;
	}
	template <typename T>
	bool ArrayofPointers<T>::isEmpty() {
		if (size == 0) return true;
		else return false;
	}
#endif