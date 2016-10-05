template<class T>class MaxHeap
{
private:
	int CurrentSize, MaxSize;
	T*heap;//element array
public:
	MaxHeap(int MaxHeapSize = 10);
	~MaxHeap(){ delete[]heap; }
	int Size()const
	{
		return CurrentSize;
	}
	T Max()
	{
		if (CurrentSize == 0)
			throw OutOfBounds();
		return heap[1];
	}
	MaxHeap<T>&Insert(const T&x);//增
	MaxHeap<T>&DeleteMax(T&x);//删
	void Initialize(T a[], int size, int ArraySzie);
};
template<class T>MaxHeap<T>::MaxHeap(int MaxHeapSize)
{
	MaxSize = MaxHeapSize;
	heap = new T[MaxSize + 1];
	CurrentSize = 0;
}
template<class T>MaxHeap<T>&MaxHeap<T>::Insert(const T&x)
{
	if (CurrentSize == MaxSize)
	{
		cout << "no sapce!" << endl;
		return *this;
	}
	//寻找新的元素x的位置，i初始化为新的叶节点的位置，逐层向上，寻找最终的位置
	int i = ++CurrentSize;
	while ((i!=1)&&(x>heap[i/2]))
	{
		//i不是根节点，且其值大于父节点的值，需要继续调整
		heap[i] = heap[i / 2];//父节点下降
		i /= 2;//继续向上，搜索正确的位置
	}
	heap[i] = x;
	return *this;
}
template<class T>MaxHeap<T>&MaxHeap<T>::DeleteMax(T&x)
{
	//set x to max element and delete max element from heap
	//check if heap is empty
	if (CurrentSize == 0)
	{
		cout << "Empty heap!" << endl;
		return *this;
	}
	x = heap[1];//删除最大元素
	//重整堆
	T y = heap[CurrentSize - 1];//取最后一个节点，从根开始重新调整
	//find place for y starting  at root
	int i = 1,//current node of heap
		ci = 2;//child of i
	while (ci <= CurrentSize)
	{
		//使ci指向i的俩孩子较大者
		if (ci < CurrentSize&&heap[ci] < heap[ci + 1])
		{
			ci++;
		}
		//y的值大于等于孩子节点
		if (y >= heap[ci])
		{
			break;//i就是y的正确位置
		}
		//否，需要继续往下，重新整理
		heap[i] = heap[ci];//大于父节点的孩子上升
		i = ci;//向下一层，继续搜索正确位置
		ci *= 2;
	}
	heap[i] = y;
	return *this;
}
template<class T>void MaxHeap<T>::Initialize(T a[], int size, int ArraySize)
{
	//Initialize max heap to array a
	delete[]heap;
	heap = a;
	CurrentSize = size;
	MaxSize = ArraySize;
	//从最后一个内部节点开始，一直到根，对每一个字树进行重整
	for (int i = CurrentSize / 2; i >= 1; i--)
	{
		T y = heap[i];//子树的根节点元素
		//find place to put y
		int c = 2 * i;//parent of c is target
		//location  for y
		while (c <= CurrentSize)
		{
			//heap[c] should be larger sibling（兄弟）
			if (c < CurrentSize&&heap[c] < heap[c + 1])
			{
				c++;
			}
			//can we put y in heap[c/2]
			if (y >= heap[c])
			{
				break;//yes
			}
			//no
			heap[c / 2] = heap[c];
			c *= 2;//move down a level
		}
		heap[c / 2] = y;
	}
}