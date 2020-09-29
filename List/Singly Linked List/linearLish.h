#pragma once
template<class T>
struct LinkNode// 链表结点类的定义
{
	T data;// 数据域
	LinkNode<T>* link;// 链指针域
	LinkNode(LinkNode<T>* ptr = nullptr) { link = ptr; }
	// 仅初始化指针成员的构造函数  
	LinkNode(const T& item, LinkNode<T>* ptr = nullptr)
	{
		data = item; link = ptr;
	}
	// 初始化数据与指针成员的构造函数
};

template<class T>
class List
{
public:
	List() { first = new LinkNode<T>; }// 构造函数
	List(const T& x) { first = new LinkNode<T>(x); }// 构造函数
	List(List<T>& L);// 复制构造函数
	~List() { makeEmpty(); }// 析构函数
	void makeEmpty();// 将链表置为空表
	LinkNode<T>* Locate(int i)const;// 搜索第i个元素的地址
	bool getData(int i, T& x)const;// 取出第i个元素的值
	void setData(int i, T& x);// 用x修改第i个元素的值
	bool Insert(int i, T& x);// 在第i个元素后插入x
	bool Remove(int i, T& x);// 删除第i个元素，x返回该元素的值
	bool IsEmpty()const
	{
		return first->link == nullptr ? true : false;
	}
	// 判表空否
	void output(); // 输出
	void input(T endTag); // 输入
protected:
	LinkNode<T>* first; // 链表的头指针
};
