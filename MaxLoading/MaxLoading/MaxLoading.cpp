/*MaxLoading.cpp : �������̨Ӧ�ó������ڵ㡣
����ʽ��֧�޽編���
���㷨��ѭ�����У����ȼ�⵱ǰ��չ��������ӽ���Ƿ�Ϊ���н�㡣�����������뵽��������С�Ȼ�����Ҷ��ӽ�����
�����������(�Ҷ��ӽ��һ���ǿ��н��)��2�����ӽ�㶼�����󣬵�ǰ��չ��㱻��������������еĶ���Ԫ�ر�ȡ����Ϊ��ǰ��
չ��㣬���ڶ�����ÿһ����֮����һ��β�����-1������ȡ����Ԫ��ʱ���������һ�����ա���ȡ����Ԫ����-1ʱ�����жϵ�ǰ
�����Ƿ�Ϊ�ա�������зǿգ���β�����-1���������У��㷨��ʼ������һ��Ļ��㡣�ڵ����������ʾ���˼�װ��װ�ϴ�����
������ʾ�����˼�װ��װ�ϴ�����bestw�ǵ�ǰ���Ž⣻ew�ǵ�ǰ��չ�������Ӧ��������r��ʣ�༯װ�����������ew+r<bestwʱ����
������������ȥ����Ϊ��ʱ��Ҫ��װ��༯װ�䣬��Ӧ�ðѴ���װ�ϴ������⣬Ϊ��ȷ���������ɹ���֦��Ӧ�����㷨ÿһ�ν�����������ʱ�����bestw��ֵ��
Ϊ�����㷨�������ܷ���ع����������ֵ��Ӧ�����Ž⣬�㷨����洢��Ӧ�Ӽ����дӻ��㵽������·����Ϊ��Ŀ�ģ�����ÿ����㴦����ָ���丸����ָ�룬���������Ҷ��ӱ�־��
�ҵ�����ֵ�󣬿��Ը���parent���ݵ����ڵ㣬�ҵ����Ž⡣
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
	QNode*parent;//ָ�򸸽ڵ��ָ��
	bool LChild;//����ӱ�ʶ
	Type Weight;//�ڵ�����Ӧ��������
};
template<class Type>void EnQueue(Queue<QNode<Type>*>&Q, Type wt, int i, int n, Type bestw, QNode<Type>*E, QNode<Type>*&bestE, int bestx[], bool ch);
template<class Type>Type MaxLoading(Type w[], Type c, int n, int bestx[]);

int main()
{
	float c = 70;
	float w[] = {0, 20, 10, 26, 15};//�±��1��ʼ
	int x[N + 1];
	float bestw;
	cout << "�ִ�����Ϊ��" << c << endl;
	cout << "��װ��Ʒ�������ֱ�Ϊ��" << endl;
	for (int i = 1; i <=N; i++)
	{
		cout << w[i] << " ";
	}
	cout << endl;
	bestw = MaxLoading(w, c, N, x);
	cout << "��֧�޽�ѡ����Ϊ��" << endl;
	for (int i = 1; i <= 4; i++)
	{
		cout << x[i] << " ";
	}
	cout << endl;
	cout << "����������Ϊ��" << bestw << endl;
	return 0;
}

//����ڵ����ڵ��б�Q��
template<class Type>void EnQueue(Queue<QNode<Type>*>&Q, Type wt, int i, int n, Type bestw, QNode<Type>*E, QNode<Type>*&bestE, int bestx[], bool ch)
{
	if (i == n)//����Ҷ�ڵ�
	{
		if (wt == bestw)
		{
			//��ǰ��������
			bestE = E;
			bestx[n] = ch;
		}
		return;
	}
	//��Ҷ�ڵ�
	QNode<Type>*b;
	b = new QNode<Type>;
	b->Weight = wt;
	b->parent = E;
	b->LChild = ch;
	Q.Add(b);
}
template<class Type>Type MaxLoading(Type w[], Type c, int n, int bestx[])
{
	//���з�֧�޽編����������װ�أ�bestx�������Ž�
	//��ʼ��
	Queue<QNode<Type>*>Q;//��ڵ����
	Q.Add(0);//ͬ��ڵ�β����ʶ
	int i = 1;//��ǰ��չ�ڵ������Ĳ�
	Type Ew = 0,//��ǰ��չ�ڵ�����Ӧ��������
		bestw = 0,//��ǰ����������
		r = 0;//ʣ�༯װ������
	for (int j = 2; j <= n; j++)
	{
		r += w[j];
	}
	QNode<Type>*E = 0,//��ǰ��չ�ڵ�
		*bestE=0;//��ǰ������չ�ڵ�
	//�����Ӽ��ռ���
	while (true)
	{
		//�������ӽڵ�
		Type wt = Ew + w[i];
		if (wt <= c)//���нڵ�
		{
			if (wt > bestw)
			{
				bestw = wt;
			}
			EnQueue(Q, wt, i, n, bestw, E, bestE, bestx, true);
		}
		//����Ҷ��ӽڵ�
		if (Ew + r > bestw)
		{
			EnQueue(Q, Ew, i, n, bestw, E, bestE, bestx, false);
		}
		Q.Delete(E);//ȡ��һ��չ�ڵ�
		if (!E)
		{
			if (Q.IsEmpty())
			{
				break;
			}
			Q.Add(0);//ͬ��Ӵ���β����ʶ
			Q.Delete(E);//ȡ��һ��չ�ڵ�
			i++;//������һ��
			r -= w[i];//ʣ�༯װ������
		}
		Ew = E->Weight;//����չ�ڵ�����Ӧ��������
	}
	//���쵱ǰ���Ž�
	for (int j = n - 1; j > 0; j--)
	{
		bestx[j] = bestE->LChild;
		bestE = bestE->parent;
	}
	return bestw;
}