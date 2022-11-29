#include "atoi_itoa.h"


int main()
{

/* declerations for itoa */
char buffer_itoa[10] = {0};
int num_itoa = 25;


/* declerations for atoi */
char buffer_atoi[29] = "6234";
int res_atoi = 0;


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
Itoa10(num_itoa, buffer_itoa, 36);
PRINT_TESTS(strcmp("p", buffer_itoa));
printf("%s\n",buffer_itoa);


/* tests for atoi */
res_atoi = Atoi10(buffer_atoi);
printf("%d\n", res_atoi);
PRINT_TESTS(1234 != res_atoi);




	return 0;

}
