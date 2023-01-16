#include <stdio.h>

int octal_to_decimal(int octal) 
{
	int decimal = 0;
    	int base = 1;
    	while (octal != 0)
    	{
        	decimal += (octal % 10) * base;
        	octal /= 10;
        	base *= 8;
    	}
    	return decimal;
}



int decimal_to_binary(int decimal)
{
    	int binary = 0;
    	int i = 1;
    	while (decimal != 0) {
        binary += (decimal % 2) * i;
        i *= 10;
        decimal /= 2;
    }
    
    	return binary;	

}





int main()
{

	/*        
		1. save the i-mode in a different value.
		2. count the letters in the string
		3. the first 4 digits (nibel) - file type: extract it; 
		4. the next 3 bits are the special: if the strlen on string is 3 - zero them and continue. else - treat them
		5. the string numbers are octal - convert to decimal, and from decimal to biary
		6. use the conerted binary - add to it the extracted value of the file type. assign this number to the i-mode
		
		regular file - 0x8000. in binary - 1000000000000000, in octal - 100000
		regular file type + 0456 in binary - 1000000100101110, in octal - 100456
		only 0456 - 100101110
		
	*/

	char *str = "456"; 
	int octal = 456;
	int decimal = 0;
	int binary = 0;
	decimal = octal_to_decimal(octal);
	printf("decimal is: %d\n",decimal);
	binary = decimal_to_binary(decimal);
	printf("binary is: %d\n",binary);
		
	str+=1;
	printf("tav is :%s\n",(str));
	str+=1;



	return 0;
}


