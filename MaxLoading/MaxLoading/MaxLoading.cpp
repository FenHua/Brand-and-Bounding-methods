/*MaxLoading.cpp : 定义控制台应用程序的入口点。
队列式分支限界法求解
在算法的循环体中，首先检测当前扩展结点的左儿子结点是否为可行结点。如果是则将其加入到活结点队列中。然后将其右儿子结点加入
到活结点队列中(右儿子结点一定是可行结点)。2个儿子结点都产生后，当前扩展结点被舍弃。活结点队列中的队首元素被取出作为当前扩
展结点，由于队列中每一层结点之后都有一个尾部标记-1，故在取队首元素时，活结点队列一定不空。当取出的元素是-1时，再判断当前
队列是否为空。如果队列非空，则将尾部标记-1加入活结点队列，算法开始处理下一层的活结点。节点的左子树表示将此集装箱装上船，右
子树表示不将此集装箱装上船。设bestw是当前最优解；ew是当前扩展结点所相应的重量；r是剩余集装箱的重量。则当ew+r<bestw时，可
将其右子树剪去，因为此时若要船装最多集装箱，就应该把此箱装上船。另外，为了确保右子树成功剪枝，应该在算法每一次进入左子树的时候更新bestw的值。
为了在算法结束后能方便地构造出与最优值相应的最优解，算法必须存储相应子集树中从活结点到根结点的路径。为此目的，可在每个结点处设置指向其父结点的指针，并设置左、右儿子标志。
找到最优值后，可以根据parent回溯到根节点，找到最优解。
*/

#include "stdafx.h"
#include"Queue.h"
#include<iostream>
using namespace std;

const int N = 4;
template<class Type>class QNode
{
	template<class Type>friend void EnQueue(Queue<QNode<Type>*>&Q, Type wt, int i, int n, Type bestw, QNode<Type>*E, QNode<Type>*&bestE, int bestx[], bool ch);
	template<class Type>friend Type MaxLoading(Type w[], Type c, int n, int bestx[]);
private:
	QNode*parent;//指向父节点的指针
	bool LChild;//左儿子标识
	Type Weight;//节点所相应的载重量
};
template<class Type>void EnQueue(Queue<QNode<Type>*>&Q, Type wt, int i, int n, Type bestw, QNode<Type>*E, QNode<Type>*&bestE, int bestx[], bool ch);
template<class Type>Type MaxLoading(Type w[], Type c, int n, int bestx[]);

int main()
{
	float c = 70;
	float w[] = {0, 20, 10, 26, 15};//下标从1开始
	int x[N + 1];
	float bestw;
	cout << "轮船载重为：" << c << endl;
	cout << "待装物品的重量分别为：" << endl;
	for (int i = 1; i <=N; i++)
	{
		cout << w[i] << " ";
	}
	cout << endl;
	bestw = MaxLoading(w, c, N, x);
	cout << "分支限界选择结果为：" << endl;
	for (int i = 1; i <= 4; i++)
	{
		cout << x[i] << " ";
	}
	cout << endl;
	cout << "最优载重量为：" << bestw << endl;
	return 0;
}

//将活节点加入节点列表Q中
template<class Type>void EnQueue(Queue<QNode<Type>*>&Q, Type wt, int i, int n, Type bestw, QNode<Type>*E, QNode<Type>*&bestE, int bestx[], bool ch)
{
	if (i == n)//可行叶节点
	{
		if (wt == bestw)
		{
			//当前最优载重
			bestE = E;
			bestx[n] = ch;
		}
		return;
	}
	//非叶节点
	QNode<Type>*b;
	b = new QNode<Type>;
	b->Weight = wt;
	b->parent = E;
	b->LChild = ch;
	Q.Add(b);
}
template<class Type>Type MaxLoading(Type w[], Type c, int n, int bestx[])
{
	//队列分支限界法，返回最优装载，bestx返回最优解
	//初始化
	Queue<QNode<Type>*>Q;//活节点队列
	Q.Add(0);//同层节点尾部标识
	int i = 1;//当前扩展节点所处的层
	Type Ew = 0,//当前扩展节点所相应的载重量
		bestw = 0,//当前最优载重量
		r = 0;//剩余集装箱重量
	for (int j = 2; j <= n; j++)
	{
		r += w[j];
	}
	QNode<Type>*E = 0,//当前扩展节点
		*bestE=0;//当前最优扩展节点
	//搜索子集空间树
	while (true)
	{
		//检查左儿子节点
		Type wt = Ew + w[i];
		if (wt <= c)//可行节点
		{
			if (wt > bestw)
			{
				bestw = wt;
			}
			EnQueue(Q, wt, i, n, bestw, E, bestE, bestx, true);
		}
		//检查右儿子节点
		if (Ew + r > bestw)
		{
			EnQueue(Q, Ew, i, n, bestw, E, bestE, bestx, false);
		}
		Q.Delete(E);//取下一扩展节点
		if (!E)
		{
			if (Q.IsEmpty())
			{
				break;
			}
			Q.Add(0);//同层接待你尾部标识
			Q.Delete(E);//取下一扩展节点
			i++;//进入下一层
			r -= w[i];//剩余集装箱重量
		}
		Ew = E->Weight;//新扩展节点所对应的载重量
	}
	//构造当前最优解
	for (int j = n - 1; j > 0; j--)
	{
		bestx[j] = bestE->LChild;
		bestE = bestE->parent;
	}
	return bestw;
}