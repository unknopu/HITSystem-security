#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    printf("Process kill, kill http service\n");
    char cmd[100];
    strcpy(cmd, "kill -9 ");
    strcat(cmd, argv[0]);
    printf("Invoke command: ");
    printf("%s\n", cmd);
    system(cmd);
    return 0;
}
