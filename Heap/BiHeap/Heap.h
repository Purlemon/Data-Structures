#ifndef HEAP_H
#define HEAP_H
#include<vector>
using namespace std;
template<typename T>
class Heap
{
private:
	vector<T> heap;//根为heap[0]的堆

public:
	Heap() :heap(0) {}
	Heap(size_t _size) :heap(_size) {}

	int p(int i) { return (i - 1) / 2; }//返回i的父亲下标
	int lc(int i) { return 2 * i + 1; }//返回i的左孩子下标
	int rc(int i) { return 2 * i + 2; }//返回i的右孩子下标

	T getMin() { return heap[0]; }//返回最小值
	void insert(T e);//插入元素e
	bool deleteMin();//删除最小值
	void bulidHeap(const vector<T>& v);//用v内序列建堆
	void print();//打印堆

	bool PercUp();//上滤
	bool PercDown(size_t i);//从i开始下渗
};

template<typename T>
void Heap<T>::insert(T e)
{
	heap.push_back(e);
	PercUp();
}

template<typename T>
bool Heap<T>::deleteMin()
{
	if (heap.empty())
		return false;
	swap(heap[0], heap[heap.size()-1]);//交换最小值和最后一个元素
	heap.pop_back();//删除最小值
	PercDown(0);
}

template<typename T>
void Heap<T>::bulidHeap(const vector<T>& v)
{
	heap = v;
	//从最后一个子节点的父亲开始下渗，一直到根
	for (int i = p(heap.size() - 1); i >= 0; --i)
		PercDown(i);
}

template<typename T>
void Heap<T>::print()
{
	for (auto i : heap)
		cout << i << " ";
	cout << endl;
}

template<typename T>
bool Heap<T>::PercUp()
{
	T temp;
	for (size_t i = heap.size() - 1; i > 0; i = p(i))
	{//如果i比它父亲小，交换i和它父亲，直到根
		if (heap[i] < heap[p(i)])
			swap(heap[i], heap[p(i)]);
		else 
			return true;
	}
}

template<typename T>
bool Heap<T>::PercDown(size_t i)
{
	while (i < heap.size())
	{//交换i和它两个儿子中较小的一个
		if (lc(i) < heap.size() && heap[i] > heap[lc(i)] && (!(rc(i) < heap.size())||heap[lc(i)] <= heap[rc(i)])) {
			swap(heap[i], heap[lc(i)]);
			i = lc(i);
		}
		else if (rc(i) < heap.size() && heap[i] > heap[rc(i)] && heap[lc(i)] >= heap[rc(i)]) {
			swap(heap[i], heap[rc(i)]);
			i = rc(i);
		}
		else
			return true;
	}
}

#endif
