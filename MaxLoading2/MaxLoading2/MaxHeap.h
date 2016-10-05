template<class T>class MaxHeap
{
private:
	int CurrentSize, MaxSize;
	T*heap;//元素数组
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
	//构建堆
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
	//寻找新元素x的位置，i初始化为新的叶节点的位置，逐层向上，寻找最终位置
	int i = ++CurrentSize;
	while ((i != 1) && (x > heap[i / 2]))
	{
		//i不是根节点，且其值大于父节点的值，需要继续调整
		heap[i] = heap[i / 2];//父节点下降
		i /= 2;
	}
	heap[i] = x;
	return *this;
}
template<class T>MaxHeap<T>&MaxHeap<T>::DeleteMax(T&x)
{
	//将x设置为最大元素，并且删除最大元素
	if (CurrentSize == 0)
	{
		cout << "Empty heap!" << endl;
		return *this;
	}
	x = heap[1];//删除最大元素
	//重新调整
	T y = heap[CurrentSize--];//取最后一个节点，从根开始调整
	//find place for y starting at root
	int i = 1,//current node of heap
		ci = 2;//child of i
	while (ci <= CurrentSize)
	{
		//使ci指向i的两个孩子中较大者
		if ((ci <CurrentSize)&&(heap[ci]<heap[ci+1]))
		{
			ci++;
		}
		//y的值大于等于孩子节点？
		if (y >= heap[ci])
		{
			break;//是，i就是y的正确位置，退出
		}
		//否，需要继续向下，重整堆
		heap[i] = heap[ci];//大于父节点的孩子节点上升
		i = ci;
		ci *= 2;
	}
	heap[i] = y;
	return *this;
}
template<class T>void MaxHeap<T>::Initialize(T a[], int size, int ArraySize)
{
	//用a初始化堆
	delete[]heap;
	heap = a;
	CurrentSize = size;
	MaxSize = ArraySize;
	//从最后一个内部节点开始，一直到根，对每一个字树进行重整
	for (int i = CurrentSize / 2; i >= 1; i--)
	{
		T y = heap[i];//子树根节点元素
		//找到放元素y的位置
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