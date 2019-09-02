#include <sys/socket.h>
#include <netinet/in.h>
 #include <arpa/inet.h>
 #include <sys/types.h>
 #include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define SRV_ADDR "127.0.0.1"
#define SRV_PORT 56789
#define BUFF_SIZE 32768

int readn(int fd, char *buff, int nbytes);
int writen(int fd, char *buff, int nbytes);

int main(int argc, char *argv[]){
   int cfd; // socket du client
   struct sockaddr_in srv_addr; // socket addr du serveur 
   char buff[BUFF_SIZE];

   cfd = socket(AF_INET, SOCK_STREAM, 0); // création de la socket
     if (cfd == -1) // traitement de l'erreur
         perror("Impossible de créer la socket que puis faire encore\n");
   /* donne une identite a la socket. */
   srv_addr.sin_family = AF_INET;
   srv_addr.sin_port = htons (SRV_PORT);
   inet_aton(SRV_ADDR, &srv_addr.sin_addr.s_addr);

   

   int fd = open(argv[1], 2);
   long size = lseek(fd, SEEK_END, 2);
   lseek(fd, 0, 0);

   // connexion au serveur 
   connect(cfd, (struct sockaddr *) &srv_addr, sizeof(struct sockaddr_in));
   snprintf(buff, BUFF_SIZE, "%ld", size);
   printf("%s\n", buff);
   send(cfd, buff, BUFF_SIZE, 0);

   send(cfd, argv[1], BUFF_SIZE, 0);
#if 1
   while(size > 0){ 
     bzero(buff, BUFF_SIZE);
     if(size > BUFF_SIZE){
         readn(fd, buff, BUFF_SIZE);
         send(cfd, buff, BUFF_SIZE, 0);
         size-=BUFF_SIZE;
     }
     else{
        readn(fd, buff, size);
        send(cfd, buff, size, 0);
        size-=size;
     }
      
   }
#endif
   close(cfd);

   close(fd);
   return(0);
}
/**Read n bytes from a descriptor
 ** Utiliser à la place de read lorsque fd est un flux*/

int readn(int fd, char *buff, int nbytes){
   int nleft, nread;
   nleft = nbytes;
   while(nleft > 0){
       nread = read(fd, buff, nleft);
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
 ** Utiliser à la place de write lorsque fd est un flux*/
int writen(int fd, char *buff, int nbytes){
   int nleft, nwritten;
   nleft = nbytes;
   while(nleft > 0){
       nwritten = write(fd, buff, nleft);
       if(nwritten <= 0)
           return(nwritten); // il ya eu une erreur
       nleft -= nwritten;
       buff += nwritten;
   }
   return(nbytes-nleft);
}
