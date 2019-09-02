/** Ce code lance deux processus qui modifie de façon concurrente
 *  une variable partagée se trouvant dans une mémoire partagée
 *  Abomey-Calavi le 13/07/19
 *  Auteur: Assogba Emery Kouassi assogba.emery@gmail.com*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h> 
#include <sys/shm.h>  
#include <sys/sem.h>
#include <errno.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    pid_t pid1, pid2, pid3;
    int status;
    char *argp1[] = {"w", NULL, NULL};
    
    // ftok to generate unique key 
    key_t key = ftok("shmfile",65); 
    int a = 0; // shared data
    // shmget returns an identifier in shmid 
    int shmid = shmget(key,1024,0666|IPC_CREAT); 
    // shmat to attach to shared memory 
    char *str = (char*) shmat(shmid,(void*)0,0); 
    // initialise la mémoire partagée à 0
    sprintf(str, "%d", a);
    // creation du premier processus
    pid1 = fork();
    if(pid1 < 0){
          perror("Erreur de création du processus\n");
          exit(EXIT_FAILURE);
    }

    if(pid1 == 0){
        execv("./w", argp1);
    }

    else{
        char *argp2[] = {"Q1", NULL, NULL};
        sleep(7);
        // creation du second processus
        pid2 = fork();
        if(pid2 < 0){
          perror("Erreur de création du second processus\n");
          pid1 = wait(&status);
          exit(EXIT_FAILURE);
        }

        if(pid2 == 0){
            execv("./w", argp2);
        }

        else{
               // attente des deux fils 
                pid1 = wait(&status);
                printf("Status de l'arret du fils %d %d\n", status, pid1);
                pid2 = wait(&status);
                printf("Status de l'arret du fils %d %d\n", status, pid2);
                // lecture de la valeur finale
                a = atoi(str);
                printf("Valeur Finale de a = %d\n", a);
                //detacche str de la mémoire partagée
                shmdt(str); 
                // detruit la mémoire partagée 
                shmctl(shmid,IPC_RMID,NULL);
        }

        
    } 
}
