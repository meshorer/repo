
/*Check for balanced parentheses in an expression.
Write a function to examine whether the pairs of parentheses { , } , ( , ) , [ , ] are correct in a given string.

    Example:

    Input: string = “[()](){[()]()}”
    Output: Balanced  

    Input: string = “[{}(])”  
    Output: Not Balanced  */

#include<stdio.h>

int CheckClose(char *str,int parent)
{
	int normal_open = 0;
	int curley_open = 0;
	int square_open = 0;
	int sum = 0;
	char *ptr = str;
	ptr++;
	while (*ptr != parent)
	{
		if (*ptr == '(')
			{
				normal_open+=1;
			}
		if (*ptr == '{')
			{
				curley_open+=1;
			}
		if (*ptr == '[')
			{
				square_open+=1;
			}
			
		if (*ptr == ')')
			{
				normal_open-=1;
			}
		if (*ptr == '}')
			{
				curley_open-=1;
			}
		if (*ptr == ']')
			{
				square_open-=1;
			}	

		ptr++;	
	}
	sum = normal_open + curley_open + square_open;
	if (*ptr == parent && sum == 0)
	{
		return 0;
	}
	return 1;

}

void CheckParenthesis(char *str)
{
	int normal_open = 0;
	int curley_open = 0;
	int square_open = 0;
	int parent = 0;
	int flag = 0;
	
	while(*str)
	{
		if (normal_open + curley_open + square_open != 0)
		{
			printf("not balanced\n");
			return;
		}
		
		switch (*str)
		{
		
		case '(':
			parent = ')';
			break;
			
		case '{':
			parent = '}';
			break;
			
		case '[':
			parent = ']';	
			break;
		
		}
		str++;
		while (*str != parent)
		{
		
			if (*str == '(')
			{
				normal_open+=1;
				if (1 == CheckClose(str,')'))
				{
					flag = 1;
					break;
				} 
			}
				
			if (*str == '{')
			{
				curley_open+=1;
				if (1 == CheckClose(str,'}'))
				{
					flag = 1;
					break;
				}
			}

			if (*str == '[')
			{
				square_open+=1;
				if (1 == CheckClose(str,']'))
				{
					flag = 1;
					break;
				}
			}
			
			if (*str == ')')
			{
				normal_open-=1;	
			}
			
			if (*str == '}')
			{
				curley_open-=1;	
			}
			
			if (*str == ']')
			{
				square_open-=1;	
			}
			
			str++;
				
		}
		str++;
	}
		
		if (flag + normal_open + curley_open + square_open != 0)
		{
			printf("not balanced\n");
			return;
		}
	
		else
		{
			printf( "balanced\n");
			return;
		}
}

int main()
{
	char str[] = "[()](){[()]()}";
	char str1[] = "[()](){[()]]()}";
	char str2[] = "[{}(])";
	char str3[] = "[{(})]";
	CheckParenthesis(str);
	CheckParenthesis(str1);
	CheckParenthesis(str2);
	CheckParenthesis(str3);
	return 0;
}