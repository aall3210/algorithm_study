#include <iostream>
#include <cstdlib>


// 前缀表达式求值，递归求解
char *a;
int i = 0;
int Eval()
{
	int x = 0;
	while(a[i] == ' ')	i++;
	if(a[i] == '+')
	{
		return Eval() + Eval();
	}
	if(a[i] == '*')
	{
		return Eval() * Eval();
 	}
 	while((a[i] >= '0') && (a[i] <= '9'))
 	{
 		x = 10 * x + (a[i] - '0');
 		i++;
 	}
 	return x;
}