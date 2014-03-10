// 二叉搜索树的常用操作

typedef int Type;

struct TreeNode
{
	Type data;
	TreeNode *leftchild;
	TreeNode *rightchild;
	TreeNode *parent;
	unsigned visit;
};


// 递归查询
TreeNode* RecurBSTree(TreeNode *root, Type k)
{
	if(k == root->data && root != NULL)
	{
		return root;
	}
	else if(k > root->data)
	{
		return RecurBSTree(root->rightchild, k);
	}
	else
	{
		return RecurBSTree(root->leftchild, k);
	}
}

// 非递归查询
TreeNode* NonRecurBSTree(TreeNode *root, Type k)
{
    if(NULL == root)
    {
    	std::cout << "This tree is empty!" << std::endl;
    	return ;
    }
    while(root)
    {
    	if(k == root->data)
		{
			break;
		}
		else if(k > root->data)
		{
			root = root->rightchild;
		}
		else
		{
			root = root->leftchild;
		}
    }
    return root;
}

// 二叉树最大关键元素
TreeNode* BSTreeMax(TreeNode *root)
{
	if(NULL == root)
    {
    	std::cout << "This tree is empty!" << std::endl;
    	return ;
    }
    while(root->rightchild)
    {
    	root = root->rightchild;
    }
    return root;
}

// 二叉树最小关键元素
TreeNode* BSTreeMin(TreeNode *root)
{
	if(NULL == root)
    {
    	std::cout << "This tree is empty!" << std::endl;
    	return ;
    }
    while(root->leftchild)
    {
    	root = root->leftchild;
    }
    return root;
}

// 二叉搜索树的前驱查找
TreeNode* BSTreePreNode(TreeNode *n)
{
	if(n->leftchild ！= NULL)
	{
		return BSTreeMax(n->leftchild);
	}
	TreeNode *p = n->parent;
	while((p != NULL) && (n == p->leftchild))
	{
		n = p;
		p = p->parent;
	}
	return p;
}

// 二叉搜索树的后继查找
TreeNode* BSTreePostNode(TreeNode *n)
{
	if(n->rightchild)
	{
		return BSTreeMin(n->rightchild);
	}
	TreeNode *p = n->parent;
	while((p != NULL) && (n == p->rightchild))
	{
		n = p;
		p = p->parent;
	}
	return p;
}


// 二叉搜索树的插入操作,其实类似查找操作
void BSTInsertion(TreeNode *root, int key )
{
	TreeNode *n = new TreeNode;
	n->data = key;
	n->leftchild = n->rightchild = n->parent = NULL;

	// 和查找一样先找到位置
	TreeNode *s = root;
	TreeNode *p = NULL;
	while(s)
	{
		p = s;
		if(key <= s->data)
		{
			s = s->leftchild;
		}
		else
		{
			s = s->rightchild;
		}
	}

	if(NULL == p)	// 根节点为空
	{
		root = n;
	}
	else if(key <= p->data)
	{
		p->leftchild = n;
	}
	else
	{
		p->rightchild = n;
	}
	n->parent = p;
}


// 二叉搜索树的删除操作，略有点麻烦... 
// 先构造一个结点替换函数,s替换掉n结点,s为n的子树结点
void BSTransplant(TreeNode *root, TreeNode *n, TreeNode *s)
{
	if(NULL == n->parent)
	{
		root = s;
	}
	else if(n == n->parent->leftchild)
	{
		n->parent->leftchild = s;
	}
	else
	{
		n->parent->rightchild = s;
	}
	if(s)	// 确保s是NULL时不连接其双亲，对应下边结点无孩子情况
	{
		s->parent = n->parent;
	}
}

// 替换函数会确保双亲孩子关系连接顺利
void BSTDelete(TreeNode *root, TreeNode *n)
{
	// 结点的右子树为空，包含无子树和只有左子树
	if（NULL == n->rightchild）
	{
		BSTransplant(root, n, n->leftchild);
	}
	else if(NULL == n->leftchild)
	{
		BSTransplant(root, n, n->rightchild);
	}
	else
	{
		// 好好理解!!!
		TreeNode *a = BSTMin(n->rightchild);
		if(a != n->rightchild)
		{
			BSTransplant(root, a, a->rightchild);
			a->rightchild = n->rightchild;
			n->rightchild->parent = a;
		}
		BSTransplant(root, n, a);
		a->leftchild = n->leftchild;
		n->leftchild->parent = a;
	}
}