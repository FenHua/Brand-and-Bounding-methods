/*FindPath.cpp : 定义控制台应用程序的入口点。
问题描述
印刷电路板将布线区域划分成n×m个方格如图a所示。精确的电路布线问题要求确定连接方格a的中点到方
格b的中点的最短布线方案。在布线时，电路只能沿直线或直角布线，如图b所示。为了避免线路相交，已布
了线的方格做了封锁标记，其它线路不允穿过被封锁的方格。
算法思想
解此问题的队列式分支限界法从起始位置a开始将它作为第一个扩展结点。与该扩展结点相邻并且可达的方格
成为可行结点被加入到活结点队列中，并且将这些方格标记为1，即从起始方格a到这些方格的距离为1。
接着，算法从活结点队列中取出队首结点作为下一个扩展结点，并将与当前扩展结点相邻且未标记过的方格标
记为2，并存入活结点队列。这个过程一直继续到算法搜索到目标方格b或活结点队列为空时为止。即加入剪枝
的广度优先搜索。
*/

#include "stdafx.h"
#include"Queue.h"
#include<fstream>
#include<iostream>
using namespace std;

ifstream fin("C:\\Users\\YAN\\Desktop\\data.txt");
const int n = 7;
const int m = 7;
int grid[n + 2][m +2];
struct Position
{
	int row;
	int col;
};
bool FindPath(Position start, Position finish, int &PathLen, Position*&path);

int main()
{
	int PathLen;
	Position start, finish, *path;
	start.row = 3;
	start.col = 2;
	finish.row = 4;
	finish.col = 6;
	cout << "布线起点：" << endl;
	cout << start.col << " " << start.row << endl;
	cout << "布线结束点：" << endl;
	cout << finish.col << " " << finish.row << endl;
	cout << "布线方格阵列如下（0表示允许布线，1表示不允许布线）:" << endl;
	for (int i = 1; i <= m; i++)
	{
		for (int j = 1; j < n; j++)
		{
			fin >> grid[i][j];
			cout << grid[i][j] << " ";
		}
		cout << endl;
	}
	FindPath(start, finish, PathLen, path);
	cout << "布线长度为：" << PathLen << endl;
	cout << "布线路径如下：" <<endl;
	for (int i = 0; i < PathLen; i++)
	{
		cout << path[i].col << " " << path[i].row << endl;
	}
	return 0;
}
bool FindPath(Position start, Position finish, int&PathLen, Position*&path)
{
	if ((start.row == finish.row) && (start.col == finish.col))
	{
		PathLen = 0;
		return true;
	}
	//设置方格阵列围墙
	for (int i = 0; i <= m + 1; i++)
	{
		grid[0][i] = grid[n + 1][i] = 1;//顶部和底部
	}
	for (int i = 0; i <= n + 1; i++)
	{
		grid[i][0] = grid[i][m + 1] = 1;//左翼和右翼
	}
	//初始化相对位移
	Position offset[4];
	offset[0].row = 0;
	offset[0].col = 1;//右
	offset[1].row = 1;
	offset[1].col = 0;//下
	offset[2].row = 0;
	offset[2].col = -1;//左
	offset[3].row = -1;
	offset[3].col = 0;//上
	int NumOfNbrs = 4;//相邻方格数
	Position here, nbr;
	here.row = start.row;
	here.col = start.col;
	grid[start.row][start.col] = 2;//标记可达方格位置
	Queue<Position>Q;
	do{
		//标记相邻可达方格
		for (int i = 0; i < NumOfNbrs; i++)
		{
			nbr.row = here.row + offset[i].row;
			nbr.col = here.col + offset[i].col;
			if (grid[nbr.row][nbr.col] == 0)//方格未被标记
			{
				grid[nbr.row][nbr.col] = grid[here.row][here.col] + 1;
				if ((nbr.row == finish.row) && (nbr.col == finish.col))
				{
					break;
				}
				Q.Add(nbr);
			}
		}
		//是否到达目标位置finish
		if ((nbr.row == finish.row) && (nbr.col == finish.col))
		{
			break;//完成布线
		}
		if (Q.IsEmpty())//活节点队列是否为空
		{
			return false;//无解
		}
		Q.Delete(here);//取下一个扩展节点
	} while (true);
	//构造最短布线路径
	PathLen = grid[finish.row][finish.col] - 2;
	path = new Position[PathLen];//从目标位置finish开始向起始位置回溯
	here = finish;
	for (int j = PathLen - 1; j >= 0; j--)
	{
		path[j] = here;//找前驱位置
		for (int i = 0; i < NumOfNbrs; i++)
		{
			nbr.row = here.row + offset[i].row;
			nbr.col = here.col + offset[i].col;
			if (grid[nbr.row][nbr.col] == j + 2)
			{
				break;
			}
		}
		here = nbr;//向前移动
	}
	return true;
}
