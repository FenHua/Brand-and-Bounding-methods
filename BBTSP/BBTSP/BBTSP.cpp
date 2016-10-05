/*BBTSP.cpp : 定义控制台应用程序的入口点。
算法思路
旅行售货员问题的解空间可以组织成一棵树，从树的根结点到任一叶结点的路径定义了图的一条周游路线。旅行售货员问题要在图G中找出费用最小的周游路线。路线是一个带权图。
图中各边的费用（权）为正数。图的一条周游路线是包括V中的每个顶点在内的一条回路。周游路线的费用是这条路线上所有边的费用之和。算法开始时创建一个最小堆，用于表示活
结点优先队列。堆中每个结点的子树费用的下界lcost值是优先队列的优先级。接着算法计算出图中每个顶点的最小费用出边并用minout记录。如果所给的有向图中某个顶点没有出边，
则该图不可能有回路，算法即告结束。如果每个顶点都有出边，则根据计算出的minout作算法初始化。
算法的while循环体完成对排列树内部结点的扩展。对于当前扩展结点，算法分2种情况进行处理：
1、首先考虑s=n-2的情形，此时当前扩展结点是排列树中某个叶结点的父结点。如果该叶结点相应一条可行回路且费用小于当前最小费用，则将该叶结点插入到优先队列中，否则舍去该叶结点。
2、当s<n-2时，算法依次产生当前扩展结点的所有儿子结点。由于当前扩展结点所相应的路径是x[0:s]，其可行儿子结点是从剩余顶点x[s+1:n-1]中选取的顶点x[i]，且(x[s]，x[i])是所给有向图G中
的一条边。对于当前扩展结点的每一个可行儿子结点，计算出其前缀(x[0:s]，x[i])的费用cc和相应的下界lcost。当lcost<bestc时，将这个可行儿子结点插入到活结点优先队列中。
算法中while循环的终止条件是排列树的一个叶结点成为当前扩展结点。当s=n-1时，已找到的回路前缀是x[0:n-1]，它已包含图G的所有n个顶点。因此，当s=n-1时，相应的扩展结点表示一个叶
结点。此时该叶结点所相应的回路的费用等于cc和lcost的值。剩余的活结点的lcost值不小于已找到的回路的费用。它们都不可能导致费用更小的回路。因此已找到的叶结点所相应的回路是一个最
小费用旅行售货员回路，算法可以结束。算法结束时返回找到的最小费用，相应的最优解由数组v给出。
*/

#include "stdafx.h"
#include"MinHeap.h"
#include"iostream"
#include<fstream>
using namespace std;

ifstream fin("C:\\Users\\YAN\\Desktop\\data.txt");
const int N = 4;//图的顶点个数
template<class Type>class Traveling
{
	friend int main();
public:
	Type BBTSP(int v[]);
private:
	int n;//图G 的顶点数
	Type **a,//图G 的邻接矩阵
		NoEdge,//图G的无边标识
		cc,//当前的费用
		bestc;//当前最小费用
};
template<class Type>class MinHeapNode
{
	friend Traveling<Type>;
public:
	operator Type()const
	{
		return lcost;
	}
private:
	Type lcost,//子树费用的下界
		cc,//当前费用
		rcost;//x[s:n-1]中顶点最小出边费用和
	int s,//根节点到当前结点的路径为：x[0:s]
		*x;//需要进一步搜索的顶点时s[s+1,n-1]
};


int main()
{
	int bestx[N + 1];
	cout << "图的顶点个数n=" << N << endl;
	int**a = new int*[N + 1];
	for (int i = 0; i <= N; i++)
	{
		a[i] = new int[N + 1];
	}
	cout << "图的邻接矩阵为：" << endl;
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			fin >> a[i][j];
			cout << a[i][j] << " ";
		}
		cout << endl;
	}
	Traveling<int>t;
	t.a = a;
	t.n = N;
	cout << "最短回路的长为：" << t.BBTSP(bestx) << endl;
	cout << "最短回路为：" << endl;
	for (int i = 1; i <= N; i++)
	{
		cout << bestx[i] << "-->";
	}
	cout << bestx[1] << endl;
	for (int i = 0; i <= N; i++)
	{
		delete[]a[i];
	}
	delete[]a;
	return 0;
}

//解旅行商售货问题的优先队列分支限界法
template<class Type>Type Traveling<Type>::BBTSP(int v[])
{
	MinHeap<MinHeapNode<Type>>H(1000);
	Type*MinOut = new Type[n + 1];
	//计算MinOut[i]=顶点i的最小出边费用
	Type MinSum = 0;//最小出边费用和
	for (int i = 0; i <= n; i++)
	{
		Type Min = NoEdge;
		for (int j = 1; j <= n; j++)
		{
			if (a[i][j] != NoEdge && (a[i][j] < Min || Min == NoEdge))
			{
				Min = a[i][j];
			}
		}
		if (Min == NoEdge)
		{
			return NoEdge;//无回路
		}
		MinOut[i] = Min;
		MinSum += Min;
	}
	//初始化
	MinHeapNode<Type>E;
	E.x = new int[n];
	for (int i = 0; i < n; i++)
	{
		E.x[i] = i + 1;
	}
	E.s = 0;//根节点到当前结点路劲为x[0:s]
	E.cc = 0;//当前费用
	E.rcost = MinSum;//最小出边费用和
	Type bestc = NoEdge;
	//搜索排列空间树
	while (E.s < n - 1)//非叶节点
	{
		if (E.s == n - 2)
		{
			//再加2条边构成回路
			//所构成回路是否优于当前最优解
			if (a[E.x[n - 2]][E.x[n - 1]] != NoEdge && a[E.x[n - 1]][1] != NoEdge && (E.cc + a[E.x[n - 2]][E.x[n - 1]] + a[E.x[n - 1]][1] < bestc ||bestc==NoEdge))
			{
				//费用更小的回路
				bestc = E.cc + a[E.x[n - 2]][E.x[n - 1]] + a[E.x[n - 1]][1];
				E.cc = bestc;
				E.lcost = bestc;
				E.s++;
				H.Insert(E);
			}
			else
			{
				delete[]E.x;
			}
		}
		else//产生当前扩展节点的儿子节点
		{
			for (int i = E.s + 1; i < n; i++)
			{
				if (a[E.x[E.s]][E.x[i]] != NoEdge)
				{
					//可行儿子节点
					Type cc = E.cc + a[E.x[E.s]][E.x[i]];
					Type rcost = E.rcost - MinOut[E.x[E.s]];
					Type b = cc + rcost;//下界
					if (b < bestc || bestc == NoEdge)
					{
						//子树可能含有最优解
						//节点插入最小堆
						MinHeapNode<Type>N;
						N.x = new int[n];
						for (int j = 0; j < n; j++)
						{
							N.x[j] = E.x[j];
						}
						N.x[E.s + 1] = E.x[i];
						N.x[i] = E.x[E.s + 1];
						N.cc = cc;
						N.s = E.s + 1;
						N.lcost = b;
						N.rcost = rcost;
						H.Insert(N);
					}
				}
			}
			delete[] E.x;//完成节点扩展
		}
		if (H.Size() == 0)
		{
			break;
		}
		H.DeleteMin(E);//取下一个扩展节点
	}
	if (bestc == NoEdge)
	{
		return NoEdge;//无回路
	}
	//将最优解复制到v[1:n]
	for (int i = 0; i < n; i++)
	{
		v[i + 1] = E.x[i];
	}
	while (true)
	{
		//释放最小堆中的所有节点
		delete[]E.x;
		if (H.Size() == 0)
			break;
		H.DeleteMin(E);//取下一个节点
	}
	return bestc;
}