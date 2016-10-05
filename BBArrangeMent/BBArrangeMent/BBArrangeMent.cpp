/* BBArrangeMent.cpp : 定义控制台应用程序的入口点。
算法思路
电路板排列问题的解空间是一颗排列树。采用优先队列式分支限界法找出所给电路板的最小密度布局。算法中采用最小堆表示活节点优先级队列。
最小堆中元素类型是BoradNode，每一个BoardNode类型的节点包含域x，表示节点所相应的电路板排列；s表示该节点已确定的电路板排列x[1:s]；
cd表示当前密度，now[j]表示x[1:s]中所含连接块j中的电路板数。算法开始时，将排列树的根结点置为当前扩展结点。在do-while循环体内算法依次
从活结点优先队列中取出具有最小cd值的结点作为当前扩展结点，并加以扩展。算法将当前扩展节点分两种情形处理：
1)首先考虑s=n-1的情形，当前扩展结点是排列树中的一个叶结点的父结点。x表示相应于该叶结点的电路板排列。计算出与x相应的密度并在必要时
更新当前最优值和相应的当前最优解。
2)当s<n-1时，算法依次产生当前扩展结点的所有儿子结点。对于当前扩展结点的每一个儿子结点node，计算出其相应的密度node.cd。当node.cd<bestd时，
将该儿子结点N插入到活结点优先队列中。
*/

#include "stdafx.h"
#include"MinHeap.h"
#include"iostream"
#include<fstream>
using namespace std;
ifstream fin("C:\\Users\\YAN\\Desktop\\data.txt");
int max(int, int);
class BoardNode
{
	friend int BBArrangeMent(int**, int, int, int*&);
public:
	operator int()const
	{
		return cd;
	}
private:
	int*x,//x[1:n]记录电路板排列
		s,//x[1:s]是当前节点所相应的部分排列
		cd,//x[1:s]的密度
		*now;//now[j]是x[1:s]所含连接块j中电路板数
};
int BBArrangeMent(int**B, int n, int m, int*&bestx);

int main()
{
	int m = 5, n = 8;
	int *bestx;
	cout << "m=" << m << ",n=" << n << endl;
	cout << "N1={4,5,6},N2={2,3},N3={1,3},N4={3,6},N5={7,8}" << endl;
	cout << "二维数组B如下：" << endl;
	int **B = new int*[n + 1];
	for (int i = 1; i <= n; i++)
	{
		B[i] = new int[m + 1];
	}
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			fin >> B[i][j];
			cout << B[i][j] << " ";
		}
		cout << endl;
	}
	cout << "当前最优密度为:" << BBArrangeMent(B, n, m, bestx) << endl;
	cout << "最优排列为：" << endl;
	for (int i = 1; i <= n; i++)
	{
		cout << bestx[i] << " ";
	}
	cout << endl;

	for (int i = 1; i <= n; i++)
	{
		delete[] B[i];
	}
	delete[] B;
	return 0;
}

//解电路板排列问题的优先队列式分支限界法
int BBArrangeMent(int**B, int n, int m, int*&bestx)
{
	MinHeap<BoardNode>H(1000);//活节点最小堆
	BoardNode E;
	E.x = new int[n + 1];
	E.s = 0;
	E.cd = 0;
	E.now = new int[m + 1];//now[i]=x[1:s]所含连接块i中电路板数
	int*total = new int[m + 1];//total[i]=连接块i中的电路板数
	for (int i = 1; i <= m; i++)
	{
		total[i] = 0;
		E.now[i] = 0;
	}
	for (int i = 1; i <= n; i++)
	{
		E.x[i] = i;//初始化为1,2,3...n
		for (int j = 1; j <= m; j++)
		{
			total[j] += B[i][j];//连接块中电路板数
		}
	}
	int bestd = m + 1;
	bestx = 0;
	do//节点扩展
	{
		if (E.s == n - 1)//仅一个儿子节点
		{
			int ld = 0;//最后一块电路板的密度
			for (int j = 1; j <= m; j++)
			{
				ld += B[E.x[n]][j];
			}
			if (ld < bestd)//密度更小的电路排列
			{
				delete[]bestx;
				bestx = E.x;
				bestd = max(ld, E.cd);
			}
			else
			{
				delete[]E.x;
			}
			delete[]E.now;
		}
		else//产生当前扩展节点的所有儿子节点
		{
			for (int i = E.s + 1; i <= n; i++)
			{
				BoardNode N;
				N.now = new int[m + 1];
				for (int j = 1; j <= m; j++)
				{
					//插入新的电路板
					N.now[j] = E.now[j] + B[E.x[i]][j];
				}
				int ld = 0;//新插入的电路板密度
				for (int j = 1; j <= m; j++)
				{
					if (N.now[j] > 0 && total[j] != N.now[j])
					{
						ld++;
					}
				}
				N.cd = max(ld, E.cd);
				if (N.cd < bestd)//可能产生更好的叶子节点
				{
					N.x = new int[n + 1];
					N.s = E.s + 1;
					for (int j = 1; j <= n; j++)
					{
						N.x[j] = E.x[j];
					}
					N.x[N.s] = E.x[i];
					N.x[i] = E.x[N.s];
					H.Insert(N);
				}
				else
				{
					delete[]N.now;
				}
			}
			delete[]E.x;
		}//完成当前节点扩展
		if (H.Size() == 0)
		{
			return bestd;//无扩展节点
		}
		H.DeleteMin(E);
	} while (E.cd < bestd);
	//释放最小堆中所有的节点
	do
	{
		delete[]E.x; 
		delete[]E.now;
		if (H.Size() == 0)
		{
			break;
		}
		H.DeleteMin(E);
	} while (true);
	return bestd;
}
int max(int a, int b)
{
	return (a > b) ? a : b;
}