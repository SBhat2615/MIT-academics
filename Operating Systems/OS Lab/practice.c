#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main()
{
pid_t pid;
/* fork another process */
pid = fork();
if (pid < 0) { /* error occurred */
fprintf(stderr, "Fork Failed");
exit(-1); }
else if (pid == 0) { /* child process */
  printf("In child process\n");
 execlp("/bin/ls", "ls", NULL);
}
else { /* parent process */
/* parent will wait for the child to complete */
printf("In parent process\nWaiting for child to complete\n");
wait (NULL);
printf ("Child Complete\n");
exit(0);
} }
