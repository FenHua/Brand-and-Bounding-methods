/*BBTSP.cpp : �������̨Ӧ�ó������ڵ㡣
�㷨˼·
�����ۻ�Ա����Ľ�ռ������֯��һ�����������ĸ���㵽��һҶ����·��������ͼ��һ������·�ߡ������ۻ�Ա����Ҫ��ͼG���ҳ�������С������·�ߡ�·����һ����Ȩͼ��
ͼ�и��ߵķ��ã�Ȩ��Ϊ������ͼ��һ������·���ǰ���V�е�ÿ���������ڵ�һ����·������·�ߵķ���������·�������бߵķ���֮�͡��㷨��ʼʱ����һ����С�ѣ����ڱ�ʾ��
������ȶ��С�����ÿ�������������õ��½�lcostֵ�����ȶ��е����ȼ��������㷨�����ͼ��ÿ���������С���ó��߲���minout��¼���������������ͼ��ĳ������û�г��ߣ�
���ͼ�������л�·���㷨������������ÿ�����㶼�г��ߣ�����ݼ������minout���㷨��ʼ����
�㷨��whileѭ������ɶ��������ڲ�������չ�����ڵ�ǰ��չ��㣬�㷨��2��������д���
1�����ȿ���s=n-2�����Σ���ʱ��ǰ��չ�������������ĳ��Ҷ���ĸ���㡣�����Ҷ�����Ӧһ�����л�·�ҷ���С�ڵ�ǰ��С���ã��򽫸�Ҷ�����뵽���ȶ����У�������ȥ��Ҷ��㡣
2����s<n-2ʱ���㷨���β�����ǰ��չ�������ж��ӽ�㡣���ڵ�ǰ��չ�������Ӧ��·����x[0:s]������ж��ӽ���Ǵ�ʣ�ඥ��x[s+1:n-1]��ѡȡ�Ķ���x[i]����(x[s]��x[i])����������ͼG��
��һ���ߡ����ڵ�ǰ��չ����ÿһ�����ж��ӽ�㣬�������ǰ׺(x[0:s]��x[i])�ķ���cc����Ӧ���½�lcost����lcost<bestcʱ����������ж��ӽ����뵽�������ȶ����С�
�㷨��whileѭ������ֹ��������������һ��Ҷ����Ϊ��ǰ��չ��㡣��s=n-1ʱ�����ҵ��Ļ�·ǰ׺��x[0:n-1]�����Ѱ���ͼG������n�����㡣��ˣ���s=n-1ʱ����Ӧ����չ����ʾһ��Ҷ
��㡣��ʱ��Ҷ�������Ӧ�Ļ�·�ķ��õ���cc��lcost��ֵ��ʣ��Ļ����lcostֵ��С�����ҵ��Ļ�·�ķ��á����Ƕ������ܵ��·��ø�С�Ļ�·��������ҵ���Ҷ�������Ӧ�Ļ�·��һ����
С���������ۻ�Ա��·���㷨���Խ������㷨����ʱ�����ҵ�����С���ã���Ӧ�����Ž�������v������
*/

#include "stdafx.h"
#include"MinHeap.h"
#include"iostream"
#include<fstream>
using namespace std;

ifstream fin("C:\\Users\\YAN\\Desktop\\data.txt");
const int N = 4;//ͼ�Ķ������
template<class Type>class Traveling
{
	friend int main();
public:
	Type BBTSP(int v[]);
private:
	int n;//ͼG �Ķ�����
	Type **a,//ͼG ���ڽӾ���
		NoEdge,//ͼG���ޱ߱�ʶ
		cc,//��ǰ�ķ���
		bestc;//��ǰ��С����
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
	Type lcost,//�������õ��½�
		cc,//��ǰ����
		rcost;//x[s:n-1]�ж�����С���߷��ú�
	int s,//���ڵ㵽��ǰ����·��Ϊ��x[0:s]
		*x;//��Ҫ��һ�������Ķ���ʱs[s+1,n-1]
};


int main()
{
	int bestx[N + 1];
	cout << "ͼ�Ķ������n=" << N << endl;
	int**a = new int*[N + 1];
	for (int i = 0; i <= N; i++)
	{
		a[i] = new int[N + 1];
	}
	cout << "ͼ���ڽӾ���Ϊ��" << endl;
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
	cout << "��̻�·�ĳ�Ϊ��" << t.BBTSP(bestx) << endl;
	cout << "��̻�·Ϊ��" << endl;
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

//���������ۻ���������ȶ��з�֧�޽編
template<class Type>Type Traveling<Type>::BBTSP(int v[])
{
	MinHeap<MinHeapNode<Type>>H(1000);
	Type*MinOut = new Type[n + 1];
	//����MinOut[i]=����i����С���߷���
	Type MinSum = 0;//��С���߷��ú�
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
			return NoEdge;//�޻�·
		}
		MinOut[i] = Min;
		MinSum += Min;
	}
	//��ʼ��
	MinHeapNode<Type>E;
	E.x = new int[n];
	for (int i = 0; i < n; i++)
	{
		E.x[i] = i + 1;
	}
	E.s = 0;//���ڵ㵽��ǰ���·��Ϊx[0:s]
	E.cc = 0;//��ǰ����
	E.rcost = MinSum;//��С���߷��ú�
	Type bestc = NoEdge;
	//�������пռ���
	while (E.s < n - 1)//��Ҷ�ڵ�
	{
		if (E.s == n - 2)
		{
			//�ټ�2���߹��ɻ�·
			//�����ɻ�·�Ƿ����ڵ�ǰ���Ž�
			if (a[E.x[n - 2]][E.x[n - 1]] != NoEdge && a[E.x[n - 1]][1] != NoEdge && (E.cc + a[E.x[n - 2]][E.x[n - 1]] + a[E.x[n - 1]][1] < bestc ||bestc==NoEdge))
			{
				//���ø�С�Ļ�·
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
		else//������ǰ��չ�ڵ�Ķ��ӽڵ�
		{
			for (int i = E.s + 1; i < n; i++)
			{
				if (a[E.x[E.s]][E.x[i]] != NoEdge)
				{
					//���ж��ӽڵ�
					Type cc = E.cc + a[E.x[E.s]][E.x[i]];
					Type rcost = E.rcost - MinOut[E.x[E.s]];
					Type b = cc + rcost;//�½�
					if (b < bestc || bestc == NoEdge)
					{
						//�������ܺ������Ž�
						//�ڵ������С��
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
			delete[] E.x;//��ɽڵ���չ
		}
		if (H.Size() == 0)
		{
			break;
		}
		H.DeleteMin(E);//ȡ��һ����չ�ڵ�
	}
	if (bestc == NoEdge)
	{
		return NoEdge;//�޻�·
	}
	//�����Ž⸴�Ƶ�v[1:n]
	for (int i = 0; i < n; i++)
	{
		v[i + 1] = E.x[i];
	}
	while (true)
	{
		//�ͷ���С���е����нڵ�
		delete[]E.x;
		if (H.Size() == 0)
			break;
		H.DeleteMin(E);//ȡ��һ���ڵ�
	}
	return bestc;
}