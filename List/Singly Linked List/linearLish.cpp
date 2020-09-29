#include"linearLish.h"
#include<iostream>
using namespace std;
template<class T>
List<T>::List(List<T>& L)
{
	
}

template<class T >
void List<T>::makeEmpty()
{
	LinkNode<T>* q;
	while (first->link != nullptr)
	{
		//逐个删除节点
		q = first->link;
		first->link = q->link;
		delete q;
	}
}

template<class T>
LinkNode<T>* List<T>::Locate(int i)const
{
	// 定位函数。返回表中第i个元素的地址
	if (i < 0)return nullptr;
	LinkNode<T>* current = first; int k = 0;
	while (current != nullptr && k < i) 
	{
		current = current->link; k++;
	}
	return current;
}

template<class T>
bool List<T>::getData(int i, T& x)const
{
	// 取出第i个元素的值
	if (i < 0)return false;
	LinkNode<T>* current = Locate(i);
	if (current == nullptr)return false;
	else { x = current->data; return true; }
}

template<class T>
void List<T>::setData(int i, T& x)
{
	// 用x修改第i个元素的值
	if (i < 0)return;
	LinkNode<T>* current = Locate(i);
	if (current == nullptr)return;
	else current->data = x;
}

template<class T>
bool List<T>::Insert(int i, T& x)
{
	// 在第i个元素后插入x
	LinkNode<T>* current = Locate(i);
	if (current == nullptr)return false;
	LinkNode<T>* newNode = new LinkNode<T>(x);
	newNode->link = current->link;
	current->link = newNode;
	return true;
}

template<class T>
bool List<T>::Remove(int i, T& x)
{
	// 删除第i个元素，x返回该元素的值
	LinkNode<T>* current = Locate(i-1);
	if (current == nullptr || current->link == nullptr)return false;
	LinkNode<T>* del = current->link;
	x = del->data;
	delete del;
	return true;
}

template<class T>
void List<T>::output()
{
	//将单链表中所有数据按逻辑顺序输出
	LinkNode<T>* current = first->link;
	while (current!= nullptr)
	{
		cout << "输出：" << current->data << endl;
		current = current->link;
	}
}

template<class T>
void List<T>::input(T endTag)
{
	//后插法建立单链表，碰到endTag停止输入
	LinkNode<T>* newNode, * last; T val;
	makeEmpty();
	cin >> val; last = first;
	while (val != endTag) {
		newNode = new LinkNode<T>(val);
		last->link = newNode; last = newNode;
		cin >> val;
	}
	last->link = nullptr;
}

int main()
{
	List<int> list(10);
	int i = 0;
	list.input(i);
	list.output();
	int x=114;
	int m = 3;
	list.setData(m, x);
	list.output();
}
