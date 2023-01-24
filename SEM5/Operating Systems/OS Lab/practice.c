#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>

#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <dirent.h>

#include <string.h>

#include <pthread.h>
// struct Process{
//   int ProcessSize[10];
//   int Priority[10];
// };

void* child_thread(void* param){
  printf("In child thread\n");
  return NULL;
}

int counter = 0;
void * func(void * params) {
counter++;
}

int main(){

  // read, write - return bytes read or written
  /*
  char buf[10];
  //printf("%lu", sizeof(buf)/sizeof(char));
  int nread = read(0, buf, 10);
  //if((write(0, buf, nread))!=nread)
  //  write(2, "Error occured\n", 13);
  printf("%s %d", buf, nread);
  //close(fa); close(fb);
  */


  // open, close - return file descriptor
  /*
  char c;
  int in = open("prTxtIn.txt", O_RDONLY);
  int out = open("prTxtOut.txt", O_WRONLY);

  int o = lseek(in, -1, SEEK_END);
  //printf("%d", o);
  int i = -1;
  while(read(in, &c, 1) == 1 && (o =! (-i))){
    lseek(in, --i, SEEK_END);
    write(out, &c, 1);
  }
  */


  // 
  //mkdir("/Users/siddhartha/Desktop/MIT_Academics/Academics/Operating Systems/OS Lab/practiceDirectory", O_RDONLY | O_WRONLY);
  //rmdir("/Users/siddhartha/Desktop/MIT_Academics/Academics/Operating Systems/OS Lab/practiceDirectory");


  // Fork
  /*
  pid_t pid;
  pid = fork();
  int i = 0;
  int status = 5;
  switch(pid){
    case -1:
      printf("ERROR FORKING\n");
    case 0:
      printf("I'm a child\t%d\n", getpid());
      execlp("/bin/ls", "ls", NULL);
    default:
      wait(&status);
      printf("I'm a parent %d\t%d\n", i++, getppid());
      printf("Child returned: %d\n", status);
  }
  */

  /*
  int ret;
  struct stat* sb;
  ret = stat("/Users/siddhartha/Desktop/SINCHANA.pdf", sb);
  printf("%hu\n", sb->st_nlink);
  */

/*
  int n;
int fd[2];
char buf[1025];
char *data = "hello... this is sample data"; pipe(fd);
write(fd[1], data, strlen(data));
if ((n = read(fd[0], buf, 28)) >= 0) {
buf[n] = 0; // terminate the string
printf("read %d bytes from the pipe: \"%s\"\n", n, buf); }
else
perror("read");
exit(0);
*/

pthread_t thread1, thread2; 
pthread_create(&thread1, 0, func, 0); 
pthread_create(&thread2, 0, func, 0); 
pthread_join(thread1, 0 ); 
pthread_join(thread2, 0 );
printf("%d", counter);
}