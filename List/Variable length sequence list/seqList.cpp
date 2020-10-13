#include"seqList.h"
#include<string>
using namespace std;

template<class T>
SeqList<T>::SeqList(int sz) :maxSize(sz), last(0)
{
	// 构造函数，通过指定参数sz定义数组长
	data = new T[maxSize];
}

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
	cout << "已扩容，当前表最大元素个数：" << maxSize << endl;
	return true;
}

template<class T>
bool SeqList<T>::deleteSize()
{
	if (last > (maxSize / 4))return false;
    T* ptr;
	T* newData = new T[maxSize / 2+1];
	if (newData == nullptr)cout << "分配内存错误";
	for (int i = 0; i < last; i++)
		newData[i] = data[i];
	ptr = data;
	data = newData;
	delete[]ptr;
	maxSize = maxSize / 2 + 1;
	cout << "已减容，当前表最大元素个数：" << maxSize << endl;
	if (last < (maxSize / 4))deleteSize();
	return true;
}

template<class T>
bool SeqList<T>::insert(int i,T x)
{
	last++;
	if (isFull()==true)resize();
	if (i<0 || i>last ) { cout << "插入位置不合理"; return false; }
	for (int j = last; j > i; j--)
		data[j - 1] = data[j - 2];
	data[i-1] = x;
	return true;
}

template<class T>
bool SeqList<T>::remove(int i)
{
	if (isEmpty()==true) { cout << "表空，无法删除"; return false; }
	if (i<0 || i>last ) { cout << "删除位置不合理"; return false; }
	for (int j = i; j < last; j++)
		data[j-1] = data[j];
	last--;
	deleteSize();
	return true;
}

template<class T>
bool SeqList<T>::append(T x)
{
	if (isFull() == true)resize();//如果表满，扩容
	last++;
	data[last - 1] = x;
	//cout << "元素+1" << endl;
	return true;
}


template<class T>
bool SeqList<T>::init()
{
	//初始化列表并删除原来的列表空间
	maxSize = 10;
	T* ptr;
	T* newData = new T[maxSize];
	if (newData == nullptr) { cout << "分配内存错误"; return false; }
	ptr = data;
	data = newData;
	delete[]ptr;
	last = 0;
	return true;
}

template<class T>
void SeqList<T>::input()
{
	cout << "开始建立顺序表，请输入表中元素个数:";
	while (true)
	{
		cin >> last;
		if (last <= maxSize - 1)break;
		cout << "表元素个数输入有误，不能超过" << maxSize - 1<<endl;
	}
	for(int i=0;i<last;i++)
	{
		cout << "第" << i + 1 << "个元素为:"; cin >> data[i];
	}
	deleteSize();
}

template<class T>
void SeqList<T>::print()
{
	cout << "开始打印顺序表："  << endl;
	for (int i = 0; i < last; i++)
		cout << "第" << i + 1 << "个元素为:" << data[i] << endl;
}

int main()
{
	SeqList<string>seqlist(20);
	seqlist.init();
	if (seqlist.isEmpty())cout << "表空" << endl;
    seqlist.append("201930380235");
	seqlist.append("201930380273");
	seqlist.append("201930380224");
	seqlist.append("201930380268");
	seqlist.append("201930380289");
	seqlist.append("201930380245");
	seqlist.append("201930380285");
	seqlist.append("201930380264");
	seqlist.append("201930380254");
	if (seqlist.isEmpty())cout << "表空" << endl;
	else cout << "表不空" << endl;
	seqlist.insert(5, "201930382024");
	seqlist.print();
	cout <<"表的长度为:"<< seqlist.length() << endl;
	seqlist.remove(5);
	seqlist.print();
	seqlist.find(5);
	string atTest = "201930380264";
	cout<<seqlist.at(atTest);
}