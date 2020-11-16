#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H
#include"Heap.h"
using namespace std;

template<typename T>
class BinNode
{
public:
	T elem;//元素
	BinNode<T>* lc;//左子树
	BinNode<T>* rc;//右子树
	string code;//编码
	int freq;//频次(权重)

	//构造函数
	BinNode() :
		lc(nullptr), rc(nullptr), freq(0) {}
	BinNode(T _elem, int _freq=0, BinNode<T>* _lc = nullptr, BinNode<T>* _rc = nullptr, int _path = 0) :
		elem(_elem), lc(_lc), rc(_rc), freq(_freq) {}
	BinNode(const BinNode &n) :
		elem(n.elem), lc(n.lc), rc(n.rc), freq(n.freq) {}

	//将e作为当前节点左子节点插入
	BinNode<T>* insertAsLc(const T& e) { return lc = new BinNode(e); }
	//将e作为当前节点右子节点插入
	BinNode<T>* insertAsRc(const T& e) { return rc = new BinNode(e); }
	//若为叶子节点，返回true
	bool isLeaf() { return lc == nullptr && rc == nullptr ? true : false; }

	//重载关系运算符
	bool operator<(const BinNode<T>& n) {
		if (freq < n.freq)return true;
		else return false;
	}
	bool operator<=(const BinNode<T>& n) {
		if (freq <= n.freq)return true;
		else return false;
	}
	bool operator>(const BinNode<T>& n) {
		if (freq > n.freq)return true;
		else return false;
	}bool operator>=(const BinNode<T>& n) {
		if (freq >= n.freq)return true;
		else return false;
	}
	bool operator==(const BinNode<T>& n) {
		if (freq == n.freq)return true;
		else return false;
	}
	friend ostream& operator<<(ostream& output, const BinNode<T>& n) {
		output << n.elem;
		return output;
	}
};

template<typename T>
class HuffmanTree
{
private:
	Heap<BinNode<T>> forest;//用堆存放单个节点
public:
	BinNode<T>* root;//根节点
	HuffmanTree() :
		forest(0), root(nullptr){}
	HuffmanTree(vector<BinNode<string>>& f, BinNode<T>* r = nullptr) :
		root(r) {
		forest = f;  buildHuffmanTree(); preorderCode(root);
	}

	bool buildHuffmanTree();//建立编码树
	bool findPreorder(string e,BinNode<T>* t, string& cs);//从t节点开始遍历编码树，找到e的编码，写入cs

	//遍历，计算编码
	bool preorderCode(BinNode<T>* t);
	bool lcpreorder(BinNode<T>* t, string& s);
	bool rcpreorder(BinNode<T>* t, string& s);

	//返回s的编码
	string code(string& s);

	//返回s的解码
	string decode(string& s);
};

template<typename T>
bool HuffmanTree<T>::buildHuffmanTree()
{
	if (forest.empty())return false;
	for (int i = forest.size(); i != 1; --i)
	{
		//建立三个新节点空间,左右子节点取自当前节点森林中最小
		BinNode<T>* curr = new BinNode<T>;
		curr->lc = new BinNode<T>(forest.getMin());
		forest.deleteMin();
		curr->rc = new BinNode<T>(forest.getMin());
		forest.deleteMin();
		curr->freq = curr->lc->freq + curr->rc->freq;//新节点权重等于两个子节点之和
		forest.insert(*curr);//将新节点插入森林
		root = curr;//当森林里只有一棵树时，当前节点必然是根节点
	}
	return true;
};

template<typename T>
bool HuffmanTree<T>::preorderCode(BinNode<T>* t)
{//前序遍历
	if (t == nullptr) return false;
	if(t->isLeaf())cout << t->elem << " "<<t->code<<endl;
	lcpreorder(t->lc,t->code);
	rcpreorder(t->rc,t->code);
	return true;
}
template<typename T>
bool HuffmanTree<T>::lcpreorder(BinNode<T>* t, string& s)
{//左子树编码+0
	if (t == nullptr) return false;
	t->code = s+"0";
	preorderCode(t);
	return true;
}
template<typename T>
bool HuffmanTree<T>::rcpreorder(BinNode<T>* t, string& s)
{//右子树编码+1
	if (t == nullptr) return false;
	t->code = s+ "1";
	preorderCode(t);
	return true;
}

template<typename T>
bool HuffmanTree<T>::findPreorder(string e, BinNode<T>* t , string& cs)
{
	if (t == nullptr) return false;
	if (e == t->elem) {	cs += t->code; return true;	}
	findPreorder(e, t->lc,cs);
	findPreorder(e, t->rc,cs);
}

template<typename T>
string HuffmanTree<T>::code(string& s)
{
	string cs;
	for (auto is : s) {
		string sis = { is };
		findPreorder(sis, root, cs);
	}
	return cs;
}

template<typename T>
string HuffmanTree<T>::decode(string& s)
{
	string ds;
	BinNode<T>*curr = root;
	for (auto& i : s)
	{
		if (i == '0')//0访问左子树
			curr = curr->lc;
		else if (i == '1')//1访问右子树
			curr = curr->rc;
		else
			return ds;//编码出现非01字符，解码失败
		if (curr->isLeaf())
		{//若为叶子节点，输出对应字符，同时将当前指针置为root
			ds += curr->elem;
			curr = root;
		}
	}
	return ds;
}

//计算s的各个字符频率，返回频率表
vector<BinNode<string>> wordFreq(string& s)
{
	vector<BinNode<string>>table;
	bool find = false;
	for (auto& is : s)
	{
		string sis = { is };
		for (auto& itable : table)
		{
			if (itable.elem == sis) {
				itable.freq++;
				find = true;
				break;
			}
		}
		if (find)
			find = false;
		else
		{
			BinNode<string>word(sis, 1);
			table.push_back(word);
		}
	}
	return table;
}
#endif

