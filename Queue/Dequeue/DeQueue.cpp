#include"DeQueue.h"
#include<iostream>
using namespace std;
template<class T>
DeQueue<T>::DeQueue(int sz) :front(1), rear(0), maxSize(sz)
{
	//����һ��������maxSize��Ԫ�صĿն���
	elements = new T[maxSize];//����˫�˶��пռ�
}

template<class T>
bool DeQueue<T>::push(const T& x)
{
	//��˫�˶��в�������x�����ͷ�����򱨴�
	if (IsFull() == true) { cout << "����������"<<x<<" δ�����ͷ"<<endl; return false; }
	elements[front] = x;//����ͷָ�����
	front = (front + 1) % maxSize;//��ͷָ��+1
	return true;
}

template<class T>
T DeQueue<T>::pop()
{
	//��˫�˶��в��գ���ɾ����ͷԪ�ز����ض�ͷԪ�أ����򱨴�
	T x;
	if (IsEmpty() == true) { cout << "����Ϊ��"<<endl; return false; }
	if (front == 0)front = maxSize - 1;
	else front = (front - 1) % maxSize;//��ͷָ��-1
	x = elements[front];
	return x;//ɾ���ɹ������ظ�Ԫ��
}

template<class T>
bool DeQueue<T>::inject(const T& x)
{
	//��˫�˶��в�������x�����β�����򱨴�
	if (IsFull() == true) { cout << "����������"<<x<<" δ�����β"<<endl; return false; }
	elements[rear] = x;//����βָ�����
	if (rear == 0)rear = maxSize - 1;
	else rear = (rear - 1) % maxSize;//��βָ��-1
	return true;
}

template<class T>
T DeQueue<T>::eject()
{
	//��˫�˶��в��գ���ɾ����βԪ�ز����ض�βԪ�أ����򱨴�
	T x;
	if (IsEmpty() == true) { cout << "����Ϊ��"<<endl; return false; }
	rear = (rear + 1) % maxSize;//��ͷָ��+11
	x = elements[rear];
	return x;//ɾ���ɹ������ظ�Ԫ��
}

template<class T>
T DeQueue<T>::getFront()
{
	//��˫�˶��в���,���ض�ͷԪ��
	if (IsEmpty() == true) { cout << "����Ϊ��"; return false; }
	return  elements[front];
}

template<class T>
T DeQueue<T>::getRear()
{
	//��˫�˶��в���,���ض�βԪ��
	if (IsEmpty() == true) { cout << "����Ϊ��"; return false; }
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
