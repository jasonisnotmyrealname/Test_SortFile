//#define _GNU_SOURCE
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char * argv[])
{
    struct dirent **namelist;
    int n,i;

    n = scandir(argv[1], &namelist, 0, versionsort);
    if (n < 0)
        perror("scandir");
    else
    {
        for(i =0 ; i < n; ++i)
        {
            printf("%s\n", namelist[i]->d_name);
            free(namelist[i]);
        }
        free(namelist);
    }
    return 0;
}
