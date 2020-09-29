#include<iostream>
using namespace std;

template<class T>
class TwoStack
{
public:
	TwoStack(int sz = 10);//构造函数
	~TwoStack() { delete[]elements; }//析构函数
	bool push(const T& x);//将x压入右栈顶
	T pop();//弹出右栈顶并将其返回
	bool inject(const T& x);//将x压入左栈顶
	T eject();//弹出左栈顶并将其返回
	T getFront();//返回右栈顶
	T getRear();//返回左栈顶
	bool IsEmpty()const { return(front == rear) ? true : false; }
	//判断双向栈是否为空
	bool IsFull()const { return ((front + 1) % maxSize == rear) ? true : false; }
	//判断双向栈是否已满
	bool IsLeftBlock() { return (rear == 1) ? true : false; }
	bool IsRightBlock() { return(front == 0) ? true : false; }
private:
	int rear, front;//左栈顶与右栈顶指针
	T* elements;//存放双向栈元素的数组
	int maxSize;//双向栈最大可能的元素个数
};

template<class T>
TwoStack<T>::TwoStack(int sz) :front(1), rear(0), maxSize(sz)
{
	//建立一个最大具有maxSize个元素的空栈
	elements = new T[maxSize];//创建双向栈空间
}

template<class T>
bool TwoStack<T>::push(const T& x)
{
	//若双向栈不满，则将x压入右栈顶，否则报错
	if (IsFull() == true) { cout << "栈已满，" << x << " 未压入右栈顶" << endl; return false; }
	elements[front] = x;//按右栈顶指针压入
	front = (front + 1) % maxSize;//右栈顶指针+1
	return true;
}

template<class T>
T TwoStack<T>::pop()
{
	//若双向栈不空，则弹出右栈顶元素并返回，否则报错
	T x;
	if (IsEmpty() == true) { cout << "栈为空" << endl; return false; }
	if (front == 0)front = maxSize - 1;
	else front = (front - 1) % maxSize;//右栈顶指针-1
	if (IsRightBlock() == true) { cout << "右栈已到达栈底，无法弹出。错误代码："; return false; }
	x = elements[front];
	return x;//弹出成功，返回该元素
}

template<class T>
bool TwoStack<T>::inject(const T& x)
{
	//若双向栈不满，则将x压入左栈顶，否则报错
	if (IsFull() == true) { cout << "栈已满，" << x << " 未压入栈头" << endl; return false; }
	elements[rear] = x;//按左栈顶指针压入
	if (rear == 0)rear = maxSize - 1;
	else rear = (rear - 1) % maxSize;//左栈顶指针-1
	return true;
}

template<class T>
T TwoStack<T>::eject()
{
	//若双向栈不空，则弹出左栈顶元素并返回，否则报错
	T x;
	if (IsEmpty() == true) { cout << "栈为空" << endl; return false; }
	rear = (rear + 1) % maxSize;//左栈顶指针+1
	if (IsLeftBlock() == true) { cout << "左栈已到达栈底，无法弹出。错误代码："; return false; }
	x = elements[rear];
	return x;//弹出成功，返回该元素
}

template<class T>
T TwoStack<T>::getFront()
{
	//若双向栈不空,返回右栈顶元素
	if (IsEmpty() == true) { cout << "栈为空"; return false; }
	return  elements[front];
}

template<class T>
T TwoStack<T>::getRear()
{
	//若双向栈不空,返回左栈顶元素
	if (IsEmpty() == true) { cout << "栈为空"; return false; }
	return  elements[rear];
}

int main()
{
	TwoStack<int>TwoStack(6);
	TwoStack.push(1);
	TwoStack.push(2);
	TwoStack.inject(3);
	TwoStack.inject(4);
	cout << TwoStack.pop() << endl;
	cout << TwoStack.pop() << endl;
	cout << TwoStack.pop() << endl;
	cout << TwoStack.eject() << endl;
	cout << TwoStack.eject() << endl;
}
