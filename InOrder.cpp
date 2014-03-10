// 有待改进非递归形式，能否不使用栈?

// 中序递归遍历
void RecurseInOrder(TreeNode *root)
{
	if(root)
    {
        InOrder(root->leftchild);
        std::cout << root->data << " ";
        InOrder(root->rightchild);
    }
}

// 中序遍历非递归形式
// stack[]是辅助存储结构,num为栈的计数器
vod NonRecurseInOrder(TreeNode *root)
{
	if(NULL == root)
	{
		std::cout << "The tree id empty!" << std::endl;
		return ;
	}
	TreeNode *ptr = root;
	num = -1;
	while(ptr || (num != -1))
	{
		while(ptr != NULL)
		{
			satck[++num] = ptr;
			ptr = ptr->leftchld;
		}
		if(num != -1)
		{
			ptr = stack[num--];
			// 仅在输出的位置上与前序遍历不同
			std::cout << ptr->data << " ";
			ptr = ptr->rightchild;
		}
	}
}

// 非递归中序遍历，且不适用栈
// 结点结构体添加访问标记visit，父母结点parent
void NonRecurseInOrderWithoutStack(TreeNode *root)
{
	if(NULL == root)
	{
		std::cout << "The tree is empty!" << std::endl;
		return ;
	}
	TreeNode *ptr = root;
	while(ptr)
	{
		while(ptr->leftchild)
		{
			ptr = ptr->leftchild;
		}
		if(!ptr->visit)
		{
			std::cout << ptr->data << " ";
			ptr->visit = true;
		}
		if(ptr->rightchild && !ptr->rightchild->visit)
		{
			ptr = ptr->rightchild;
		}
		else
		{
			ptr = ptr->parent;
		}
	}
}