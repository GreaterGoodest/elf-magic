#include <sys/mman.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdint.h>
#include <errno.h>
#include <stdio.h>

uint32_t check_tracer(){
    int32_t retval = 0;
    int32_t fd = 0;

    fd = open("/proc/self/status", O_RDONLY);
    if(fd == -1)
    {
        perror("open /proc/self/status");
        return errno;
    }

    char buff[1028];
    retval = read(fd, buff, sizeof(buff));
    if (retval == -1)
    {
        perror("read /proc/self/status");
        return errno;
    }

    char *line = NULL;
    const char *key = "TracerPid";
    line = strtok(buff, "\n");
    while (strncmp(line, key, sizeof(key)))
    {
        line = strtok(NULL, "\n");
    }

    char *pid_str = NULL;
    pid_str = strtok(line, ":");
    pid_str = strtok(NULL, "");

    int pid = strtol(pid_str, NULL, 10);

    if (pid != 0)
    {
        puts("Spy Discovered!");
        exit(0);
    }

    return 0;
}

int32_t virtualization_check()
{
    int32_t retval = 0;
    int32_t fd = 0;

    fd = open("/proc/cpuinfo", O_RDONLY);
    if(fd == -1)
    {
        perror("open /proc/cpuinfo");
        return errno;
    }

    char buff[1028];
    retval = read(fd, buff, sizeof(buff));
    if (retval == -1)
    {
        perror("read /proc/cpuinfo");
        return errno;
    }    

    const char *hyper_string = "hypervisor";    
    if (strstr(buff, hyper_string))
    {
        puts("We're virtualized!");
        exit(0);
    }
    return 0;
}

int main()
{
    int retval = check_tracer();    
    if (retval != 0)
    {
        puts("check tracer failed");
        return retval;
    }

    retval = virtualization_check();
    if (retval != 0)
    {
        puts("virtualization check failed");
        return retval;
    }

    puts("No Spy Found...");
}
