#define _GNU_SOURCE

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>

int main()
{
    extern int errno;

    uid_t ruid, euid, suid;
    getresuid(&ruid, &euid, &suid);
    printf("Process setuid，pid=%d\nruid=%d\neuid=%d\nsuid=%d\n",
        getpid(), ruid, euid, suid);
    pid_t pid;
    char httpServicePid[10];
    if((pid = fork()) < 0)
    {
        printf("Fork process error! %s\n", strerror(errno));
    } else if(!pid)
    {
        if(execl("/home/ubuntu/Desktop/lab1/http_server.o", "0", NULL) != 0)
        {
            printf("Invoke httpService error! %s\n", strerror(errno));
        }
    } else
    {
        sprintf(httpServicePid, "%d", pid);
    }

    setresuid(ruid, ruid, euid);
    printf("Revoke permission temporarily\n");
    getresuid(&ruid, &euid, &suid);
    printf("ruid=%d\neuid=%d\nsuid=%d\n", ruid, euid, suid);

    if((pid = fork()) < 0)
    {
        printf("Fork echo error! %s\n", strerror(errno));
    } else if(!pid)
    {
        if(execl("/home/ubuntu/Desktop/lab1/echo.o", "test message", "0", NULL) != 0)
        {
            printf("Invoke echo error! %s\n", strerror(errno));
        }
    } else
    {
        int stat_val;
        waitpid(pid, &stat_val, 0);
    }

    setresuid(ruid, suid, suid);
    printf("Restore permission \n");
    getresuid(&ruid, &euid, &suid);
    printf("ruid=%d\neuid=%d\nsuid=%d\n", ruid, euid, suid);

    if((pid = fork()) < 0)
    {
        printf("Fork kill error! %s\n", strerror(errno));
    } else if(!pid)
    {
        if(execl("/home/ubuntu/Desktop/lab1/kill.o", httpServicePid, "0", NULL) != 0)
        {
            char* errnoMeg = strerror(errno);
            printf("Invoke kill error! %s\n", errnoMeg);
        }
    } else
    {
        int stat_val;
        waitpid(pid, &stat_val, 0);
    }

    setresuid(ruid, euid, suid);
    printf("Revoke permission permanently\n");
    getresuid(&ruid, &euid, &suid);
    printf("ruid=%d\neuid=%d\nsuid=%d\n", ruid, euid, suid);

    return 0;
}
