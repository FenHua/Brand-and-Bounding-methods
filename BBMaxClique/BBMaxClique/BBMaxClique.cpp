/* BBMaxClique.cpp : 定义控制台应用程序的入口点。
算法设计
最大团问题的解空间树也是一棵子集树。子集树的根结点是初始扩展结点，对于这个特殊的扩展结点，其cliqueSize的值为0。 
算法在扩展内部结点时，首先考察其左儿子结点。在左儿子结点处，将顶点i加入到当前团中，并检查该顶点与当前团中其它顶
点之间是否有边相连。当顶点i与当前团中所有顶点之间都有边相连，则相应的左儿子结点是可行结点，将它加入到子集树中并
插入活结点优先队列，否则就不是可行结点。
接着继续考察当前扩展结点的右儿子结点。当upperSize>bestn时，右子树中可能含有最优解，此时将右儿子结点加入到子集树
中并插入到活结点优先队列中。算法的while循环的终止条件是遇到子集树中的一个叶结点(即n+1层结点)成为当前扩展结点。
对于子集树中的叶结点，有upperSize＝cliqueSize。此时活结点优先队列中剩余结点的upperSize值均不超过当前扩展结点的
upperSize值，从而进一步搜索不可能得到更大的团，此时算法已找到一个最优解。
*/

#include "stdafx.h"
#include"MaxHeap.h"
#include<iostream>
#include<fstream>
using namespace std;

const int N = 5;//图G的顶点数
ifstream fin("C:\\Users\\YAN\\Desktop\\data.txt");
class bbnode
{
	friend class Clique;
private:
	bbnode*parent;//指向父节点的指针
	bool LChild;//左儿子节点标识
};
class CliqueNode
{
	friend class Clique;
public:
	operator int()const
	{
		return un;
	}
private:
	int cn,//当前团的顶点数
		un,//当前团顶点数的上界
		level;//节点在子集空间树中所处的层次
	bbnode*ptr;//指向活节点在子集树中相应节点的指针
};
class Clique
{
	friend int main();
public:
	int BBMaxClique(int[]);
private:
	void AddLiveNode(MaxHeap<CliqueNode>&H, int cn, int un, int level, bbnode E[], bool ch);
	int **a,//图G 的邻接矩阵
		n;//图G 的顶点数
};


int main()
{
	int bestx[N+1];
	int**a = new int*[N + 1];
	for (int i = 1; i <= N; i++)
	{
		a[i] = new int[N + 1];
	}
	cout << "图G的邻接矩阵为：" << endl;
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			fin >> a[i][j];
			cout << a[i][j] << " ";
		}
		cout << endl;
	}
	Clique c;
	c.a = a;
	c.n = N;
	cout << "图G 的最大团顶点个数为：" << c.BBMaxClique(bestx) << endl;
	cout << "图G 的最大团解向量为：" << endl;
	for (int i = 1; i <= N; i++)
	{
		cout << bestx[i] << " ";
	}
	cout << endl;
	for (int i = 1; i <= N; i++)
	{
		delete[]a[i];
	}
	delete[]a;
	return 0;
}

//将活节点加入到子集空间树并插入到最大堆中
void Clique::AddLiveNode(MaxHeap<CliqueNode>&H, int cn, int un, int level, bbnode E[], bool ch)
{
	bbnode*b = new bbnode;
	b->parent = E;
	b->LChild = ch;
	CliqueNode N;
	N.cn = cn;
	N.ptr = b;
	N.un = un;
	N.level = level;
	H.Insert(N);
}
//解决最大团问题的优先队列分支限界法
int Clique::BBMaxClique(int bestx[])
{
	MaxHeap<CliqueNode>H(1000);
	//初始化
	bbnode*E = 0;
	int i = 1, cn = 0, bestn = 0;
	//搜索子集空间树
	while (i != n + 1)//非叶节点
	{
		//检查顶点i与当前团中其它顶点之间是否右边相连
		bool Ok = true;
		bbnode*B = E;
		for (int j = i - 1; j > 0; B = B->parent, j--)
		{
			if (B->LChild&&a[i][j] == 0)
			{
				Ok = false;
				break;
			}
		}
		if (Ok)//左儿子节点为可行节点
		{
			if (cn + 1 > bestn)
			{
				bestn = cn + 1;
			}
			AddLiveNode(H, cn + 1, cn + n - i + 1, i + 1, E, true);
		}
		if (cn + n - i >= bestn)//右子树可能含最优解
		{
			AddLiveNode(H, cn, cn + n - i, i + 1, E, false);
		}
		//取下一扩展节点
		CliqueNode N;
		H.DeleteMax(N);//堆非空
		E = N.ptr;
		cn = N.cn;
		i = N.level;
	}
	//构造当前最优解
	for (int j = n; j > 0; j--)
	{
		bestx[j] = E->LChild;
		E = E->parent;
	}
	return bestn;
}