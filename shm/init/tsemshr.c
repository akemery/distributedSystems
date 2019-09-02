#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <stdio.h> 
#include <sys/sem.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>

#define ITER 10

union semun {
   int  val;    /* Value for SETVAL */
   struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
   unsigned short  *array;  /* Array for GETALL, SETALL */
   struct seminfo  *__buf;  /* Buffer for IPC_INF
                              (Linux-specific) */
};


int main() 
{ 
  // ftok to generate unique key 
  key_t shm_key = ftok("shmfile",65); 
  key_t sem_key = ftok("semfile",75);
  union semun sem_arg;
  struct sembuf sb = {0, -2, 0};
  int i;
  // shmget returns an identifier in shmid 
  int shmid = shmget(shm_key,1024,0666|IPC_CREAT); 

  int semid = semget(sem_key, 1, 0666|IPC_CREAT);
  // shmat to attach to shared memory 
  char *str = (char*) shmat(shmid,(void*)0,0); 
  sem_arg.val = 1;
  
  if(semctl(semid, 0, SETVAL, sem_arg)==-1){
     perror("semctl");
     exit(1);
  }
  
  for(i=0; i < ITER; i++){
     if(semop(semid, &sb,1) == -1){
       perror("sempo");
       exit(1);
     }
     printf("Data read from memory: %s\n",str); 
  }

  if(semctl(semid, 0, IPC_RMID, sem_arg) == -1){
    perror("semctl");
     exit(1);
  }
  //detach from shared memory 
  shmdt(str); 
	
  // destroy the shared memory 
  shmctl(shmid,IPC_RMID,NULL); 
	
  return 0; 
} 

