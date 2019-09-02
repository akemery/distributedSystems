#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define CMD_SIZE 20
int main(int argc, char *argv[])
{
   size_t nbytes = 0;
   char *line = NULL;
   char cmd1[CMD_SIZE] = "./Q1_popen ";
   char cmd2[CMD_SIZE] = "./Q1_popen ";
   char cmd3[CMD_SIZE] = "./Q1_popen ";
   strncat(cmd1, argv[1], CMD_SIZE);
   strncat(cmd2, argv[2], CMD_SIZE);
   strncat(cmd3, argv[3], CMD_SIZE);
   FILE *stream1 = popen(cmd1, "r");
   FILE *stream2 = popen(cmd2, "r");
   FILE *stream3 = popen(cmd3, "r");

   do{
      line = NULL;
      nbytes = 0;
      nbytes = getline(&line, &nbytes, stream1);
      printf("toto ::: %s\n", line);
      free(line);
    }while(!feof(stream1));

   do{
      line = NULL;
      nbytes = 0;
      nbytes = getline(&line, &nbytes, stream2);
      printf("toto ::: %s\n", line);
      free(line);
    }while(!feof(stream2));

    do{
      line = NULL;
      nbytes = 0;
      nbytes = getline(&line, &nbytes, stream3);
      printf("toto ::: %s\n", line);
      free(line);
    }while(!feof(stream3));
}
