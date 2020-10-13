#pragma once
#include<iostream>
using namespace std;
#define defaultSize 5
template<class T>
class SeqList
{
public:
	SeqList(int sz = defaultSize) :maxSize(sz), last(0)
	{
		init();
	}
	~SeqList() { delete[]data; }
	bool init();
	int length() { return last; }
	int at(T& x);
	T find(int i);
	T getValue(int i) { return data[i - 1]; }
	bool getData(int i, T& x) {
		if (i > 0 && i <= last + 1) { x = data[i - 1]; return true; }
		else return false;
	}
	bool setData(int i, T& x) {
		if (i > 0 && i <= last + 1) { data[i - 1] = x; return true; }
		else return false;
	}
	bool insert(int i, T& x);
	bool remove(int i);
	bool isEmpty() { return (last == 0) ? true : false; }
	bool isFull() { return (last == maxSize - 1) ? true : false; }
	bool resize();
	bool deleteSize();
	bool append(T& x);
protected:
	T* data;
	int maxSize;
	int last;
};

template<class T>
int SeqList<T>::at(T& x)
{
	for (int i = 0; i <= last; i++)
		if (data[i] == x)return i + 1;
	return 0;
}

template<class T>
T SeqList<T>::find(int i)
{
	return data[i - 1];
}

template<class T>
bool SeqList<T>::resize()
{
	T* newData = new T[maxSize * 2];
	if (newData == nullptr)cout << "分配内存错误";
	T* ptr;
	for (int i = 0; i < last; i++)
		newData[i] = data[i];
	ptr = data;
	data = newData;
	delete[]ptr;
	maxSize = maxSize * 2;
	//cout << "已扩容，当前表最大元素个数：" << maxSize << endl;
	return true;
}

template<class T>
bool SeqList<T>::deleteSize()
{
	if (last > (maxSize / 4))return false;
	T* ptr;
	T* newData = new T[maxSize / 2 + 1];
	if (newData == nullptr)cout << "分配内存错误";
	for (int i = 0; i < last; i++)
		newData[i] = data[i];
	ptr = data;
	data = newData;
	delete[]ptr;
	maxSize = maxSize / 2 + 1;
	//cout << "已减容，当前表最大元素个数：" << maxSize << endl;
	if (last < (maxSize / 4))deleteSize();
	return true;
}

template<class T>
bool SeqList<T>::insert(int i, T& x)
{
	last++;
	if (isFull() == true)resize();
	if (i<0 || i>last) { cout << "插入位置不合理"; return false; }
	for (int j = last; j > i; j--)
		data[j - 1] = data[j - 2];
	data[i - 1] = x;
	return true;
}

template<class T>
bool SeqList<T>::remove(int i)
{
	if (isEmpty() == true) { /*cout << "表空，无法删除";*/return false; }
	if (i<0 || i>last) { /*cout << "删除位置不合理";*/ return false; }
	for (int j = i; j < last; j++)
		data[j - 1] = data[j];
	last--;
	deleteSize();
	return true;
}

template<class T>
bool SeqList<T>::append(T& x)
{
	if (isFull() == true)resize();
	last++;
	data[last - 1] = x;
	//cout << "元素+1" << endl;
	return true;
}


template<class T>
bool SeqList<T>::init()
{
	maxSize = defaultSize;
	T* ptr;
	T* newData = new T[maxSize];
	if (newData == nullptr) { cout << "分配内存错误"; return false; }
	ptr = data;
	data = newData;
	delete[]ptr;
	last = 0;
	return true;
}


