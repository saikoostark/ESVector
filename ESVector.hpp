#ifndef ESVECTOR_HPP
#define ESVECTOR_HPP

#include <iostream>
#include <initializer_list>

using namespace std;

template <class t>
class ESVector
{
  private:
	t *arr;
	int _size;
	int _capacity;

  public:
 
	using iterator = t*;
	
	ESVector(initializer_list<t> another);

	ESVector(int n);

	ESVector(t *, int n); //eslam

	ESVector(const ESVector<t> &another);

	~ESVector() {} //eslam

	ESVector<t> &operator=(const ESVector &another);

	ESVector &operator=(const ESVector &&); //eslam

	int push_back(t value); //eslam

	t pop_back();

	void erase(iterator it);

	void erase(iterator it1, iterator it2); //eslam

	void clear();

	void insert(iterator it, t al); //saikoo-empty

	iterator begin(); //eslam

	iterator end(); //eslam

	bool operator==(const ESVector<t> &another); //eslam

	bool operator<(const ESVector<t> &another);

	int size();

	int capacity(); //eslam

	int resize(); //eslam

	bool empty();

	t &operator[](int item); //eslam

	template <class u>
	friend ostream &operator<<(ostream &out, ESVector<u> another);
};

template <class u>
ostream &operator<<(ostream &out, ESVector<u> another)
{
	for (int i = 0; i < another._size; i++)
	{
		out << another.arr[i];
		if (i != another._size - 1)
			out << " ";
	}
	return out;
}

template <class t>
ESVector<t>::ESVector(initializer_list<t> another)
{
	this->_size = another.size();
	this->_capacity = this->_size * 2;

	arr = new t[_capacity];

	auto it = another.begin();
	for (int i = 0; i < _size; i++)
	{
		arr[i] = *(it++);
	}
}


template <class t>
ESVector<t>::ESVector(int n)
{
	_size = n;
	_capacity = n * 2;
	arr = new t[_capacity];

	for (int i = 0; i < _size; i++)
		arr[i] = 0;
}


template <class t>
ESVector<t>::ESVector(const ESVector &another)
{
	this->_size = another._size;
	this->_capacity = another._capacity;
	arr = new t[_capacity];

	for (int i = 0; i < _size; i++)
		arr[i] = another.arr[i];
}


template <class t>
ESVector<t> &ESVector<t>::operator=(const ESVector<t> &another)
{
	delete[] arr;

	this->_size = another._size;
	this->_capacity = another._capacity;
	arr = new t[_capacity];

	for (int i = 0; i < _size; i++)
		arr[i] = another.arr[i];

	return *this;
}


template <class t>
t ESVector<t>::pop_back()
{
	if (_size != 0)
	{
		return arr[--_size];
	}
}


template <class t>
void ESVector<t>::clear()
{
	_size = 0;
}


template <class t>
bool ESVector<t>::operator<(const ESVector<t> &another)
{
	if (this->_size >= another._size)
		return 0;

	for (int i = 0; i < _size; i++)
	{
		if (arr[i] >= another.arr[i])
			return 0;
	}

	return 1;
}


template <class t>
int ESVector<t>::size()
{
	return this->_size;
}


template <class t>
bool ESVector<t>::empty()
{
	return (_size == 0);
}


template <class t>
void ESVector<t>::erase(ESVector<t>::iterator it){
	
	if(it >= arr+_size || it < arr)
	return;
	
	for(int i = (it - arr) ; i < _size - 1 ; i++)
	arr[i] = arr[i+1];
	
	_size--;
}


template<class t >
void ESVector<t>::insert(ESVector<t>::iterator it, t val){
	
	int len = (it - arr);
	if(len < 0 )
	return;
	
	int old_size = _size;
	int new_size = max(len+1 , _size+1);
	if((len+1) > _capacity){
		t *temp = new t[_size];
		for(int i = 0 ; i < _size ; i++)
	 	temp[i] = arr[i]; 
		delete [] arr;
		_size = (len+1);
		_capacity = _size * 2;
		arr = new t[_capacity];
		for(int i = 0 ; i < old_size ; i++)
		 arr[i] = temp[i];
		 new_size = len+1;
	}
		for(int i = _size ; i > len ; i--)
		arr[i] = arr[i-1];
		arr[len] = val;
		_size = new_size;
	
	
}



//keep or remove 
template <class t>
int ESVector<t>::capacity(){
	return _capacity;
}

template <class t>
t* ESVector<t>::begin(){
	return arr;
}

template <class t>
t* ESVector<t>:: end(){
	return arr+_size;
}

template <class t>
t & ESVector<t>:: operator[](int item){
	return arr[item];		
}
//

#endif
