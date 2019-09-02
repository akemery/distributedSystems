#include <sys/socket.h>
#include <netinet/in.h>
 #include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define MY_ADDR "127.0.0.1"
#define MY_PORT 56789
#define LISTEN_BACKLOG 50
#define BUFF_SIZE 32768

int readn(int fd, char *buff, int nbytes);
int written(int fd, char *buff, int nbytes);

int main(int argc, char *argv[]){
   int sfd; // socket du serveur
   int cfd; // socket du client
   struct sockaddr_in my_addr; // socket addr du serveur 
   struct sockaddr_in peer_addr; // socket addr d'un client

   socklen_t peer_addr_size; // la taille du sock
   pid_t child;

   char buffer[BUFF_SIZE];
   char name[BUFF_SIZE];

   sfd = socket(AF_INET, SOCK_STREAM, 0); // création de la socket
     if (sfd == -1) // traitement de l'erreur
         perror("Impossible de créer la socket que puis faire encore\n");

   memset(&my_addr, 0, sizeof(struct sockaddr_in)); /* reinitialiser la structure */
   
    /* donne une identite a la socket. */
   my_addr.sin_family = AF_INET;
   my_addr.sin_port = htons (MY_PORT);
   inet_aton(MY_ADDR, &my_addr.sin_addr.s_addr);
  
   // on demande au SE de confirmer l'identité de la socket
   if (bind(sfd, (struct sockaddr *) &my_addr,
                   sizeof(struct sockaddr_in)) == -1)
       perror("bind error\n");

   // on définit le nombre de clients que le serveur peut traiter en même temps
   if (listen(sfd, LISTEN_BACKLOG) == -1)
               perror("listen\n");

   // on se bloque en attendant les connexion des client
   peer_addr_size = sizeof(struct sockaddr_in);
   while(1){
   cfd = accept(sfd, (struct sockaddr *) &peer_addr,
                   &peer_addr_size);
   
   if (cfd == -1)
               perror("accept\n");
   child = fork();
   if(child < 0)
      perror("errreur de création du fils\n");

   if(child==0){
         printf("indentité du client %d\n", peer_addr.sin_port);
         read(cfd, buffer, BUFF_SIZE);
         long size = atol(buffer);
         read(cfd, name, BUFF_SIZE);
         printf("%s\n", name);
         int fd = creat(name, 2);
         if(fd < 0)
            perror("Impossible d'ouvrir le fichier");
#if 1
         while(size > 0){ 
          // bzero(buffer, BUFF_SIZE);
           int rsize, wsize;
           if(size > BUFF_SIZE){
             rsize = read(cfd, buffer, BUFF_SIZE);
             wsize = written(fd, buffer, BUFF_SIZE);
             size-=BUFF_SIZE;
           }
           else{
             rsize = read(cfd, buffer, size);
             wsize = written(fd, buffer, size);
             size-=size;
           }
         }
#endif
         close(sfd);
         close(fd);
         break;
   }

   else{
       close(cfd);
   }
  }
}


/**Read n bytes from a descriptor
 ** Utiliser à la place de read lorsque fd est un flux*/

int readn(int fd, char *buff, int nbytes){
   int nleft, nread;
   nleft = nbytes;
   while(nleft > 0){
       nread = read(fd, buff, nleft);
       printf("lecture %d\n", nread);
       if(nread < 0)
           return(nread); // il ya eu une erreur
       else if(nread == 0)
           break;  // la fin du fichier est atteint
       nleft -= nread;
       buff += nread;
   }

   return(nbytes-nleft);
}

/**Ecrire n bytes from a descriptor
 ** Utiliser à la place de read lorsque fd est un flux*/
int written(int fd, char *buff, int nbytes){
   int nleft, nwritten;
   nleft = nbytes;
   while(nleft > 0){
       nwritten = write(fd, buff, nleft);
       printf("ecriture %d\n", nwritten);
       if(nwritten <= 0)
           return(nwritten); // il ya eu une erreur
       nleft -= nwritten;
       buff += nwritten;
   }
   return(nbytes-nleft);
}
