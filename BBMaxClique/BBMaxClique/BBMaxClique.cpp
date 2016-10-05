/* BBMaxClique.cpp : �������̨Ӧ�ó������ڵ㡣
�㷨���
���������Ľ�ռ���Ҳ��һ���Ӽ������Ӽ����ĸ�����ǳ�ʼ��չ��㣬��������������չ��㣬��cliqueSize��ֵΪ0�� 
�㷨����չ�ڲ����ʱ�����ȿ���������ӽ�㡣������ӽ�㴦��������i���뵽��ǰ���У������ö����뵱ǰ����������
��֮���Ƿ��б�������������i�뵱ǰ�������ж���֮�䶼�б�����������Ӧ������ӽ���ǿ��н�㣬�������뵽�Ӽ����в�
����������ȶ��У�����Ͳ��ǿ��н�㡣
���ż������쵱ǰ��չ�����Ҷ��ӽ�㡣��upperSize>bestnʱ���������п��ܺ������Ž⣬��ʱ���Ҷ��ӽ����뵽�Ӽ���
�в����뵽�������ȶ����С��㷨��whileѭ������ֹ�����������Ӽ����е�һ��Ҷ���(��n+1����)��Ϊ��ǰ��չ��㡣
�����Ӽ����е�Ҷ��㣬��upperSize��cliqueSize����ʱ�������ȶ�����ʣ�����upperSizeֵ����������ǰ��չ����
upperSizeֵ���Ӷ���һ�����������ܵõ�������ţ���ʱ�㷨���ҵ�һ�����Ž⡣
*/

#include "stdafx.h"
#include"MaxHeap.h"
#include<iostream>
#include<fstream>
using namespace std;

const int N = 5;//ͼG�Ķ�����
ifstream fin("C:\\Users\\YAN\\Desktop\\data.txt");
class bbnode
{
	friend class Clique;
private:
	bbnode*parent;//ָ�򸸽ڵ��ָ��
	bool LChild;//����ӽڵ��ʶ
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
	int cn,//��ǰ�ŵĶ�����
		un,//��ǰ�Ŷ��������Ͻ�
		level;//�ڵ����Ӽ��ռ����������Ĳ��
	bbnode*ptr;//ָ���ڵ����Ӽ�������Ӧ�ڵ��ָ��
};
class Clique
{
	friend int main();
public:
	int BBMaxClique(int[]);
private:
	void AddLiveNode(MaxHeap<CliqueNode>&H, int cn, int un, int level, bbnode E[], bool ch);
	int **a,//ͼG ���ڽӾ���
		n;//ͼG �Ķ�����
};


int main()
{
	int bestx[N+1];
	int**a = new int*[N + 1];
	for (int i = 1; i <= N; i++)
	{
		a[i] = new int[N + 1];
	}
	cout << "ͼG���ڽӾ���Ϊ��" << endl;
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
	cout << "ͼG ������Ŷ������Ϊ��" << c.BBMaxClique(bestx) << endl;
	cout << "ͼG ������Ž�����Ϊ��" << endl;
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

//����ڵ���뵽�Ӽ��ռ��������뵽������
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
//����������������ȶ��з�֧�޽編
int Clique::BBMaxClique(int bestx[])
{
	MaxHeap<CliqueNode>H(1000);
	//��ʼ��
	bbnode*E = 0;
	int i = 1, cn = 0, bestn = 0;
	//�����Ӽ��ռ���
	while (i != n + 1)//��Ҷ�ڵ�
	{
		//��鶥��i�뵱ǰ������������֮���Ƿ��ұ�����
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
		if (Ok)//����ӽڵ�Ϊ���нڵ�
		{
			if (cn + 1 > bestn)
			{
				bestn = cn + 1;
			}
			AddLiveNode(H, cn + 1, cn + n - i + 1, i + 1, E, true);
		}
		if (cn + n - i >= bestn)//���������ܺ����Ž�
		{
			AddLiveNode(H, cn, cn + n - i, i + 1, E, false);
		}
		//ȡ��һ��չ�ڵ�
		CliqueNode N;
		H.DeleteMax(N);//�ѷǿ�
		E = N.ptr;
		cn = N.cn;
		i = N.level;
	}
	//���쵱ǰ���Ž�
	for (int j = n; j > 0; j--)
	{
		bestx[j] = E->LChild;
		E = E->parent;
	}
	return bestn;
}