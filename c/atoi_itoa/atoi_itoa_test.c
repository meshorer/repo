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
printf("%d\n", res_atoi);

/* original func: */
res_atoi1 = atoi(buffer_atoi);
PRINT_TESTS(6234 != res_atoi1);
res_atoi1 = atoi(max_int);
PRINT_TESTS(INT_MAX != res_atoi1);


	return 0;

}
