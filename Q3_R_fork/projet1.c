#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

pid_t pidchld = 0;

void gestion_alarm (int numero)
{
	fprintf(stdout, "\n%ld a recu le signal %d (%s)\n", 
	        (long) getpid(), numero, sys_siglist[numero]);
        kill(pidchld, SIGUSR1);
        alarm(5);
}


void gestion_chld (int numero)
{
        int status;
	fprintf(stdout, "\n%ld a recu le signal %d (%s)\n", 
	        (long) getpid(), numero, sys_siglist[numero]);
         pidchld = wait(&status);
         printf("Status de l'arret du fils %d %d\n", status, pidchld);
}

int main(int argc, char *argv[])
{
    pid_t pid1, pid2, pid3;
    int status;

    signal(SIGALRM, gestion_alarm);
    char *argp1[] = {"Q1_R", argv[1], NULL};
    if(argc!=4){
       printf("USAGE projet1 data1.in data2.in data3.in\n");
       exit(1);
    }

    pidchld = fork();
    if(pidchld < 0){
          perror("Erreur de création du processus\n");
          exit(EXIT_FAILURE);
    }

    if(pidchld == 0){
        execv("./Q1_R", argp1);
    }

    else{
           alarm(5);  
           while(1)
               pause();  
        }        
}
