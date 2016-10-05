/*Shortestpaths.cpp : 定义控制台应用程序的入口点。
分支限界法
(1)描述：采用广度优先产生状态空间树的结点，并使用剪枝函数的方法称为分枝限界法。
所谓“分支”是采用广度优先的策略，依次生成扩展结点的所有分支（即：儿子结点）。
所谓“限界”是在结点扩展过程中，计算结点的上界（或下界），边搜索边减掉搜索树的某些分支，从而提高搜索效率。
(2)原理：按照广度优先的原则，一个活结点一旦成为扩展结点（E-结点）R后，算法将依次生成它的全部孩子结点，将那些导致不可行解或导致非最优解的儿子舍弃，其余儿子加入活结点表中。然后，从活结点表中取出一个结点作为当前扩展结点。重复上述结点扩展过程，直至找到问题的解或判定无解为止。
(3)分支限界法与回溯法
1)求解目标：回溯法的求解目标是找出解空间树中满足约束条件的所有解，而分支限界法的求解目标则是找出满足约束条件的一个解，或是在满足约束条件的解中找出在某种意义下的最优解。
2)搜索方式的不同：回溯法以深度优先的方式搜索解空间树，而分支限界法则以广度优先或以最小耗费优先的方式搜索解空间树。
常见的分支限界法：1)FIFO分支限界法(队列式分支限界法)  2)LC(least cost)分支限界法(优先队列式分支限界法)
*/

#include "stdafx.h"
#include"MinHeap2.h"
#include<iostream>
#include<fstream>
using namespace std;

ifstream fin("C:\\Users\\YAN\\Desktop\\data.txt");
template<class Type>class Graph
{
	friend int main();
public:
	void ShortestPaths(int);
private:
	int n,//图G的顶点数
		*prev;//前驱顶点数组
	Type **c,//图D 的邻接矩阵
		*dist;//最短距离数组
};
template<class Type>class MinHeapNode
{
	friend Graph<Type>;
public:
	operator int()const
	{
		return length;
	}
private:
	int i;//顶点编号
	Type length;//当前路长
};
template<class Type>void Graph<Type>::ShortestPaths(int v)//单源最短路径问题的优先队列式分支限界法
{
	MinHeap<MinHeapNode<Type>>H(1000);
	MinHeapNode<Type>E;
	//定义源为初始扩展节点
	E.i = v;
	E.length = 0;
	dist[v] = 0;
	while (true)//搜索问题的解空间
	{
		for (int j = 1; j <= n; j++)
		{
			if ((c[E.i][j] != 0) && (E.length + c[E.i][j] < dist[j]))
			{
				//顶点i到顶点j可达，且满足控制约束
				dist[j] = E.length + c[E.i][j];
				prev[j] = E.i;
				//加入活节点优先队列
				MinHeapNode<Type>N;
				N.i = j;
				N.length = dist[j];
				H.Insert(N);
			}
		}
		try
		{
			H.DeleteMin(E);//取下一扩展结点
		}
		catch (int )
		{
			break;
		}
		if (H.currentsize == 0)//优先队列空
		{
			break;
		}
	}
}

int main()
{
	int n = 11;
	int prev[12] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	int dist[12] = { 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000 };
	cout << "单源图的邻接矩阵如下：" << endl;
	int**c = new int*[n + 1];
	for (int i = 1; i <= n; i++)
	{
		c[i] = new int[n + 1];
		for (int j = 1; j <= n; j++)
		{
			fin >> c[i][j];
			cout << c[i][j] << " ";
		}
		cout << endl;
	}
	int v = 1;
	Graph<int>G;
	G.n = n;
	G.c = c;
	G.dist = dist;
	G.prev = prev;
	G.ShortestPaths(v);
	cout << "从S到T的最短路长是：" << dist[11] << endl;
	for (int i = 2; i <= n; i++)
	{
		cout << "prev(" << i << ")=" << prev[i] << " " << endl;
	}
	for (int i = 2; i <= n; i++)
	{
		cout << "从1到" << i << "的最短路长为：" << dist[i] << endl;
	}
	for (int i = 1; i <= n; i++)
	{
		delete[]c[i];
	}
	delete[]c;
	return 0;
}

