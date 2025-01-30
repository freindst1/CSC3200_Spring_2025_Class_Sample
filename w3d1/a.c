#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int main(){

   int fd;
   fd =  open("a.txt", O_RDONLY);
   printf("%d", fd);
   if (fd == -1){
      perror("open");
   }

   if (close(fd) == -1){
      perror("close");
   }


    fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644); //644 = 110100100 rw-r--r-- 

   return 0;
}