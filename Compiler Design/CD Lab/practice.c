#include <stdio.h>
#include <fcntl.h>

int main(){
  FILE  *fd1, *fd2;
  fd1 = fopen("output.txt", "r");
  if(fd1 == NULL){
    perror("Error opening file 1 !!");
  }
  fd2 = fopen("output.txt", "w+");
  if(fd2 == NULL){
    perror("Error opening file 2 !!");
  }
  int offset = 0;
  
  int size = 
  char c;
  while(i != size){
    fseek(fd1, --offset, SEEK_END);
    c = fgetc(fd1);
    if(c == '\n'){
      fputc('\n', fd2);
    }
    else{
      fputc(c, fd2);
    }
    c = fgetc(fd1);
  }
  
  fclose(fd1);
  fclose(fd2);
}