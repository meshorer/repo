
void Fix_Bugs();

void dragon();
void bunny();

int count_error = 0;



#define PRINT_TESTS(num) \
 if (0 == (num)) { \
            printf("\r"); \
        } else { \
            printf("\033[0;31mFAIL in file %s at line %d \033[0m\n",__FILE__, __LINE__); \
            count_error += 1;}
            
            
#define CHECK_ERROR(count_error) \
		if (count_error > 0){ \
		Fix_Bugs();}\
		else{bunny();}
		
	
	
	
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



void dragon()
{
    printf("\n\n Shlish Elyon !\n\n\n");
    printf("                 .\"-,.__\n");
    printf("                 `.     `.  ,\n");
    printf("              .--'  .._,'\"-' `.\n");
    printf("             .    .'         `'\n");
    printf("             `.   /          ,'\n");
    printf("               `  '--.   ,-\"'\n");
    printf("                `\"`   |  \\\n");
    printf("                   -. \\, |\n");
    printf("                    `--Y.'      ___.\n");
    printf("                         \\     L._, \\\n");
    printf("               _.,        `.   <  <\\                _\n");
    printf("             ,' '           `, `.   | \\            ( `\n");
    printf("          ../, `.            `  |    .\\`.           \\ \\_\n");
    printf("         ,' ,..  .           _.,'    ||\\l            )  '\".\n");
    printf("        , ,'   \\           ,'.-.`-._,'  |           .  _._`.\n");
    printf("      ,' /      \\ \\        `' ' `--/   | \\          / /   ..\\\n");
    printf("    .'  /        \\ .         |\\__ - _ ,'` `        / /     `.`.\n");
    printf("    |  '          ..         `-...-\"  |  `-'      / /        . `.\n");
    printf("    | /           |L__           |    |          / /          `. `.\n");
    printf("   , /            .   .          |    |         / /             ` `\n");
    printf("  / /          ,. ,`._ `-_       |    |  _   ,-' /               ` \\\n");
    printf(" / .           \\\"`_/. `-_ \\_,.  ,'    +-' `-'  _,        ..,-.    \\`.\n");
    printf(".  '         .-f    ,'   `    '.       \\__.---'     _   .'   '     \\ \\\n");
    printf("' /          `.'    l     .' /          \\..      ,_|/   `.  ,'`     L`\n");
    printf("|'      _.-\"\"` `.    \\ _,'  `            \\ `.___`.'\"`-.  , |   |    | \\\n");
    printf("||    ,'      `. `.   '       _,...._        `  |    `/ '  |   '     .|\n");
    printf("||  ,'          `. ;.,.---' ,'       `.   `.. `-'  .-' /_ .'    ;_   ||\n");
    printf("|| '              V      / /           `   | `   ,'   ,' '.    !  `. ||\n");
    printf("||/            _,-------7 '              . |  `-'    l         /    `||\n");
    printf(". |          ,' .-   ,' ||               | .-.        `.      .'     ||\n");
    printf(" `'        ,'    `\".'    |               |    `.        '. -.'       `'\n");
    printf("          /      ,'      |               |,'    \\-.._,.'/'\n");
    printf("          .     /        .               .       \\    .''\n");
    printf("        .`.    |         `.             /         :_,'.'\n");
    printf("          \\ `...\\   _     ,'-.        .'         /_.-'\n");
    printf("           `-.__ `,  `'   .  _.>----''.  _  __  /\n");
    printf("                .'        /\"'          |  \"'   '_\n");
    printf("               /_|.-'\\ ,\".             '.'`__'-( \\\n");
    printf("                 / ,\"'\"\\,'               `/  `-.|\"  \n");

}



void bunny()
{

printf("       (\\__/) \n");
printf("       (•ㅅ•)      Don’t talk to\n");
printf("    ＿ノヽ ノ＼＿      me or my son\n");
printf("`/　`/ ⌒Ｙ⌒ Ｙ  ヽ     ever again.\n");
printf("( 　(三ヽ人　 /　  |\n");
printf("|　ﾉ⌒＼ ￣￣ヽ   ノ\n");
printf("ヽ＿＿＿＞､＿_／\n");
printf("     ｜( 王 ﾉ〈  (\\__/)\n");
printf("     /ﾐ`ー― 彡 \\ (•ㅅ•)\n");
printf("    / ╰   ╯\\/   \\>\n");



}
