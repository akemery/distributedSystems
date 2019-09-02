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
  // ftok to generate unique key 
  key_t key = ftok("shmfile",65); 
  int i;
  int a = 0; // shared data
  // shmget returns an identifier in shmid 
  int shmid = shmget(key,1024,0666); 
  // shmat to attach to shared memory 
  char *str = (char*) shmat(shmid,(void*)0,0); 

  for(i=0; i < ITER; i++){
     a = atoi(str);
     printf("Proc %d %d\n", getpid(), a);
     a = a + 1;
     sleep(a);
     sprintf(str, "%d", a);
  }	
  //detach from shared memory 
  shmdt(str); 
  // destroy the shared memory 
  //shmctl(shmid,IPC_RMID,NULL);
  return 0; 
} 
