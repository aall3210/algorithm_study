// 对比BinaryTree.cpp 有这么麻烦的条件匹配么？？

// 后序遍历递归形式
void PostOrder(TreeNode *root)
{
	if(root != NULL)
    {
    	PostOrder(root->leftchild);
    	PostOrder(root->rightchild);
    	std::cout << root->data << " ";
    }
}

// 非递归形式的后序遍历
// satck[]辅助栈结构体,stack[].data存放二叉树结点,
// stack[].cnt表示访问结点计数，num栈计数器
void PostOrder(TreeNode *root)
{
	if(NULL == root)
	{
		std::cout << "The tree is empty!" << std::endl;
		return ;
	}
	TreeNode *ptr = root;
	num = -1;

	// 查看条件变化！！
	while((ptr != NULL) || (num != -1))
	{
		// while((ptr != NULL) && (satck[num].cnt == 0))
		while(ptr != NULL)
		{
			stack[++num].data = ptr;
			stack[num].cnt = 1;
			ptr = ptr->leftchild;
		}
		/*
		if(num != -1) 
		{
			if(stack[num].cnt == 1)
			{
				ptr = (stack[num].data)->rightchild;
				stack[num].cnt = 2;
			}
			while((stack[num].cnt == 2) && (num != -1))
			{
				std::cout << (stack[num].data)->data << " ";
				ptr = satck[num--].data;
			}
		}
		*/
		if(num != -1)
		{
			if(stack[num].cnt == 1)
			{
				ptr = (stack[num].data)->rightchild;
				stack[num].cnt = 2;
			}
			else
			{
				std::cout << (stack[num].data)->data << " ";
				ptr = NULL;
			}
		}
	}
}

// 参考思路
while(!s.empty())
    {
        cur=s.top();
        if((cur->lchild==NULL&&cur->rchild==NULL)||
           (pre!=NULL&&(pre==cur->lchild||pre==cur->rchild)))
        {
            cout<<cur->data<<" ";  //如果当前结点没有孩子结点或者孩子节点都已被访问过 
              s.pop();
            pre=cur; 
        }
        else
        {
            if(cur->rchild!=NULL)
                s.push(cur->rchild);
            if(cur->lchild!=NULL)    
                s.push(cur->lchild);
        }
    }    