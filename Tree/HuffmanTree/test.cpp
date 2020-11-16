#include<iostream>
#include"HuffmanTree.h"
#include"Heap.h"
using namespace std;

int main()
{
	BinNode<string> a("a",7);
	BinNode<string> b("b",9);
	BinNode<string> c("c",2);
	BinNode<string> d("d",6);
	BinNode<string> e("e",32);
	BinNode<string> f("f",3);
	vector<BinNode<string>>x = { a,b,c,d,e,f };
	HuffmanTree<string> h(x);
	string s="ffeefeaaecffbdbfbcdadacdeedccf";
	string cs=h.code(s);
	cout << endl << "电文：" << s << endl;
	cout << "编码：" << cs << endl;
}
