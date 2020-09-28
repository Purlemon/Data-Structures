#pragma once
#include<iostream>
using namespace std;
template<class T>
class DeQueue
{
public:
	DeQueue(int sz=10);//构造函数
	~DeQueue() { delete[]elements; }//析构函数
	bool push(const T& x);//将x插入队头
	T pop();//删除队头并将其返回
	bool inject(const T& x);//将x插入队尾
	T eject();//删除队尾并将其返回
	T getFront();//返回队头
	T getRear();//返回队尾
	bool IsEmpty()const { return(front == rear) ? true : false; }
	//判断双端队列是否为空
	bool IsFull()const { return ((front + 1) % maxSize == rear) ? true : false; }
	//判断双端队列是否已满
private:
	int rear, front;//队尾与队头指针
	T* elements;//存放双端队列元素的数组
	int maxSize;//双端队列最大可能的元素个数
};
