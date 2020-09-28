#include"DeQueue.h"
#include<iostream>
using namespace std;
template<class T>
DeQueue<T>::DeQueue(int sz) :front(1), rear(0), maxSize(sz)
{
	//建立一个最大具有maxSize个元素的空队列
	elements = new T[maxSize];//创建双端队列空间
}

template<class T>
bool DeQueue<T>::push(const T& x)
{
	//若双端队列不满，则将x插入队头，否则报错
	if (IsFull() == true) { cout << "队列已满，"<<x<<" 未插入队头"<<endl; return false; }
	elements[front] = x;//按队头指针插入
	front = (front + 1) % maxSize;//队头指针+1
	return true;
}

template<class T>
T DeQueue<T>::pop()
{
	//若双端队列不空，则删除队头元素并返回队头元素，否则报错
	T x;
	if (IsEmpty() == true) { cout << "队列为空"<<endl; return false; }
	if (front == 0)front = maxSize - 1;
	else front = (front - 1) % maxSize;//队头指针-1
	x = elements[front];
	return x;//删除成功，返回该元素
}

template<class T>
bool DeQueue<T>::inject(const T& x)
{
	//若双端队列不满，则将x插入队尾，否则报错
	if (IsFull() == true) { cout << "队列已满，"<<x<<" 未插入队尾"<<endl; return false; }
	elements[rear] = x;//按队尾指针插入
	if (rear == 0)rear = maxSize - 1;
	else rear = (rear - 1) % maxSize;//队尾指针-1
	return true;
}

template<class T>
T DeQueue<T>::eject()
{
	//若双端队列不空，则删除队尾元素并返回队尾元素，否则报错
	T x;
	if (IsEmpty() == true) { cout << "队列为空"<<endl; return false; }
	rear = (rear + 1) % maxSize;//队头指针+11
	x = elements[rear];
	return x;//删除成功，返回该元素
}

template<class T>
T DeQueue<T>::getFront()
{
	//若双端队列不空,返回队头元素
	if (IsEmpty() == true) { cout << "队列为空"; return false; }
	return  elements[front];
}

template<class T>
T DeQueue<T>::getRear()
{
	//若双端队列不空,返回队尾元素
	if (IsEmpty() == true) { cout << "队列为空"; return false; }
	return  elements[rear];
}

int main()
{
	DeQueue<int>dequeue(3);
	dequeue.push(1);
	dequeue.push(2);
	dequeue.inject(3);
	dequeue.inject(4);
	cout << dequeue.pop() << endl;
	cout << dequeue.pop() << endl;
	cout << dequeue.eject() << endl;
	cout << dequeue.eject() << endl;
}
