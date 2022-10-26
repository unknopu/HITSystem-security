#include <stdio.h>

int main(int argc, char* argv[])
{
    int i counter=0;
    char** ptr;
    extern char** environ;
    printf("Process echo\n");
    for(i = 0; i < argc; i ++)
    {
        printf("argv[%d]=%s\n", i, argv[i]);
    }
    for(ptr=environ; counter!=5; ptr++)
    {
        printf("%s\n", *ptr);
        counter++;
    }
    return 0;
}
