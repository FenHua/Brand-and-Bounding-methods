/*BBFlowShop.cpp : 定义控制台应用程序的入口点。
算法描述
算法中用最小堆表示活节点优先队列。最小堆中元素类型是MinHeapNode。每一个MinHeapNode类型的节点包含域x,用来表示节点所相应的作业调度。s表示该作业已安排的作业时x[1:s]。
f1表示当前已安排的作业在机器1上的最后完成时间；f2表示当前已安排作业在机器2上的完成时间；sf2表示当前已安排的作业在机器2上的完成时间和；bb表示当前完成时间和下界。二维数
组M表示所给的n个作业在机器1和机器2所需的处理时间。在类Flowshop中用二维数组b存储排好序的作业处理时间。数组a表示数组M和b的对应关系。算法Sort实现对各作业在机器1和2上
所需时间排序。函数Bound用于计算完成时间和下界。
函数BBFlow中while循环完成对排列树内部结点的有序扩展。在while循环体内算法依次从活结点优先队列中取出具有最小bb值（完成时间和下界）的结点作为当前扩展结点，并加以扩展。 算
法将当前扩展节点E分两种情形处理：
1)首先考虑E.s=n的情形，当前扩展结点E是排列树中的叶结点。E.sf2是相应于该叶结点的完成时间和。当E.sf2 < bestc时更新当前最优值bestc和相应的当前最优解bestx。
2)当E.s<n时，算法依次产生当前扩展结点E的所有儿子结点。对于当前扩展结点的每一个儿子结点node，计算出其相应的完成时间和的下界bb。当bb < bestc时，将该儿子结点插入到活结点
优先队列中。而当bb bestc时，可将结点node舍去。
*/

#include "stdafx.h"
#include"MinHeap.h"
#include"iostream"
using namespace std;

class Flowshop;
class MinHeapNode
{
	friend Flowshop;
public:
	operator int() const
	{
		return bb;
	}
private:
	void Init(int);
	void NewNode(MinHeapNode, int, int, int, int);
	int s,//已经安排作业数
		f1,//机器1上最后完成时间
		f2,//机器2上最后完成时间
		sf2,//当前机器2上完成时间和
		bb,//当前完成时间和下界
		*x;//当前作业调度
};
class Flowshop
{
	friend int main(void);
public:
	int BBFlow(void);
private:
	int Bound(MinHeapNode E, int&f1, int&f2, bool**y);
	void Sort(void);
	int n,//作业数
		**M,//各作业所需的处理时间数组
		**b,//各作业所需要的处理时间排序数组
		**a,//数组M和b的对应关系数组
		*bestx,//最优解
		bestc;//最小完成时间和
	bool **y;//工作数组
};
template<class Type>inline void Swap(Type &a, Type&b);


int main()
{
	int n = 3, bf;
	int M1[3][2] = { { 2, 1 }, { 3, 1 }, {2,3} };
	int**M = new int*[n];
	int**b = new int*[n];
	int**a = new int*[n];
	bool **y = new bool*[n];
	int*bestx = new int[n];
	for (int i = 0; i <= n; i++)
	{
		M[i] = new int[2];
		b[i] = new int[2];
		a[i] = new int[2];
		y[i] = new bool[2];
	}
	cout << "各作业所需要的时间处理数组M(i,j)值如下：" << endl;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			M[i][j] = M1[i][j];
		}
	}
	for (int i = 0; i < n; i++)
	{
		cout << "(";
		for (int j = 0; j < 2; j++)
			cout << M[i][j] << " ";
		cout << ")";
	}
	cout << endl;
	Flowshop flow;
	flow.n = n;
	flow.M = M;
	flow.b = b;
	flow.a = a;
	flow.y = y;
	flow.bestx = bestx;
	flow.bestc = 1000;//给初值
	flow.BBFlow();
	cout << "最优值是：" << flow.bestc << endl;
	cout << "最优调度是：";
	for (int i = 0; i < n; i++)
	{
		cout << (flow.bestx[i] + 1) << " ";
	}
	cout << endl;
	for (int i = 0; i < n; i++)
	{
		delete[]M[i];
		delete[]b[i];
		delete[]a[i];
		delete[]y[i];
	}
	return 0;
}

//最小堆节点初始化
void MinHeapNode::Init(int n)
{
	x = new int[n];
	for (int i = 0; i < n; i++)
	{
		x[i] = i;
	}
	s = 0;
	f1 = 0; 
	f2 = 0;
	sf2 = 0;
	bb = 0;
}
//最小堆新节点
void MinHeapNode::NewNode(MinHeapNode E, int Ef1, int Ef2, int Ebb, int n)
{
	x = new int[n];
	for (int i = 0; i < n; i++)
	{
		x[i] = E.x[i];
	}
	f1 = Ef1;
	f2 = Ef2;
	sf2 = E.sf2 + f2;
	bb = Ebb;
	s = E.s + 1;
}
//对各作业在机器1和机器2上所需时间排序
void Flowshop::Sort(void)
{
	int *c = new int[n];
	for (int j = 0; j < 2; j++)
	{
		for (int i = 0; i < n; i++)
		{
			b[i][j] = M[i][j];
			c[i] = i;
		}
		for (int i = 0; i < n - 1; i++)
		{
			for (int k = n - 1; k>i; k--)
			{
				if (b[k][j] < b[k - 1][j])
				{
					Swap(b[k][j], b[k - 1][j]);
					Swap(c[k], c[k - 1]);
				}
			}
		}
		for (int i = 0; i < n; i++)
		{
			a[c[i]][j] = i;
		}
	}
	delete[]c;
}
//计算完成时间和下界
int Flowshop::Bound(MinHeapNode E, int&f1, int&f2, bool**y)
{
	for (int k = 0; k < n; k++)
	{
		for (int j = 0; j < 2; j++)
			y[k][j] = false;
	}
	for (int k = 0; k < E.s; k++)
	{
		for (int j = 0; j < 2; j++)
		{
			y[a[E.x[k]][j]][j] = true;
		}
	}
	f1 = E.f1 + M[E.x[E.s]][0];
	f2 = ((f1>E.f2) ? f1 : E.f2) + M[E.x[E.s]][1];
	int sf2 = E.sf2 + f2;
	int s1 = 0, s2 = 0, k1 = n - E.s, k2 = n - E.s, f3 = f2;
	//计算s1的值
	for (int j = 0; j < n; j++)
	{
		if (!y[j][1])
		{
			k2--;
			s1 += b[j][1];
			s2 += f3 + k2*b[j][1];
		}
	}
	//返回完成时间和下界
	return sf2 + ((s1>s2) ? s1 : s2);
}
//解批处理作业调度问题的优先队列分支限界法
int Flowshop::BBFlow(void)
{
	Sort();//对各作业在机器1和2上所需时间排序
	MinHeap<MinHeapNode>H(1000);
	MinHeapNode E;
	//初始化
	E.Init(n);
	//搜索排列空间树
	while (E.s <= n)
	{
		//叶节点
		if (E.s == n)
		{
			if (E.sf2 < bestc)
			{
				bestc = E.sf2;
				for (int i = 0; i < n; i++)
				{
					bestx[i] = E.x[i];
				}
			}
			delete[]E.x;
		}
		else//产生当前扩展节点的儿子节点
		{
			for (int i = E.s; i < n; i++)
			{
				Swap(E.x[E.s], E.x[i]);
				int f1, f2;
				int bb = Bound(E, f1, f2, y);
				if (bb < bestc)
				{
					//子树可能含有最优解
					//节点插入最小堆
					MinHeapNode N;
					N.NewNode(E, f1, f2, bb, n);
					H.Insert(N);
				}
				Swap(E.x[E.s], E.x[i]);
			}
			delete[]E.x;//完成节点扩展
		}
		if (H.Size() == 0)
			break;
		H.DeleteMin(E);//取下一个扩展节点
	}
	return bestc;
}
template<class Type>inline void Swap(Type&a, Type&b)
{
	Type temp = a;
	a = b;
	b = temp;
}