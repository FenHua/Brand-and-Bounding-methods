/* BBArrangeMent.cpp : �������̨Ӧ�ó������ڵ㡣
�㷨˼·
��·����������Ľ�ռ���һ�����������������ȶ���ʽ��֧�޽編�ҳ�������·�����С�ܶȲ��֡��㷨�в�����С�ѱ�ʾ��ڵ����ȼ����С�
��С����Ԫ��������BoradNode��ÿһ��BoardNode���͵Ľڵ������x����ʾ�ڵ�����Ӧ�ĵ�·�����У�s��ʾ�ýڵ���ȷ���ĵ�·������x[1:s]��
cd��ʾ��ǰ�ܶȣ�now[j]��ʾx[1:s]���������ӿ�j�еĵ�·�������㷨��ʼʱ�����������ĸ������Ϊ��ǰ��չ��㡣��do-whileѭ�������㷨����
�ӻ������ȶ�����ȡ��������Сcdֵ�Ľ����Ϊ��ǰ��չ��㣬��������չ���㷨����ǰ��չ�ڵ���������δ���
1)���ȿ���s=n-1�����Σ���ǰ��չ������������е�һ��Ҷ���ĸ���㡣x��ʾ��Ӧ�ڸ�Ҷ���ĵ�·�����С��������x��Ӧ���ܶȲ��ڱ�Ҫʱ
���µ�ǰ����ֵ����Ӧ�ĵ�ǰ���Ž⡣
2)��s<n-1ʱ���㷨���β�����ǰ��չ�������ж��ӽ�㡣���ڵ�ǰ��չ����ÿһ�����ӽ��node�����������Ӧ���ܶ�node.cd����node.cd<bestdʱ��
���ö��ӽ��N���뵽�������ȶ����С�
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
	int*x,//x[1:n]��¼��·������
		s,//x[1:s]�ǵ�ǰ�ڵ�����Ӧ�Ĳ�������
		cd,//x[1:s]���ܶ�
		*now;//now[j]��x[1:s]�������ӿ�j�е�·����
};
int BBArrangeMent(int**B, int n, int m, int*&bestx);

int main()
{
	int m = 5, n = 8;
	int *bestx;
	cout << "m=" << m << ",n=" << n << endl;
	cout << "N1={4,5,6},N2={2,3},N3={1,3},N4={3,6},N5={7,8}" << endl;
	cout << "��ά����B���£�" << endl;
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
	cout << "��ǰ�����ܶ�Ϊ:" << BBArrangeMent(B, n, m, bestx) << endl;
	cout << "��������Ϊ��" << endl;
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

//���·��������������ȶ���ʽ��֧�޽編
int BBArrangeMent(int**B, int n, int m, int*&bestx)
{
	MinHeap<BoardNode>H(1000);//��ڵ���С��
	BoardNode E;
	E.x = new int[n + 1];
	E.s = 0;
	E.cd = 0;
	E.now = new int[m + 1];//now[i]=x[1:s]�������ӿ�i�е�·����
	int*total = new int[m + 1];//total[i]=���ӿ�i�еĵ�·����
	for (int i = 1; i <= m; i++)
	{
		total[i] = 0;
		E.now[i] = 0;
	}
	for (int i = 1; i <= n; i++)
	{
		E.x[i] = i;//��ʼ��Ϊ1,2,3...n
		for (int j = 1; j <= m; j++)
		{
			total[j] += B[i][j];//���ӿ��е�·����
		}
	}
	int bestd = m + 1;
	bestx = 0;
	do//�ڵ���չ
	{
		if (E.s == n - 1)//��һ�����ӽڵ�
		{
			int ld = 0;//���һ���·����ܶ�
			for (int j = 1; j <= m; j++)
			{
				ld += B[E.x[n]][j];
			}
			if (ld < bestd)//�ܶȸ�С�ĵ�·����
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
		else//������ǰ��չ�ڵ�����ж��ӽڵ�
		{
			for (int i = E.s + 1; i <= n; i++)
			{
				BoardNode N;
				N.now = new int[m + 1];
				for (int j = 1; j <= m; j++)
				{
					//�����µĵ�·��
					N.now[j] = E.now[j] + B[E.x[i]][j];
				}
				int ld = 0;//�²���ĵ�·���ܶ�
				for (int j = 1; j <= m; j++)
				{
					if (N.now[j] > 0 && total[j] != N.now[j])
					{
						ld++;
					}
				}
				N.cd = max(ld, E.cd);
				if (N.cd < bestd)//���ܲ������õ�Ҷ�ӽڵ�
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
		}//��ɵ�ǰ�ڵ���չ
		if (H.Size() == 0)
		{
			return bestd;//����չ�ڵ�
		}
		H.DeleteMin(E);
	} while (E.cd < bestd);
	//�ͷ���С�������еĽڵ�
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