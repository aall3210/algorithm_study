// 理解动态规划的思想(Dynamic Programming)
// 经典的DP问题，具有最有子结构和重叠子结构



///////////////////////////////////////////////////////////////////////////////////////
// 一连串矩阵相乘的括号匹配，使得所做运算量最小
// 打表存储子结构，自底向上构建CreatTable()（当初的美素数就是这样...原来这就是DP...）


// 矩阵A1..An相乘 ，Ai的维数Pi-1*Pi存储在P[0..n]中
// 数组m[1..n][1..n]中存放最小乘法次数，上三角矩阵；数组s[1..n-1][2..n]切割点k的值
// 暴力搜索的时间是指数级，很糟糕；DP只需要n的三次方级的时间和n平方级的空间。
void MatrixChainOrder(int *p， int n, int *m[], int *s[])
{
	for(int i=1; i<=n; i++)
	{
		m[i][i] = 0;
	}
	for(int l=2; l<=n; l++)
	{
		for(int i=1; i<=n-l+1; i++)
		{
			int j = i + l - 1;
			m[i][j] = 100000000;	// 给无穷大
			s[i][j] = -1;			// 给负数即可
			for(int k=i; k<j; k++)
			{
				int sum = m[i][k] + m[k+1][j] + p[i-1]*p[k]*p[j];
				if(m[i][j] > sum)
				{
					m[i][j] = sum;
					s[i][j] = k;
				}
			}
		}
	}
}


// 输出矩阵链的最佳匹配括号，最终打印出的括号对共有(n-1)对
void MatrixOptimalParens(int *s, int i, int j)
{
	if(i == j)
	{
		std::cout << "A" << i;
	}
	else
	{
		std::cout << "(";
		MatrixOptimalParens(s, i, s[i][j]);
		MatrixOptimalParens(s, s[i][j]+1, j);
		std::cout << ")";
	}
}


	
///////////////////////////////////////////////////////////////////////////////////////
// 切割钢条问题，考虑到对称的子问题，可采用自顶向下的递推，指数级的时间
// 带备忘(memo)的自顶向下会更好，但递归调用开销大
// 自底向上的DP处理(CreatTable)，空间换时间
// 打印出切割方案，n是钢条长度，s[n+1]存储切割点，p[n+1]最大切割价值，r[n+1]存储整条钢条的价值
ExtendBottomUpCutRod(int n, int *r, int *s, int *p)
{
	p[0] = 0;
	for(int i=1; i<=n; i++)
	{
		int temp = -100;
		s[i] = -1;
		for(int j=1; j<=i; j++)
		{
			int temp2 = r[i] + p[n-i]
			if(temp < temp2)
			{
				temp = temp2;
				s[i] = j;
			}
		}
		p[i] = temp;
	}
}

PrintCutRodSolution(int n, int *r)
{
	int *s = new int [n+1];
	int *p = new int [n+1];

	ExtendBottomUpCutRod(n, r, s, p);
	while(n)
	{
		std::cout << s[n] << " ";
		n -= s[n];
	}

	delete [] s;
	delete [] p;
}
///////////////////////////////////////////////////////////////////////////////////////