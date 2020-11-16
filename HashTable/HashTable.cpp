#include<iostream>
#include<vector>
#include <stdlib.h> 
#include<time.h>
using namespace std;

class Huffman
{
private:
	int coll;
	int size;
	int lf;//负载因子 
	vector<int>huffman;

public:
	Huffman(int _size) :coll(0), lf(0), size(_size), huffman(_size, -1) {}
	//输出函数 
	void print() {
		cout << "collision number:" << coll << endl;
		for (int i = 0; i != size; i++)
			cout << huffman[i] << " ";
		coll = 0;
		cout << endl;
	}
	//判断表是否满
	bool isFull() {
		return lf == size ? true : false;
	}
	//清空哈希表
	void clearHash() {
		for (auto i = huffman.begin(); i != huffman.end(); i++)
			*i = -1;
	}

	//哈希序列 
	int Hash(int x)
	{
		return x % size;
	}

	//线性探测序列 
	int Linear(int x, int i)
	{
		return (Hash(x) + i) % size;
	}

	bool linearProbing(int x)
	{
		if (isFull())return false;
		for (int i = 0; i != size; i++) {
			if (huffman[Linear(x, i)] < 0) {
				huffman[Linear(x, i)] = x;
				lf++;
				return true;
			}
			coll++;
		}
		return false;
	}

	//二次探测序列
	int Quadratic(int x, int i)
	{
		return ((Hash(x) + i * i) % size);
	}

	bool quadraticProbing(int x)
	{
		if (isFull())
			return false;
		for (int i = 0; i < (size / 2 + 1); i++) {
			if (huffman[Quadratic(x, i)] < 0) {
				huffman[Quadratic(x, i)] = x;
				lf++;
				return true;
			}
			coll++;
		}
		return false;
	}

	//伪随机探测序列
	bool pseudo_randomProbing(int x)
	{
		if (isFull()) 
			return false;
		if (huffman[Hash(x)] < 0) {

			huffman[Hash(x)] = x;
			lf++;
			return true;
		}
		srand((unsigned)time(nullptr));
		while (true)
		{
			int random = (Hash(x) + rand() % size) % size;
			if (huffman[random] < 0)
			{
				huffman[random] = x;
				lf++;
				return true;
			}
			coll++;
		}
		return false;
	}

	//双散列探测序列
	int DoubleHash(int x, int i)
	{
		return (Hash(x) + i * ((31 * x + 2) % size)) % size;
	}

	bool doubleHashProbing(int x)
	{
		if (isFull())return false;
		for (int i = 0; i < size; i++) {
			if (huffman[DoubleHash(x, i)] < 0) {
				huffman[DoubleHash(x, i)] = x;
				lf++;
				return true;
			}
			coll++;
		}
		return false;
	}
};


int main()
{
	Huffman test1(53);
	Huffman test2(53);
	Huffman test3(53);
	Huffman test4(53);
	vector<int>rOrder(50);
	srand((unsigned)time(nullptr));
	for (auto i = rOrder.begin(); i != rOrder.end(); i++)
		*i = rand() % 1000;
	
	for (auto i : rOrder)
		test1.linearProbing(i);
	cout << "Linear" << endl; test1.print();
	
	for (auto i : rOrder)
		test2.quadraticProbing(i);
	cout << "Quadratic"<<endl; test2.print();
	
	for (auto i : rOrder)
		test3.pseudo_randomProbing(i);
	cout << "Pseudo-random"<<endl; test3.print();
	
	for (auto i : rOrder)
		test4.doubleHashProbing(i);
	cout << "Double Hash"<<endl; test4.print();
}
