
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
    pid_t pid;
    int status = 0;

    pid = fork();

    if(pid == -1){
        printf("Error in forking\n");
        exit(1);
    }
    else if(pid == 0){
        printf("In the child process\n");
        printf("PID: %d\n", getpid());
        printf("Parent PID: %d\n", getppid());
    }
    else{
        printf("In the parent process\n");
        printf("PID: %d\n", getpid());
        printf("Parent PID: %d\n", getppid());
    }
    return 0;
}