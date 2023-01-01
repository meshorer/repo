
void Fix_Bugs();
int count_error = 0;



#define PRINT_TESTS(num) \
 if (0 == (num)) { \
            printf("\r"); \
        } else { \
            printf("\033[0;31mFAIL in file %s at line %d \033[0m\n",__FILE__, __LINE__); \
            count_error += 1;}
            
            
#define CHECK_ERROR(count_error) \
		if (count_error > 0){ \
		Fix_Bugs();}
		
	
	
	
void Fix_Bugs()
{
printf("\n\n go fix your bugs !\n");		
printf("                                  |     |\n");	
printf("                                  V__V_ /\n");
printf("                                   /=|=/\n");
printf("                                   [=v=]\n");
printf("                               ____V___/___\n");
printf("                              /..[  _____  ]\n");
printf("                             /_  [ [  M /] ]\n");
printf("                            /../.[ [ M /@] ]\n");
printf("                           <-->[_[ [M /@/] ]\n");
printf("                          /../ [.[ [ /@/ ] ]\n");
printf("     _________________]/ / _/  [_[ [/@/ C] ]\n");
printf("    <_________________>>0---]  [=/ /@/ C / /\n");
printf("       ___      ___   ]/000o   /__ / C / /\n");
printf("          /    /              /....| |_/ /\n");
printf("       ..../||/....           [___/=|___/\n");
printf("      .    .  .    .          [...] |...]\n");
printf("     .      ..      .         [___/ |___]\n");
printf("     .    0 .. 0    .         <---> <--->\n");
printf("  / / /.    .  .    ./ / /     [..]  [..]\n");
printf(" / / / .../|  |/... / / /    _[__]  [__]_\n");
printf("/ / /     	   / / /     [____>  <____])\n");

}
