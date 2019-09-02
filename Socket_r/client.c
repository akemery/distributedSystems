#include <sys/socket.h>
#include <netinet/in.h>
 #include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define SRV_ADDR "192.168.43.158"
#define SRV_PORT 56789

int main(int argc, char *argv[]){
   int cfd; // socket du client
   struct sockaddr_in srv_addr; // socket addr du serveur 

   cfd = socket(AF_INET, SOCK_STREAM, 0); // création de la socket
     if (cfd == -1) // traitement de l'erreur
         perror("Impossible de créer la socket que puis faire encore\n");
   /* donne une identite a la socket. */
   srv_addr.sin_family = AF_INET;
   srv_addr.sin_port = htons (SRV_PORT);
   inet_aton(SRV_ADDR, &srv_addr.sin_addr.s_addr);

   // connexion au serveur 
   connect(cfd, (struct sockaddr *) &srv_addr, sizeof(struct sockaddr_in));
   send(cfd, "BONJOUR", 10, 0);

   close(cfd);
   return(0);
}

