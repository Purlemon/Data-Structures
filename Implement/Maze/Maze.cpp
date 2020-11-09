#include"Maze.h"
#include<time.h>
#include<easyx.h>
#include <conio.h>	
using namespace std;

class Maze
{
public:
	int row;
	int col;
	vector<Node> maze;
	vector<Node> MAZE;
	vector<E> edge;
	vector<Fin> fin;

	Maze(int _row,int _col):row(_row),col(_col)
	{
	for(int i=0;i!=row;i++)
		for (int j = 0; j != col; j++)
		{
			Node* current = new Node(i, j, row);
			maze.push_back(*current);
			MAZE.push_back(*current);
		}
	}

	bool buildEdge()
	{
		for (int i = 0; i != row; i++)
			for (int j = 0; j != col; j++)
			{
				if (maze[row * i + j].x != (row - 1))
				{
					E* current1 = new E(maze[row * i + j].elem, maze[row * (i + 1) + j].elem);
					edge.push_back(*current1);
				}
				if (maze[row * i + j].y != (col - 1))
				{
					E* current2 = new E(maze[row * i + j].elem, maze[row * i + j + 1].elem);
					edge.push_back(*current2);
				}
			}
		return true;
	}
	
	bool seleteEdge(int& x, int& y)
	{
		if (!edge.size())return false;
		srand((unsigned)time(NULL));
		auto iter = edge.begin()+rand() % edge.size();
		x = iter->x; 
		y = iter->y;
		edge.erase(iter);
		return true;
	}

	int Find(int val)//返回val的根
	{
		if (maze[val].parent < 0)return val;
		return Find(maze[val].parent);
	
	}

	bool Union(int u, int v)
	{
		maze[v].parent = u;
		return true;
	}

	bool buildMaze()
	{
		int x, y, u, v;
		while (edge.size())
		{
			seleteEdge(x, y);
			u = Find(x);
			v = Find(y);
			if (u != v)
			{
				Union(u, v);
				if (MAZE[x].x == MAZE[y].x) {
					Fin* curr1 = new Fin(MAZE[y].x, MAZE[y].y, MAZE[y].x + 1, MAZE[y].y);
					fin.push_back(*curr1);
				}
				if (MAZE[x].y == MAZE[y].y) {
					Fin* curr2 = new Fin(MAZE[y].x, MAZE[y].y, MAZE[y].x, MAZE[y].y + 1);
					fin.push_back(*curr2);
				}
				
			}
		}
		return true;
	}
};

int main()
{
	initgraph(1080, 1080);
	Maze test(10, 10);
	int x, y;
	test.buildEdge();
	test.buildMaze();
	for (auto& i : test.MAZE)
	{
		rectangle(100 * i.x, 100 * i.y, 100 * (i.x + 1), 100 * (i.y + 1));
	}
	setlinecolor(BLACK );
	for (auto& i : test.fin)
		line(100*i.lx, 100 * i.ly, 100 * i.rx, 100 * i.ry);
	line(100 * test.row, 0, 100 * test.row, 100 * 1);
	line(100 * test.row, 100 * (test.col-1), 100 * test.row, 100 * test.col);
	_getch();					// 按任意键
	closegraph();				// 关闭绘图屏幕
	return 0;
}
