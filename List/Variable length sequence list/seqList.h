#pragma once
#include<iostream>
using namespace std;

template<class T>
class SeqList
{
public:
	SeqList(int sz);
	~SeqList() { delete[]data; }
	bool init();//初始化顺序表
	int length() { return last ; }
	int at(T& x);//输出特定元素的位置--O(n)
	T find(int i);//输出第i位置的元素--O(n)
	bool setData(int i, T& x) {
		//更改第i位的元素--O(n)
		if (i > 0 && i <= last + 1) { data[i - 1] = x; return true; }
		else return false;
	}
	bool insert(int i, T x); //在第i个位置插入元素--O(n)
	bool remove(int i);//移除第1个位置的元素--O(n)
	bool isEmpty() { return (last == 0) ? true : false; }//判定顺序表是否为空
	bool isFull() { return (last == maxSize - 1) ? true : false; }//判定顺序表是否为满
	bool resize(); //调整容量增大--O(n)
	bool deleteSize();//调整容量减小--O(n)
	bool append(T x);//在最后元素后追加新元素--O(1)
	void input();//建立顺序表
	void print();//遍历顺序表并输出--O(n)
protected:
	T* data;
	int maxSize;
	int last;
};
