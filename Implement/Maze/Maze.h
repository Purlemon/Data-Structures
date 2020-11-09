#pragma once
#include<iostream>
#include<vector>

struct Node
{
	int x;
	int y;
	int row;//行数
	int elem = row * x + y;

	int weighted;//权重
	int parent;

	Node(int _x, int _y, int _row,int _parent=-1) :x(_x), y(_y), row(_row),
		weighted(1),parent(_parent)
	{}
};

struct E//边集
{
	int x;
	int y;
	E(int _x,int _y):x(_x), y(_y){}
};

struct Fin
{
	int lx;
	int ly;
	int rx;
	int ry;
	Fin(int _lx, int _ly, int _rx, int _ry) :lx(_lx), ly(_ly), rx(_rx), ry(_ry){}
};
