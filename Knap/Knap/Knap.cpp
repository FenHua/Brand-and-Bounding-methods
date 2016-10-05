/*Knap.cpp : �������̨Ӧ�ó������ڵ㡣
�㷨���
���ȣ�Ҫ���������ݽ���Ԥ����������Ʒ���䵥λ������ֵ�Ӵ�С�������С������ȶ��з�֧�޽編�У���
������ȼ�����װ������Ʒ��ֵ����ʣ�µ����λ������ֵ����Ʒװ��ʣ�������ļ�ֵ�͡�
�㷨���ȼ�鵱ǰ��չ��������ӽ��Ŀ����ԡ����������ӽ���ǿ��н�㣬�������뵽�Ӽ����ͻ��
�����ȶ����С���ǰ��չ�����Ҷ��ӽ��һ���ǿ��н�㣬�����Ҷ��ӽ�������Ͻ�Լ��ʱ�Ž��������Ӽ���
�ͻ������ȶ��С�����չ��Ҷ�ڵ�ʱΪ���������ֵ��
*/

#include "stdafx.h"
#include"MaxHeap.h"
#include<iostream>
using namespace std;
class Object
{
	template<class Typew, class Typep>friend Typep Knapsack(Typep p[], Typew w[], Typew c, int n, int bestx[]);
public:
	int operator<=(Object a)const
	{
		return (d >= a.d);
	}
private:
	int ID;
	float d;//��λ������ֵ
};
template<class Typew, class Typep>class Knap;
class bbnode
{
	friend Knap<int, int>;
	template<class Typew, class Typep>friend Typep Knapsack(Typep p[], Typew w[], Typew c, int n, int bestx[]);
private:
	bbnode*parent;//ָ�򸸽ڵ��ָ��
	bool LChild;//����ӽڵ��ʶ
};
template<class Typew, class Typep>class HeapNode
{
	friend Knap<Typew, Typep>;
public:
	operator Typep()const
	{
		return uprofit;
	}
private:
	Typep uprofit,//�ڵ�ļ�ֵ�Ͻ�
		profit;//�ڵ�����Ӧ�ļ�ֵ
	Typew weight;//�ڵ�����Ӧ������
	int level;//��ڵ��������������Ĳ����
	bbnode*ptr;//ָ���ڵ����Ӽ���Ӧ�ڵ��ָ��
};
template<class Typew, class Typep>class Knap
{
	template<class Typew, class Typep>friend Typep Knapsack(Typep p[], Typew w[], Typew c, int n, int bestx[]);
public:
	Typep MaxKnapsack();
private:
	MaxHeap<HeapNode<Typep, Typew>>*H;
	Typep Bound(int i);
	void AddLiveNode(Typep up, Typep cp, Typew cw, bool ch, int lev);
	bbnode*E;//ָ����չ�ڵ��ָ��
	Typew c;//��������
	int n;//��Ʒ��
	Typew *w;//��Ʒ��������
	Typep*p;//��Ʒ��ֵ����
	Typew cw;//��ǰ����
	Typep cp;//��ǰ��ֵ
	int*bestx;//���Ž�
};
template<class Type>inline void Swap(Type&a, Type&b);
template<class Type>void BubbleSort(Type a[], int n);

int main()
{
	int n = 3;//��Ʒ��    
	int c = 30;//��������    
	int p[] = { 0, 45, 25, 25 };//��Ʒ��ֵ �±��1��ʼ    
	int w[] = { 0, 16, 15, 15 };//��Ʒ���� �±��1��ʼ    
	int bestx[4];//���Ž�  
	cout << "��������Ϊ��"<<c<< endl;
	cout << "��Ʒ�����ͼ�ֵ�ֱ�Ϊ��" << endl;
	for (int i = 1; i <= n; i++)
	{
		cout << "(" << w[i] << "," << p[i] << ")";
	}
	cout << endl;
	cout << "������װ�µ�����ֵ��Ϊ��" << Knapsack(p, w, c, n, bestx) << endl;
	cout << "�˱����������Ž�Ϊ��" <<endl;
	for (int i = 1; i <= n; i++)
	{
		cout << bestx[i] << " ";
	}
	cout << endl;
	return 0;
}

template<class Typew, class Typep>Typep Knap<Typew, Typep>::Bound(int i)//����ڵ�����Ӧ��ֵ���Ͻ�
{
	Typew cleft = c - cw;//ʣ��������
	Typep b = cp;//��ֵ�Ͻ�
	//����Ʒ��λ������ֵ�ݼ���װ��ʣ������
	while ((i <= n) && (w[i] <= cleft))
	{
		cleft -= w[i];
		b += p[i];
		i++;
	}
	//װ��ʣ������װ������
	if (i <= n)
	{
		b += p[i] / w[i] * cleft;
	}
	return b;
}
//��һ����ڵ���뵽�Ӽ��������ȶ�����
template<class Typew, class Typep>void Knap<Typew, Typep>::AddLiveNode(Typep up, Typep cp, Typew cw, bool ch, int lev)
{
	bbnode*b = new bbnode;
	b->parent = E;
	b->LChild = ch;
	HeapNode<Typep, Typew>N;
	N.uprofit = up;
	N.profit = cp;
	N.weight = cw;
	N.level = lev;
	N.ptr = b;
	H->Insert(N);
}
//���ȶ���ʽ��֧�޽編���������ֵ��bestx�������Ž�
template<class Typew,class Typep>
Typep Knap<Typew, Typep>::MaxKnapsack()
{
	H = new MaxHeap<HeapNode<Typep, Typew>>(1000);
	//Ϊbestx����洢�ռ�
	bestx = new int[n + 1];
	//��ʼ��
	int i = 1; E = 0; cw = cp = 0;
	Typep bestp = 0;//��ǰ����ֵ
	Typep up = Bound(1);//��ֵ�Ͻ�
	while (i != n + 1)//�����Ӽ��ռ���
	{
		//��鵱ǰ��չ�ڵ������ӽڵ�
		Typew wt = cw + w[i];
		if (wt <= c)//����ӽڵ�Ϊ���нڵ�
		{
			if (cp + p[i] > bestp)
			{
				bestp = cp + p[i];
			}
			AddLiveNode(up, cp + p[i], cw + w[i], true, i + 1);
		}
		up = Bound(i + 1);
		//��鵱ǰ��չ�ڵ���Ҷ��ӽڵ�
		if (up >= bestp)//���������ܺ������Ž�
		{
			AddLiveNode(up, cp, cw, false, i + 1);
		}
		//ȡ��һ����չ�ڵ�
		HeapNode<Typep, Typew>N;
		H->DeleteMax(N);
		E = N.ptr;
		cw = N.weight;
		cp = N.profit;
		up = N.uprofit;
		i = N.level;
	}
	//���쵱ǰ���Ž�
	for (int j = n; j > 0; j--)
	{
		bestx[j] = E->LChild;
		E = E->parent;
	}
	return cp;
}
//��������ֵ��bestx�������Ž�
template<class Typew,class Typep>Typep
Knapsack(Typep p[], Typew w[], Typew c, int n, int bestx[])
{
	//��ʼ��
	Typew W = 0;//װ����Ʒ����
	Typep P = 0;//װ����Ʒ��ֵ
	//�������ݵ�λ������ֵ�������Ʒ����
	Object*Q = new Object[n];
	for (int i = 1; i <= n; i++)
	{
		//��λ������ֵ����
		Q[i - 1].ID =i;
		Q[i - 1].d =1.0*p[i] / w[i];
		P += p[i];
		W += w[i];
	}
	if (W <= c)
	{
		return P;//������Ʒװ��
	}
	//���ݵ�λ��ֵ��������
	BubbleSort(Q, n);
	//������Knap�����ݳ�Ա
	Knap<Typew, Typep>K;
	K.p = new Typep[n + 1];
	K.w = new Typew[n + 1];
	for (int i = 1; i <= n; i++)
	{
		K.p[i] = p[Q[i - 1].ID];
		K.w[i] = w[Q[i - 1].ID];
	}
	K.cp = 0;
	K.cw = 0;
	K.c = c;
	K.n = n;
	//����MaxKnapsack����������Ž�
	Typep bestp = K.MaxKnapsack();
	for (int j = 1; j <= n; j++)
	{
		bestx[Q[j - 1].ID] = K.bestx[j];
	}
	delete Q;
	delete[]K.w;
	delete[]K.p;
	delete[]K.bestx;
	return bestp;
}
template<class Type>void BubbleSort(Type a[], int n)
{
	int i, j;
	for (j = 0; j < n - 1; j++)
	{
		for (i = 0; i < n - 1 - j; i++)
		{
			if (a[i + 1] <= a[i])
			{
				Swap(a[i], a[i + 1]);
			}
		}
	}
}
template<class Type>inline void Swap(Type&a, Type&b)
{
	Type temp = a;
	a = b;
	b = temp;
}