#include <stdio.h>
#include <stdlib.h>

int main () {
   FILE * fp;

   fp = fopen ("file.txt", "w+");
   fprintf(fp, "%s %s %s %d", "We", "are", "in", 2024);
   
   fclose(fp);

   printf("Done with creating \"file.txt\"");

   return(0);
}