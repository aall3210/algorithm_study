#include <iostream>
#include <cstdlib>
#define key(A)	A
#define NULLitem NULL
#define less(A, B)	(key(A) < key(B))
#define swap(A, B)	{Item t=A; A=B; B=t;}
#define eq(A, B)	(!less(A, B) && !(less(B, A)))


///////////////////////////////////////////////////////2014.03.05
// 二分搜索的递归版本
int RecurBinarySearch(Item st[], int h, int r, Key v)
{
	// int m = (h + r) / 2;
	// 对于比较代价高的应用，以及访问开销较大的外部方法，处理大型文件常用
	// 关键值是数值型的均匀分布。缺点是额外计算量。
	int m = h + (v - kay(h))*((r - h) / (key(r) - key(h)));

	if(eq(key(st[m]), v))	
		return m;
	if(h == r)
		return NULLitem;
	if(less(v, key(st[m])))
		return BinarySearch(st, h, m-1, v);
	else
		return BinarySearch(st, m+1, r, v);
}

// 非递归版本
int NonRecurBinarySearch(Item st[], int h, int r, Key v)
{
	while(h <= r)
	{
		int m = (h + r) / 2;	// 同理的差值搜索。
		if(eq(key(st[m]), v))	
			return m;
		if(less(v, key(st[m])))
			r = m - 1;
		else
			h = m + 1;
	}
	return NULLitem;
}


////////////////////////////////////////////////////////



