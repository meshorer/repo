#include<string.h>
#include<stdio.h>

int IsRotation(char* s1, char* s2)
{
	int i = 0;
	int j = 0;
	int flag = 0;
	int iterate_count = 0;
	int s1_len = strlen(s1);
	int s2_len = strlen(s2);
	if (s1_len != s2_len)
	{
		return 1;
	}
	while (i < s1_len && iterate_count < (s1_len*2)-1)
	{
		j = 0;

		while (j < s1_len && i < s1_len)
		{
			if (s1[i] == s2[j])
			{
				flag++;
				i++;
			}
			else if (s1[i] == s2[0] && j == s1_len-1)
			{
				continue;
			}
			else
			{
				flag = 0;
				i = 0;
			}
			j++;
			iterate_count ++;
		}
	}
	if (flag == s1_len)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}




int main()
{
	char str1[6] = "12345";
	char str2[6] = "35512";
	printf("\n");
	printf(" 0 for yes | 1 for no \n");
	printf("-----------------------\n");
	printf("Is %s  rotation of %s?    %d\n", str2, str1, IsRotation(str1, str2));
	printf("Is 45123  rotation of 12345?\t%d\n",IsRotation("12345","45123"));
	printf("Is 123412 rotation of 121234?\t%d\n",IsRotation("121234","123412")); 
	printf("Is 123413 rotation of 121234?\t%d\n",IsRotation("121234","123413")); 
	return 0;
}



