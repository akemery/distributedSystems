#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define CMD_SIZE 20
int main(int argc, char *argv[])
{
   char cmd1[CMD_SIZE] = "./Q1 ";
   char cmd2[CMD_SIZE] = "./Q1 ";
   char cmd3[CMD_SIZE] = "./Q1 ";
   strncat(cmd1, argv[1], CMD_SIZE);
   strncat(cmd2, argv[2], CMD_SIZE);
   strncat(cmd3, argv[3], CMD_SIZE);
   system(cmd1);
   system(cmd2);
   system(cmd3);
}
