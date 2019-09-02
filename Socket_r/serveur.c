#include <sys/socket.h>
#include <netinet/in.h>
 #include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define MY_ADDR "192.168.43.158"
#define MY_PORT 56789
#define LISTEN_BACKLOG 50

int main(int argc, char *argv[]){
   int sfd; // socket du serveur
   int cfd; // socket du client
   struct sockaddr_in my_addr; // socket addr du serveur 
   struct sockaddr_in peer_addr; // socket addr d'un client

   socklen_t peer_addr_size; // la taille du sock
   pid_t child;

   char buffer[10];

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
         read(cfd, buffer, 10);
         printf("%s\n", buffer);
         close(sfd);
         break;
   }

   else{
       close(cfd);
   }
  }
}
