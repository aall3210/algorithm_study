// 插入、选择、冒泡、希尔、索引指针排序
// 快排(多方面改进)、归并(更棒)、

#include <iostream>
#include <cstdlib>
#define NORMALSORT 1
///////////////////////////////////////////////////////////////////////////
// 选择排序，每次选择余下元素关键字最小的元素与当前元素交换
void SelectionSort(Item a[], int h, int r)
{
	for(int i=h; i<r; i++)
	{
		int mini = i;
		for(int j=i+1; j<=r; j++)
		{
			if(a[j] < a[mini])
				mini = j;	// 记录下标，而不是元素
		}
		if(mini != i)
			exch(a[mini], a[i]);
	}
}


///////////////////////////////////////////////////////////////////////////
// 已经采用自适应的插入排序  
// 还是用最小元素的关键字放在第一位
void InsertionSort(Item a[], int h, int r)
{
	for(int i=h+1; i<=r; i++)
	{
		Item t = a[i];
		a[h] = a[i];		// 观察哨关键字
		int j = i-1;
		while(t < a[j])		// 基于前部分已排序，自适应算法!
		{
			a[j+1] = a[j];	// 在内循环中不进行交换，减少指令数
			j--;
		}
		a[j+1] = t;
	}
}

// 最小元素的关键字放在第一位，在代码中避免使用观察哨，显示的测试更容易理解。同时减少一个存储。
void InsertionSort2(Item a[], int h, int r)
{
	int s = h;
	for(int i=h+1; i<=r; i++)	
	{
		if(a[s] > a[i])
			s = i;
	}
	exch(a[s], a[h]);
	for(int i=h+1; i<=r; i++)
	{
		Item t = a[i];
		int j = i-1;
		while(t < a[j])		
		{
			a[j+1] = a[j];	
			j--;
		}
		a[j+1] = t;
	}
}


///////////////////////////////////////////////////////////////////////////
// 改进的冒泡排序
void BubbleSort(Item a[], int h, int r)
{
	/*
	for(int i=h; i<r; i++)
	{
		bool nonexchange = true;	
		for(int j=r; j>i; j--)
		{
			if(a[j-1] > a[j])
			{
				exch(a[j-1], a[j]);
				if(nonexchange)
					nonexchange = false;
			}
		}
		if(nonexchange)
			break;
	}	*/
	// 代码更简洁！！
	bool exchange = true;
	while(exchange)			// 自适应改进，后部分已排好跳出外循环
	{
		exchange = false;
		for(int i=r; i>h; i--)
		{
			if(a[i-1] > a[i])
			{
				exch(a[i-1], a[i]);
				exchange = true;
			}
			// h++;
		}
		h++;
	}
}

// 自己再次改进的冒泡排序(是否有必要????)
void BubbleSort2(Item a[], int h, int r)
{
	/*
	int nonexchange = r;	
	for(int i=h; i<r; i++)
	{
		int j = r;
		if(nonexchange != r)
			j = nonexchange + 1;	// 记录上回首次改变的位置,下次循环从这个位置之后的位置开始
		nonexchange = i;
		while(j > i)
		{
			if(a[j-1] > a[j])
			{
				exch(a[j-1], a[j]);
				if(nonexchange == i)
					nonexchange = j;
			}
			j--;
		}
		if(nonexchange == i)	// 上回bubble完全没有改变顺序，表明已经全部排好了
			break;
	}	*/
	// 思路不对，应该是前面部分已经有序记录位置...
	// 据说vc03的STL就是这种思路
	int exchange = h;
	int hPre = h - 1;
	while(exchange > hPre)
	{
		hPre = h;
		h = exchange;
		for(int i=r; i>h; i--)
		{
			if(a[i-1] > a[i])
			{
				exch(a[i-1], a[i]);
				exchange = i;
			}
		}
	}
}

// 双向扫描的“冒泡”，抖动排序(shaker sort)，加入自适应
void ShakerSort(Item a[], int h, int r)
{
	/*
	bool flag = 1;
	while(h < r)
	{
		bool nonexchange = true;
		if(flag)
		{
			int i = r;
			while(i > h)
			{
				if(a[i-1] > a[i])
				{
					exch(a[i-1], a[i]);
					if(nonexchange)
						nonexchange = false;
				}
				i--;
			}
			h++;
		}
		else
		{
			int i = h;
			while(i < r)
			{
				if(a[i] > a[i+1])
				{
					exch(a[i], a[i+1]);
					if(nonexchange)
						nonexchange = false;
				}
				i++;
			}
			r--;
		}
		if(nonexchange)
			break;
	}	*/

	// 双向冒泡排序也称为“鸡尾酒排序”
	// 数据表在进行排序之间已经基本有序或局部有序，那么算法的复杂度将接近O(n)
	while(h < r)
	{
		int exchange = r;
		for(int i=r; i>h; i--)
		{
			if(a[i-1] > a[i])
			{
				exch(a[i-1], a[i]);
				exchange = i;
			}
		}
		h = exchange;

		for(int i=h; i<r; i++)
		{
			if(a[i] > a[i+1])
			{
				exch(a[i], a[i+1]);
				exchange = i;
			}
		}
		r = exchange;
	}
}


//////////////////////////////////////////////// 
// 选择一个好的步长的实际效果最多可以提高25%的效率。该问题是“简单问题存在内在复杂性”的好例子。
// 步长为3的希尔排序, [1, 4, 13, 40, 121, 364 ...]。
// 最简单步长之一[1, 8, 23, 77, 281, 1073, 4193, 16577 ...]
// 有一些不好的步长序列[1, 2, 4, 8, 16, 32 ...]，对于随即序列效果是显著的；
// 但对于最坏情况(偶数位置保存较小元素)，简直是灾难的，退化到二次时间
void ShellSort(Item a[], int h, int r)
{
	int s = (r - h) / 9;
	int hl = 1;
	while(hl <= s)	// 插入排序的长度控制在10左右!
	{
		hl = 3 * hl + 1;
	}
	while(hl > 0)
	{
		for(int i=h+hl; i<=r; i++)
		{
			Item temp = a[i];
			int j = i - hl;
			while(j >= h && less(temp, a[j]))
			{
				a[j + hl] = a[j];
				j -= hl;
			}
			a[j + hl] = temp;
		}
		hl /= 3;
	}
}


//////////////////////////////////////////////// 
// 当记录占用空间较大不适合移动时，数组表示可采用索引记录数组下标
// data[n]表示原存储空间，a[n]表示记录的结构体指针数组
#define POINTERSORT 2

// 更为通用的方法是采用指针记录，以及在原数组的基础上进行原位排序
void OriginalSort(Item data[], Item a[], int n)
{
	for(int i=0; i<n; i++)
	{
		if(a[i] == i)
		{
			continue;
		}
		else
		{
			record temp = data[i];	// temp is struct record
		}
		int k = i;
		while(a[k] != i)	// k、j记录的是data[]以及a[]的下标
		{
			int j = k;
			data[k] = data[a[k]];	// 注意多理解!!
			k = a[j];
			a[j] = j;
		}
		data[k] = temp;
		a[k] = k;
	}
}


//////////////////////////////////////////////// 
// 递归快排.  我们会意识到汇编语言或机器语言对内部循环的编码可以更节省时间！！！！
// 划分基于(1、2、4)的改进是极其有必要的!!
int Partition(Item a[], int h, int r)
{
	int i = h-1;
	int j = r;
	int temp = a[r];

	/* (4)
	int k = h;
	int m = r-1;
	*/

	for(; ;)
	{
		// (1)与划分元素相等的元素，两头指针都停止的策略是最好的，对于多个重复元素的文件可以平衡划分。
		while(a[++i] < temp) ;	
		while((a[--j] > temp) && (j > i)) ;
		if(i >= j)
			break;
		exch(a[i], a[j]);

		/* (4)采用三路划分，处理大量出现的等元素，没有等元素的同常规情况。
		// 当有许多重复关键字的元素出现在文件中，前边的算法性能将大打折扣。
		if(a[i] == temp)
		{
			exch(a[i], a[k]);
			k++;
		}
		if(a[j] == temp)
		{
			exch(a[j], a[m]);
			m--;
		}
		*/
	}
	exch(a[i], a[r]);

	/* (4)
	j = i+1;
	i--;
	for(int cnt = h; cnt < k; cnt++)
	{
		exch(a[cnt], a[i]);
		i--;
	}
	for(int cnt = r-1; cnt > m; cnt--)
	{
		exch(a[cnt], a[j]);
		j++;
	}
	*/  
	// 基于三路划分策略的返回是(r, i)&&(j, r)，中间(i+1, j-1)部分是与划分元素相等的元素
	// 采用三路划分策略必须将Patition()和RecursiveQSort()合并.
	return i;
}

// 但是现代机器的硬件使得递归在栈上的时间消耗不予考虑...
// 仅在特殊情况下需要考虑栈空间的过快增长 (3)
void RecurQSort(Item a[], int h, int r)
{
	// (2)递归最花费时间的地方就是：末梢的小文件，采用InsertionSort()来对整个基本有序的序列重新排序
	// 选择小的子文件的最优阈值可以导致平均运行时间约10%的改进。精确地选择该值不是关键!!	
	// 等效于分别对每个不长于10的小文件插入(长度选取5~20都可)
	if(r-h < 10)	
		return ;	

	// (3)划分元素的优化，可采用概率策略，利用概率的随机性来取得较大可能的性能。但在实际应用中不会用随机数生成器来产生数据使用。
	// 亦可采用：三者取中策略，使得总的时间大约减少5%
	// 有必要先进行交换，对于退化文件有较好的预防，保证不会出现异常情况。
	exch(a[(h+r)/2], a[r-1]);	
	compexch(a[h], a[r-1]);
	compexch(a[h], a[r]);
	compexch(a[r-1], a[r]);

	int i = Partition(a, h+1, r-1);

	// int i = Partition(a, h, r);
	QuickSort(a, h, i-1);
	QuickSort(a, i+1, r);
}


// 非递归快排，递归的消除通常基于栈的辅助!!

// (0)先压入大文件来确保栈的最大深度为logN，该策略可以保证栈中每个元素不会超过它下面元素大小的一半。
// 该策略最大栈空间的使用是在划分总是落在文件中间时出现。联想“内部栈的动态过程”。
// 对于随机文件，实际栈大小要小得多；对于退化文件就更小了。
#define Push2(A, B)  PushStack(A); PushStack(B);

void NonRecurQSort(Item a[], int h, int r)
{
	if(r <= h)
		return ;
	Push2(h, r);
	while(!Empty(s))
	{
		r = PopStack(s);
		h = PopStack(s);
		if((r - h) < 10)		// 5~20的阈值都是高效的。
			continue;
		else
		{
			int i = Partition(a, h, r);
			if((i-h) > (r-i))
			{
				Push2(h, i-1);	
				Push2(i+1, r);	
			}
			else
			{
				Push2(i+1, r);
				Push2(h, i-1);
			}	
		}
	}
}

#define	RECURSIVE 1
void QuickSort(Item a[], int h, int r)
{
	#ifdef RECURSIVE
		RecurQSort(a, h, r);
	#else
		NonRecurQSort(a, h, r);
	#endif

	InsertionSort2(a, h, r);
}


// QSort()的应用 -- 选择数组a[]中第k大的元素
Item Selete(Item a[], int h, int r, int k)
{
	int i = -1, j = -1;
	while(k != j)
	{
		i = Partition(a, h, r);
		j = i - h + 1;
		if(j < k)
		{
			h = i + 1;
		}
		else
		{
			r = i - 1;
		}
	}
	return a[i];
}


///////////////////////////////////////////////////  2014.02.20总结MergeSort
// 数组自顶向下基于“分治”的归并排序
// 在不添加观察哨基础上，(1)用bitonic消除内循环的比较操作，aux[]为辅助数组
// 为何会变成不稳定排序????
void MergeBitonic(Item a[], int h, int m, int r)
{
	int i=m, j=m, k=h;
	Item aux[];
	while(i >= h)	{aux[i] = a[i]; i--;}
	while(j <= r)	{aux[r+m-j] = a[j+1]; j++;}
	while(k <= r)
	{
		a[k++] = less(aux[i], aux[j]) ? aux[i++] : aux[j--];
	}
}

void MergeSort(Item a[], int h, int r)
{
	int m = (h + r)/2;
	if((r - h) < 10)	// (0)小文件的处理策略，只能先处理小文件，归并需有序
	{
		InsertionSort(a, h, r);
		return ;
	}
	MergeSort(a, h, m);
	MergeSort(a, m+1, r);
	MergeBitonic(a, h, m, r);
}


// 缺点是循环内部比较操作过多，复制数组消耗的时间
void MergeAB(Item c[], Item a[], int M, Item b[], int N)
{
	for(int i=0, j=0, k=0; k<M+N; k++)
	{
		if(i == M)	{c[k] = b[j++]; continue;}
		if(j == N)	{c[k] = a[i++]; continue;}
		c[k] = less(a[i], b[j]) ? a[i++] : b[j++];
	}
}

// (2)采用类似 pinpang buffer 的策略，减少数组的复制
// 辅助数组aux[]和a[]交替处理和存储数据，整个过程值复制一次数组!!
void MergeSortPinpang(Item a[], Item b[], int h, int r)
{
	int m = (h+r)/2;
	if((r - h) < 10)	
	{
		InsertionSort(a, h, r);
		return ;
	}
	MergeSortPinpang(b, a, h, m);
	MergeSortPinpang(b, a, m+1, r);
	MergeAB(a+l, b+h, m-h+1, b+m+1, r-m);
}

void MergeSort2(Item a[], int h, int r)
{
	for(int i=h; i<=r; i++)
	{
		aux[i] = a[i];
	}
	MergeSortPinpang(a, aux, h, r);
}


// 组合-求解的自底向上非递归的归并
#define min(A, B)  (less(A,B) ? A : B)
void MergeSort3(Item a[], int h, int r)
{
	for(int i=1; i<r-h ; i=i+i)
	{
		for(int j=h; j<=r-i; j+=i+i)
		{
			MergeBitonic(a, j, j+i-1, min(j+i+i-1, r));		//注意这里的界限！
		}
	}
}


// 关于链表link的归并排序
link Merge(link a, link b)
{
	struct node head;
	link c = &head;
	while((a!=NULL) && (b!=NULL))
	{
		if(less(a->Item, b->Item))
		{
			c->next = a;
			c = a;
			a = a->next;
		}
		else
		{
			c->neat = b;
			c = b;
			b = b->next;
		}
	}
	c->next = (a == NULL) ? b : a;
	return head.next;
}

// 自顶向下的链表归并
link MergeSortLink(link c)
{
	link a = c, b = c->next;
	if((c == NULL) || (c->next == NULL))
		return ;
	while((b!=NULL) && (b->next!=NULL))		// 链表找中点算法！！
	{
		a = a->next;
		b = b->next->next;
	}
	b = c->next;
	c->next = NULL;
	return Merge(MergeSortLink(b), MergeSortLink(a));
}

// 自底向上涉及到队列操作，待写... 栈也可以吧，类似快排


///////////////////////////////////////////////////  2014.03.02总结Heapsort()
// 删除元素或者更改优先级需要堆化a[n]数组...
inline void exch(a, b)	{Item t=a; a=b; b=t;} 
inline bool less(a, b)	{if(a<b) return true; else return false;}
void HeapifyUp(Item a[], int m)
{
 	int h = m / 2;
 	while(less(a[h], a[m]) && h)
 	{
 		exch(a[m], a[h]);
 		m = h;
 		h /= 2;
 	}
}
void HeapifyDown(Item a[], int n, int m)
{
	int s = 2 * m;
	while(s <= n)
	{
		if(less(s, n) && less(a[s], a[s+1]))
		{
			s++;
		}
		if(!less(a[m], a[s]))	break;
		exch(a[m], a[s]);
		m = s;
		s *= 2;
	}
}

void HeapSort(Item a[], int n)
{
	for(int i=n/2; i>0; i++)
	{
		HeapifyDown(a, n, i);	// 自底向上造堆所需时间为N
	}
	for(int i=n; i>0; i--)
	{
		exch(a[1], a[i]);
		HeapifyDown(a, n, 1);	// 时间复杂度为 NlogN
	}
}



int main()
{
	using namespace std;
	int N, flag;
	cin >> N >> flag;
	Item *a = new Iten [N];

	if(flag)
	{
		for(int i=0; i<N; i++)
			a[i] = 1000 * (1.0 * rand() / RAND_MAX);
	}
	else
	{
		for(int i=0; i<N; i++)
			cin >> a[i];
	}

	Sort(a, 0, N-1);

	for(int i=0; i<N; i++)
		cout << a[i] << " ";
	cout << endl;

	delete a [];
	return 0;
}

