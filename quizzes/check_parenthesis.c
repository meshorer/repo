#include<stdio.h>

int CheckParenthesis(char *str, int size)
{
	int normal_open = 0;

	int curley_open = 0;

	int square_open = 0;

	
	int i = 0;
	
	for (i = 0; i<size; i++)
	{
	
		if (str[i] == '(' || str[i] == '{' || str[i] == '[')
		{
			parent = str[i];
		}
		
		while (0 !=parent)
		{
			if (str[i] == '(')
			{
				normal_open+=1;
			}
		
			if (str[i] == '{')
			{
				curley_open+=1;
			}
		
			if (str[i] == '[')
			{
				square_open+=1;
			}
		
		}
		
		if (normal_open + curley_open + square_open != 0)
		{
			return "not balanced";
		}
	}


	
}
