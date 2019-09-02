/** Ce code modifie de façon non atomique une variable partagée
 *  une variable partagée se trouvant dans une mémoire partagée
 *  Abomey-Calavi le 13/07/19
 *  Auteur: Assogba Emery Kouassi assogba.emery@gmail.com*/
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <stdio.h> 
#include <sys/sem.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#define ITER 10



int main() 
{ 
  // generation de la clé pour la mémoire partagée
  key_t key = ftok("shmfile",65); 
  int i;
  int a = 0; // shared data
  // SE crée la mémoire partagée 
  int shmid = shmget(key,1024,0666); 
  // lie la memoire partagée a str 
  char *str = (char*) shmat(shmid,(void*)0,0); 

  for(i=0; i < ITER; i++){
     // lecture de a
     a = atoi(str);
     printf("Proc %d %d\n", getpid(), a);
     // modification de a
     a = a + 1;
     sleep(a);
     // ecriture de a
     sprintf(str, "%d", a);
  }	
  //detache str de la mémoire partagée
  shmdt(str); 
  return 0; 
} 
