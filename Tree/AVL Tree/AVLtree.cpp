#include<iostream> 
#include"AVLtree.h"
#include<algorithm>
using namespace std;

template<class E>
BinNode<E>* AVL<E>::searchIn(BinNode<E>*& t, E& val, BinNode<E>*& hot)
{
	if (!t || val == t->elem) return t;
	hot = t;
	return searchIn(((val < t->elem) ? t->left : t->right), val, hot);
}

template<class E>
BinNode<E>* AVL<E>::searchIn(BinNode<E>*& t, E& val)
{
	if (!t || val == t->elem) return t;
	return searchIn(((val < t->elem) ? t->left : t->right), val);
}

template<class E>
bool AVL<E>::find(E val)
{
	if (searchIn(root, val)) {
		cout << "元素" << val << "存在" << endl;
		return true;
	}
	else
		cout << "元素" << val << "不存在" << endl;
	return false;
}

template<class E>
BinNode<E>* AVL<E>::upDataHeight(BinNode<E>* t)
{
	if (t == nullptr)return nullptr;
	if ((!t->left) && (!t->right))t->height = 0;
	else if (!t->left)
		t->height = t->right->height + 1;
	else if (!t->right)
		t->height = t->left->height + 1;
	else
		t->height = max(t->left->height, t->right->height) + 1;
	if (t->parent == nullptr)
		return nullptr;
	return upDataHeight(t->parent);
}

template<class E>
void AVL<E>::insert(E val)
{
	BinNode<E>* cfa; BinNode<E>* current = root;
	searchIn(current, val, cfa);
	insertNode(val, cfa);
	balance(cfa);
}

template<class E>
bool AVL<E>::balance(BinNode<E>* t)
{   //g是第一个失衡节点
	BinNode<E>* g = lostBal(t);
	if (!g)return false;
	
	//p是g的儿子
	BinNode<E>* p = nullptr;
	if (!g->left)
		p = g->right;
	else if (!g->right)
		p = g->left;
	else
		p = g->left->height > g->right->height ? g->left : g->right;
	if (!p)return false;

	//v是g的孙子
	BinNode<E>* v = nullptr;
	if (!p->left)
		v = p->right;
	else if (!p->right)
		v = p->left;
	else
		v = p->left->height > p->right->height ? p->left : p->right;
	if (!v)return false;

	//cout << "平衡因子不行的" << g->elem << endl;
	//cout << "g,p,v为" << g->elem << " " << p->elem << " " << v->elem << endl;
	
	if (g->left == v->parent)//zig
	{
		if (p->left == v)//zig-zig
		{
			if (g->parent) {
				if (g->parent->left == g)
					g->parent->left = g->left;
				else
					g->parent->right = g->left;
			}
			if (root == g)root = p;
			p->parent = g->parent;
			connect(v, p, g, v->left, v->right, p->right, g->right);
		}
		else//zig-zag
		{
			if (g->parent) {
				if (g->parent->left == g)
					g->parent->left = p->right;
				else
					g->parent->right = p->right;
			}
			if (root == g)root = v;
			v->parent = g->parent;
			connect(p, v, g, p->left, v->left, v->right, g->right);
		}
	}
	else//zag
	{
		if (p->right == v)//zag-zig
		{
			if (g->parent) {
				if (g->parent->left == g)
					g->parent->left = g->right;
				else
					g->parent->right = g->right;
			}
			if (root == g)root = p;
			p->parent = g->parent;
			connect(g, p, v, g->left, p->left, v->left, v->right);
		}
		else//zag-zag
		{
			if (g->parent) {
				if (g->parent->left == g)
					g->parent->left = p->left;
				else
					g->parent->right = p->left;
			}
			if (root == g)root = v;
			v->parent = g->parent;
			connect(g, v, p, g->left, v->left, v->right, p->right);
		}
	}
	return true;
}

template<class E>
bool AVL<E>::remove(E val)
{
	BinNode<E>* current = nullptr;
	current = searchIn(root, val);//删除节点指针
	BinNode<E>* minptr = nullptr;//删除节点右子树的最小节点指针
	if (!current) {
		cout << "该节点不存在，无法删除" << endl;
		return false;
	}

	//没有子节点或有一个子节点的情况
	if (!current->left || !current->right) 
	{
		removeat(current);
		minptr = current;
	}
	//有两个子节点的情况
	else
	{
		minptr = findMin(current->right);
		current->elem = minptr->elem;
		removeat(minptr);
	}
	upDataHeight(minptr);
	balance(minptr);
	delete minptr;
	return true;
}

template<class E>
bool AVL<E>::removeat(BinNode<E>*& current)
{   //current是指向删除节点的指针

	if (!current->left)//左侧为空
	{
		if (!current->parent)//删除节点是根节点
			root = current->right;
		else {
			if (current->parent->left == current)
				current->parent->left = current->right;
			else
				current->parent->right = current->right;
			if (current->right)
				current->right->parent = current->parent;
		}
	}
	else if (!current->right)//右侧为空
	{
		if (!current->parent)//删除节点是根节点
			root = current->left;
		else {
			if (current->parent->left == current)
				current->parent->left = current->left;
			else
				current->parent->right = current->left;
			if (current->left)
				current->left->parent = current->parent;
		}
	}
	return true;
}

template<class E>
bool AVL<E>::input(int endTag)
{//当读入endTag输入结束
	E val;
	cin >> val;
	root = new BinNode<E>(val);
	cin >> val;
	while (val != endTag)
	{
		insert(val);
		cin >> val;
	}
	return true;
}

template<class E>
bool AVL<E>::preorder(BinNode<E>* t)
{
	if (t == nullptr) return false;
	cout <<"元素："<< t->elem << " " << "高度：" << t->height << endl;// " " << "平衡因子：" << t->balFac() << endl;
	//if (root == t)cout << "根节点" << endl;
	//else
	//	cout << " " << "父亲：" << t->parent->elem << endl;
	//if (t->left)cout << "左儿子：" << t->left->elem << endl;
	//if (t->right)cout << "右儿子：" << t->right->elem << endl;
	preorder(t->left);
	preorder(t->right);
	return true;
}


int main()
{
	AVL<int>avl;
	avl.input(-1);//以-1为标识符结束输入
	avl.insert(1);
	avl.remove(6);
	avl.find(1);
	avl.find(4);
	avl.preorder(avl.getRoot());
	cout << endl;
}





