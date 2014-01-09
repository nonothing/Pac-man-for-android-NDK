#ifndef ARRAYLIST_H
#define ARRAYLIST_H
template <class  T>
class List {
private:
	static const int INITIALSIZE = 10;
	static const int EXPANDSIZE = 5;
	int capacity;		// Current list capacity
	int count;			// Number of elements in list
	T* items;			// Array of items in the list
	void expand();		// Expands size of array by EXPANDSIZE
public:
	List ();
	~List () { delete [] items; }
	void append (const T& item);
	void clear () { count = 0; }
	T get (int index) const { return items[index]; }
	void insert (int index, const T& item);
	void remove (int index);
	void set (int index, const T& item) { items[index] = item; }
	int size () const { return count; }
	void traverse (void(*f)(const T&)) const;
	void traverse (void(*f)(T&));
};

template <class T>
List<T>::List () {
	items = new T[INITIALSIZE];
	capacity = INITIALSIZE;
	count = 0;
}

template <class T>
void List<T>::append (const T& item) {
	if (count == capacity)
		expand();
	items[count++] = item;
}

template <class T>
void List<T>::expand () {
	T* tmp = new T[capacity += EXPANDSIZE];
	for (int i = 0; i < count; i++)
		tmp[i] = items[i];
	delete [] items;
	items = tmp;
}

template <class T>
void List<T>::insert (int index, const T& item) {
	if (count == capacity)
		expand();
	for (int i = count - 1; i >= index; i--)
		items[i + 1] = items[i];
	items[index] = item;
	count++;
}

template <class T>
void List<T>::remove (int index) {
	for (int i = index + 1; i < count; i++)
		items[i - 1] = items[i];
	count--;
}

template <class T>
void List<T>::traverse (void(*f)(const T&)) const {
	for (int i = 0; i < count; i++)
		f(items[i]);
}

template <class T>
void List<T>::traverse (void(*f)(T&)) {
	for (int i = 0; i < count; i++)
		f(items[i]);
}

#endif
