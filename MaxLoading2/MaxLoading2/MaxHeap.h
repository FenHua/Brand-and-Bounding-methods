template<class T>class MaxHeap
{
private:
	int CurrentSize, MaxSize;
	T*heap;//Ԫ������
public:
	MaxHeap(int MaxHeapSize=10);
	~MaxHeap(){ delete[]heap; }
	int Size()const
	{
		return CurrentSize;
	}
	T Max()
	{
		if (CurrentSize == 0)
		{
			throw OutOfBounds();
		}
		return heap[1];
	}
	MaxHeap<T>&Insert(const T&x);
	MaxHeap<T>&DeleteMax(T&x);
	void Initialize(T a[], int size, int ArraySize);
};
template<class T>MaxHeap<T>::MaxHeap(int MaxHeapSize)
{
	//������
	MaxSize = MaxHeapSize;
	heap = new T[MaxSize + 1];
	CurrentSize = 0;
}
template<class T>MaxHeap<T>&MaxHeap<T>::Insert(const T&x)
{
	if (CurrentSize == MaxSize)
	{
		cout << "no space!" << endl;
		return *this;
	}
	//Ѱ����Ԫ��x��λ�ã�i��ʼ��Ϊ�µ�Ҷ�ڵ��λ�ã�������ϣ�Ѱ������λ��
	int i = ++CurrentSize;
	while ((i != 1) && (x > heap[i / 2]))
	{
		//i���Ǹ��ڵ㣬����ֵ���ڸ��ڵ��ֵ����Ҫ��������
		heap[i] = heap[i / 2];//���ڵ��½�
		i /= 2;
	}
	heap[i] = x;
	return *this;
}
template<class T>MaxHeap<T>&MaxHeap<T>::DeleteMax(T&x)
{
	//��x����Ϊ���Ԫ�أ�����ɾ�����Ԫ��
	if (CurrentSize == 0)
	{
		cout << "Empty heap!" << endl;
		return *this;
	}
	x = heap[1];//ɾ�����Ԫ��
	//���µ���
	T y = heap[CurrentSize--];//ȡ���һ���ڵ㣬�Ӹ���ʼ����
	//find place for y starting at root
	int i = 1,//current node of heap
		ci = 2;//child of i
	while (ci <= CurrentSize)
	{
		//ʹciָ��i�����������нϴ���
		if ((ci <CurrentSize)&&(heap[ci]<heap[ci+1]))
		{
			ci++;
		}
		//y��ֵ���ڵ��ں��ӽڵ㣿
		if (y >= heap[ci])
		{
			break;//�ǣ�i����y����ȷλ�ã��˳�
		}
		//����Ҫ�������£�������
		heap[i] = heap[ci];//���ڸ��ڵ�ĺ��ӽڵ�����
		i = ci;
		ci *= 2;
	}
	heap[i] = y;
	return *this;
}
template<class T>void MaxHeap<T>::Initialize(T a[], int size, int ArraySize)
{
	//��a��ʼ����
	delete[]heap;
	heap = a;
	CurrentSize = size;
	MaxSize = ArraySize;
	//�����һ���ڲ��ڵ㿪ʼ��һֱ��������ÿһ��������������
	for (int i = CurrentSize / 2; i >= 1; i--)
	{
		T y = heap[i];//�������ڵ�Ԫ��
		//�ҵ���Ԫ��y��λ��
		int c = 2 * i;//parent of c is target
		// location for y
		while (c <= CurrentSize)
		{
			//heap[c]should be larger sibling
			if ((c < CurrentSize) && (heap[c] < heap[c + 1]))
			{
				c++;
			}
			//can we put y in heap[c/2]
			if (y>heap[c])
			{
				break;//yes
			}
			heap[c / 2] = heap[c];//move child up
			c *= 2;//move down a level
		}
		heap[c / 2] = y;
	}
}