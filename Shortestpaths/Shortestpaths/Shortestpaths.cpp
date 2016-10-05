/*Shortestpaths.cpp : �������̨Ӧ�ó������ڵ㡣
��֧�޽編
(1)���������ù�����Ȳ���״̬�ռ����Ľ�㣬��ʹ�ü�֦�����ķ�����Ϊ��֦�޽編��
��ν����֧���ǲ��ù�����ȵĲ��ԣ�����������չ�������з�֧���������ӽ�㣩��
��ν���޽硱���ڽ����չ�����У���������Ͻ磨���½磩���������߼�����������ĳЩ��֧���Ӷ��������Ч�ʡ�
(2)ԭ�����չ�����ȵ�ԭ��һ������һ����Ϊ��չ��㣨E-��㣩R���㷨��������������ȫ�����ӽ�㣬����Щ���²����н���·����Ž�Ķ���������������Ӽ��������С�Ȼ�󣬴ӻ������ȡ��һ�������Ϊ��ǰ��չ��㡣�ظ����������չ���̣�ֱ���ҵ�����Ľ���ж��޽�Ϊֹ��
(3)��֧�޽編����ݷ�
1)���Ŀ�꣺���ݷ������Ŀ�����ҳ���ռ���������Լ�����������н⣬����֧�޽編�����Ŀ�������ҳ�����Լ��������һ���⣬����������Լ�������Ľ����ҳ���ĳ�������µ����Ž⡣
2)������ʽ�Ĳ�ͬ�����ݷ���������ȵķ�ʽ������ռ���������֧�޽編���Թ�����Ȼ�����С�ķ����ȵķ�ʽ������ռ�����
�����ķ�֧�޽編��1)FIFO��֧�޽編(����ʽ��֧�޽編)  2)LC(least cost)��֧�޽編(���ȶ���ʽ��֧�޽編)
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
	int n,//ͼG�Ķ�����
		*prev;//ǰ����������
	Type **c,//ͼD ���ڽӾ���
		*dist;//��̾�������
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
	int i;//������
	Type length;//��ǰ·��
};
template<class Type>void Graph<Type>::ShortestPaths(int v)//��Դ���·����������ȶ���ʽ��֧�޽編
{
	MinHeap<MinHeapNode<Type>>H(1000);
	MinHeapNode<Type>E;
	//����ԴΪ��ʼ��չ�ڵ�
	E.i = v;
	E.length = 0;
	dist[v] = 0;
	while (true)//��������Ľ�ռ�
	{
		for (int j = 1; j <= n; j++)
		{
			if ((c[E.i][j] != 0) && (E.length + c[E.i][j] < dist[j]))
			{
				//����i������j�ɴ���������Լ��
				dist[j] = E.length + c[E.i][j];
				prev[j] = E.i;
				//�����ڵ����ȶ���
				MinHeapNode<Type>N;
				N.i = j;
				N.length = dist[j];
				H.Insert(N);
			}
		}
		try
		{
			H.DeleteMin(E);//ȡ��һ��չ���
		}
		catch (int )
		{
			break;
		}
		if (H.currentsize == 0)//���ȶ��п�
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
	cout << "��Դͼ���ڽӾ������£�" << endl;
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
	cout << "��S��T�����·���ǣ�" << dist[11] << endl;
	for (int i = 2; i <= n; i++)
	{
		cout << "prev(" << i << ")=" << prev[i] << " " << endl;
	}
	for (int i = 2; i <= n; i++)
	{
		cout << "��1��" << i << "�����·��Ϊ��" << dist[i] << endl;
	}
	for (int i = 1; i <= n; i++)
	{
		delete[]c[i];
	}
	delete[]c;
	return 0;
}

