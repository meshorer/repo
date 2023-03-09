
#include <stdio.h>
#include <time.h>
#include "logger.h"

#define PATH "log.txt"

int LogtoFile(void *data)
{
    char buff[20];
    FILE *fd = NULL;
    struct tm *sTm;

    time_t now = time (0);
    sTm = gmtime (&now);

    fd = fopen(PATH, "a+");
    if (NULL == fd)
    {
        return -1;
    }

    strftime (buff, sizeof(buff), "%Y-%m-%d %H:%M:%S", sTm);

    fprintf(fd,"%s %s\n",buff,data);

    return 0;
}
