#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>

//does the main has a pid?
int main(){
  printf("my p_id is %d\n", getpid());
  int pid = fork();
  if (pid == 0){//child
    printf("this is pid 0 (%d).\n", getpid());
  } else {//parent
    printf("this is not pid 0 (%d).\n", getpid());
  }
  return 0;
}