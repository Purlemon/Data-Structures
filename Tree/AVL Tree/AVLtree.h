#pragma once
#include<iostream>
using namespace std;
template<class E>
class BinNode
{
public:
	E elem;
	int height;
	BinNode<E>* left;BinNode<E>* right;BinNode<E>* parent;

	BinNode():parent(nullptr),left(nullptr),right(nullptr),height(-1) {}
	BinNode(E _elem, BinNode<E>* _parent = nullptr, 
		BinNode<E>* _left = nullptr, BinNode<E>* _rignt = nullptr, int _height = 0)
	{
		elem = _elem;
		height = _height;
		left = _left;
		right = _rignt;
		parent = _parent;
	}
	~BinNode() {}
	bool isLeaf() { return(left == nullptr && right == nullptr) ? true : false; }
	
	//将e插入左子节点，并为其设置父节点tfa
	BinNode<E>* insertAsLC(E const& e, BinNode<E>*tfa) { return left = new BinNode<E>(e,tfa);}
	//将e插入右子节点，并未其设置父节点tfa
	BinNode<E>* insertAsRC(E const& e, BinNode<E>*tfa) {  return right = new BinNode<E>(e,tfa);}

	//计算平衡因子
	int balFac() {
		if (!left && !right)return 0;
		else if (!left && right)return right->height + 1;
		else if (left && !right)return left->height + 1;
		else
			return(left->height - right->height);
	}
};

template<class E>
class AVL {
protected:
	BinNode<E>* root;
public:
	AVL():root(nullptr) {}
	~AVL() {}

	BinNode<E>* getRoot() { return root; }

	//若val存在，返回val的位置；否则，返回空指针
	//t为val插入的位置,hot为val的父节点
	BinNode<E>* searchIn(BinNode<E>*& t, E& val, BinNode<E>*& hot);
	BinNode<E>* searchIn(BinNode<E>*& t, E& val);
	bool find(E val);//检索一个值
	
	bool input(int endTag);//建立树
	bool preorder(BinNode<E>*t);//以t为根节点前序遍历树并输出

	void insert(E val);//插入接口
	bool remove(E val);//删除接口
	bool removeat(BinNode<E>*& current);//子节点有空时的删除办法

	bool balance(BinNode<E>* t);//重平衡接口，t是被更改节点的父节点
	BinNode<E>* upDataHeight(BinNode<E>* t);//更新高度
	
	//将val作为t的子节点插入
	void insertNode(E const& val, BinNode<E>* t) { 
		val < t->elem ? t->insertAsLC(val,t) : t->insertAsRC(val,t);
		upDataHeight(t);
	}
	
	//向上遍历找到失衡节点
	BinNode<E>* lostBal(BinNode<E>* t){
		//从t开始向parent递归
		//若无，返回nullptr
		if (t == nullptr)  return nullptr;
		if ((t->balFac() == 2) || (t->balFac() == -2)) return t; 
		return lostBal(t->parent);
	}

	//综合4种旋转情况的重平衡法
	BinNode<E>* connect(BinNode<E>*& a, BinNode<E>*& b, BinNode<E>*& c,
		BinNode<E>*& t0, BinNode<E>*& t1, BinNode<E>*& t2, BinNode<E>*& t3)
	{
		a->left = t0; if (t0)t0->parent = a;
		a->right = t1; if (t1)t1->parent = a; upDataHeight(a);
		c->left = t2; if (t2)t2->parent = c;
		c->right = t3; if (t3)t3->parent = c; upDataHeight(c);
		b->left = a; a->parent = b;
		b->right = c; c->parent = b;
		upDataHeight(b);
		return b;
	}

	//返回最小值节点
	BinNode<E>* findMin(BinNode<E>* t)
	{
		if (t->left == nullptr)return t;
		t = t->left;
		findMin(t);
	}
};



