#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <stdio.h> 
#include <sys/sem.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>

#define ITER 10


int main() 
{ 
  // ftok to generate unique key 
  key_t shm_key = ftok("shmfile",65); 
  int i;
  // shmget returns an identifier in shmid 
  int shmid = shmget(shm_key,1024,0666); 

  // shmat to attach to shared memory 
  char *str = (char*) shmat(shmid,(void*)0,0); 
  
  for(i=0; i < ITER; i++){
     printf("Data read from memory: %s\n",str); 
  }
  //detach from shared memory 
  shmdt(str); 
	
  // destroy the shared memory 
  //shmctl(shmid,IPC_RMID,NULL); 
	
  return 0; 
} 

