#include "atoi_itoa.h"


int main()
{

/* declerations for itoa */
char buffer_itoa[10] = {0};
int num_itoa = 25;
int sanity = 2056;


/* declerations for atoi */
char buffer_atoi[5] = "6234";
int res_atoi = 0;
int res_atoi1 = 0;
char max_int[11] = "2147483647";



/*declerations for appears two */
	char str1[5] = {'a', 'b', 'c', 'd', 'e'};
	char str2[7] = {'e', 'b', 'c', 'd', 'e', 'f', 'e'};
	char str3[4] = {'b', 'x', 'a', 'a'};
	
	char str4[16] = "hello world 90%";
	char str5[16] = "world hello 99%";
	char str6[18] = "hello warning 71#";	

/* tests for itoa */

Itoa10(num_itoa, buffer_itoa, 2);
PRINT_TESTS(strcmp("11001", buffer_itoa));
Itoa10(num_itoa, buffer_itoa, 3);
PRINT_TESTS(strcmp("221", buffer_itoa));
Itoa10(num_itoa, buffer_itoa, 4);
PRINT_TESTS(strcmp("121", buffer_itoa));
Itoa10(num_itoa, buffer_itoa, 5);
PRINT_TESTS(strcmp("100", buffer_itoa));
Itoa10(num_itoa, buffer_itoa, 9);
PRINT_TESTS(strcmp("27", buffer_itoa));
Itoa10(num_itoa, buffer_itoa, 10);
PRINT_TESTS(strcmp("25", buffer_itoa));
Itoa10(num_itoa, buffer_itoa, 16);
PRINT_TESTS(strcmp("19", buffer_itoa));
Itoa10(num_itoa, buffer_itoa, 20);
PRINT_TESTS(strcmp("15", buffer_itoa));
Itoa10(num_itoa, buffer_itoa, 24);
PRINT_TESTS(strcmp("11", buffer_itoa));
Itoa10(num_itoa, buffer_itoa, 25);
PRINT_TESTS(strcmp("10", buffer_itoa));
Itoa10(num_itoa, buffer_itoa, 26);
PRINT_TESTS(strcmp("P", buffer_itoa));
Itoa10(num_itoa, buffer_itoa, 33);
PRINT_TESTS(strcmp("P", buffer_itoa));
Itoa10(num_itoa, buffer_itoa, 34);
PRINT_TESTS(strcmp("P", buffer_itoa));
Itoa10(num_itoa, buffer_itoa, 35);
PRINT_TESTS(strcmp("P", buffer_itoa));
Itoa10(num_itoa, buffer_itoa, 36);
PRINT_TESTS(strcmp("P", buffer_itoa));
Itoa10(34, buffer_itoa, 25);
PRINT_TESTS(strcmp("19", buffer_itoa));
Itoa10(sanity, buffer_itoa, 33);
PRINT_TESTS(strcmp("1TA", buffer_itoa));


/* tests for atoi */
res_atoi = Atoi10(buffer_atoi, 10);
PRINT_TESTS(6234 != res_atoi);
res_atoi = Atoi10(max_int, 10);
PRINT_TESTS(INT_MAX != res_atoi);
res_atoi = Atoi10("1G", 35);
PRINT_TESTS(51 != res_atoi);


/* original func: atoi */
res_atoi1 = atoi(buffer_atoi);
PRINT_TESTS(6234 != res_atoi1);
res_atoi1 = atoi(max_int);
PRINT_TESTS(INT_MAX != res_atoi1);


/* test for endian func (originally should return 1, but the header computed to 0: */
PRINT_TESTS(Endian() != 1);


	/*tests for appears two */
	AppearsTwo(str1, str2, str3, 5, 7, 3);
	AppearsTwo(str4, str5, str6, 16, 16, 18);

IS_BIG_ENDIAN;


	return 0;

}
