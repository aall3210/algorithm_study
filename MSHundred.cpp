#include <iostream>
#include <cstdlib>


// Q1
struct BSTreeNode
{
	int m_nValue;
	BSTreeNode *m_pLeft;
	BSTreeNode *m_pRight;
};
// 我自己的思路，recursion，紧凑简洁。返回尾指针，有待确认...
const BSTreeNode * InOrderChange(const BSTreeNode *head)
{
	if(!head || (!head->m_pLeft && !head->m_pRight)	)
		;
	else
	{
		BSTreeNode *pL = InOrder(head->m_pLeft);
		if(pL)
		{
			pL->m_pRight = head;
			head->m_pLeft = pL;
		}
		BSTreeNode *pR = InOrder(head->m_pRight);
		if(pR)
		{
			pR->m_pLeft = head;
			head->m_pRight = pR;
			return pR;
		}
	}
	return head;
}
// 典型的Recursion，深入理解!!!!
BSTreeNode* BSToDouLink(BSTreeNode *root)
{
	/*
	if(!head || (!head->m_pLeft && !head->m_pRight)	)
		return ;
	BSTreeNode *pL = head->m_pLeft;
	BSTreeNode *pR = head->m_pRight;

	while(pL->m_pRight)
	{
		pL = pL->m_pRight;
	}
	while(pR->m_pLeft)
	{
		pR = pR->m_pLeft;
	}
	head->m_pLeft = pL;
	head->m_pRight = pR;
	pL->m_pRight = head;
	pR->m_pLeft = head;

	BSToDouLink(head->m_pLeft);
	BSToDouLink(head->m_pRight);
	*/ //不能这样，BStree的指向关系全乱了...

	BSTreeNode *head, tail;
	Helper(head, tail, root);
	return head;
}
// 圈定链表首尾指针
void Helper(BSTreeNode *& head, BSTreeNode *&tail, BSTreeNode *& root)
{
	BSTreeNode * ltail, rhead;
	if(root == NULL)
	{
		head = tail = NULL;
	}
	Helper(head, ltail, root->m_pLeft);
	Helper(rhead, tail, root->m_pRight);
	if(ltail != NULL)
	{
		ltail->m_pRight = root;
		root->m_pLeft = ltail;
	}
	else
	{
		head = root;
	}
	if(rhead != NULL)
	{
		rhead->m_pLeft = root;
		root->m_pRight = rhead;
	}
	else
	{
		tail = root;
	}
}


// Q2，栈可以存储之前的记忆的。
struct StackElement
{
	int data;
	int min;
};
typedef struct Stack
{
	StackElement * s;
	int m_top;
	int m_maxsize;
}MinStack;

MinStack MinStackInit(int maxSize)
{
	MinStack stk;
	StackElement * p = (StackElement *)malloc(sizeof(StackElement) * maxsize);
	stk.s = p;
	stk.m_top = 0;
	stk.m_maxsize = maxsize;
	return stk;
}

void MinStackFree()
{
	free(stk.s);
}

void MinStackPush(int v)
{
	if(stk.top == maxsize)
		error("The stack is full!");
	stk.s[top].data = v;
	if(stk.top == 0)
		stk.s[stk.top].min = v;		// 注意不要漏了stk.top，不能直接top
	else
		stk.s[stk.top].min = (v < stk.s[top-1].min)	v : stk.s[stk.top-1].min;
	stk.top++;
}

int MinStackPop()
{
	if(stk.m_cnt == 0)
		error("The stack is empty!");
	return (stk.s[--stk.top].data);
}

int MinStackMin()
{
	if(stk.top == 0)
		error("The stack is empty, no min!");
	return (stk.s[stk.top-1].min);
}


// Q3
// traditional greedy algorithm.
typedef SubArray
{
	int max;
	int head;
	int rail;
};
// 线性时间的最大子数组算法
SubArray * MaxSubArray(int a[], int n)
{
	if(0 == n)
		error("Empty array");
	SubArray * p = new SubArray;
	p->max = -(1<<31);
	p->head = p->rail = -1;
	int h = 0, r = -1;
	int sum = 0;
	for(int cnt=0; cnt<n; cnt++)
	{
		sum += a[cnt];
		if(sum > p->max)
		{
			p->max = sum;
			p->rail = r;
			p->head = h;
		}
		if(sum < 0)
		{
			sum = 0;
			h = cnt + 1;
			r = cnt;
		}
		else
		{
			r++;
		}
	}
	return p;
}


// Q4
// 遍历二元树的所有路径
struct BSTreeNode
{
	int m_nValue;
	BSTreeNode *m_pLeft;
	BSTreeNode *m_pRight;
};

void BinaryTreeTrade(BSTreeNode * root, int n)
{
	// 栈的top,empty判定，还需要一个栈存储
	if(NULL == root)
		error("The tree is empty!");
	StackPush(root);
	BSTreeNode * p = StackPop();
	int sum = 0;
	while(p)
	{

	}
}
