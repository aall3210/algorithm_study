// 感觉已经没得改进了...

// 层序遍历，只有非递归形式
// Queue[]是辅助存储的结构体，类似BFS广度优先搜索
// front,rear队列头尾指针，num是计数器
void LevelOrder(TreeNode *root)
{
	if(NULL == root)
	{
		std::cout << "The Tree is emoty!" << std::endl;
		return ;
	}
	front = rear = 0;
	TreeNode *ptr = root;
	Queue[rear++] = root;
	num = 1;
	while(num != 0)
	{
		ptr = Queue[front];
		if(ptr->leftchild != NULL)
		{
			Queue[rear++] = ptr->leftchild;
			num++;
		}
		if(ptr->rightchild != NULL)
		{
			Queue[rear++] = ptr->rightchild;
			num++;
		}
		std::cout << ptr->data << " ";
		front--;
		num--;
	}
}