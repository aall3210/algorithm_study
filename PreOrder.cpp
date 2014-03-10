// 有待改进哦~ 对条件理解要更深刻！！

// 前序遍历递归形式
void PreOrder(TreeNode *root)
{
	if(NULL != root)
	{
		std::cout << root.data << " ";
		PreOrder(root->leftchild);
		PreOrder(root->rightchild);	
	}
}

// 前序遍历非递归形式
// stack[]作为辅助存储数据结构,num为栈计数器
void PreOrder(TreeNode *root)
{
	if(NULL == root)
	{
		std::cout << "Something is wrong!" << std::endl;
		return ;
	}
	TreeNode *ptr = root;
	num = -1;
	while((ptr != NULL) || (num != -1))
	{
		while(ptr != NULL)
		{
			std::cout << ptr->data << " ";
			stack[++num] = ptr;
			ptr = ptr->leftchild;
		}
		if(num != -1)
		{
			ptr = stack[num--];
			ptr = ptr->rightchld;
		}
	}
}

