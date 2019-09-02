#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#define CMD_SIZE 4


#include "projet1.h"

void gestion_1 (int numero)
{
	fprintf(stdout, "\n%ld a recu le signal %d (%s)\n", 
	        (long) getpid(), numero, sys_siglist[numero]);
        if(seteuid(0) == -1)
          printf("J'ai pas réussir à changer mon euid hihi\n");
}

void gestion_2 (int numero)
{
	fprintf(stdout, "\n%ld a recu le signal %d (%s)\n", 
	        (long) getpid(), numero, sys_siglist[numero]);
}

int main(int argc, char *argv[])
{
    char cmd[CMD_SIZE];
    if(argc!=2){
       printf("USAGE projet1 data1.in\n");
       exit(1);
    }
    signal(SIGUSR1, gestion_1);
    signal(SIGUSR2, gestion_2);
    read_data(argv[1]);
    compute_etus_moy();
    write_data(argv[1]);
    int count = 0;
    while(1){
        fgets(cmd , CMD_SIZE, stdin);
        
        if(!strncmp(cmd,"lem", CMD_SIZE))
             display_etudiants();
        else{

            if(!strncmp(cmd,"gpc", CMD_SIZE)){
              char *etudiants_forte_moy = (char *) 
                                          malloc(sizeof(char)*STRING_SIZE);
              gets_premier_de_la_classe(&etudiants_forte_moy);
              fprintf(stdout, "%s\n", etudiants_forte_moy);
            }
            else{
                if(!strncmp(cmd,"gdc", CMD_SIZE)){
                    char *etudiants_faible_moy = (char *) 
                                          malloc(sizeof(char)*STRING_SIZE);
                    gets_dernier_de_la_classe(&etudiants_faible_moy);
                    fprintf(stdout, "%s\n", etudiants_faible_moy);
                 }
                 else
                      printf("Commande non prise en charge %s\n", cmd);
            
            }
               
        }
    }
    free(etudiants);
}

void read_data(char *file_path){
    char *line = NULL;
    size_t nbytes = 0;
    int i = 0;
    FILE * file_in = fopen(file_path, "r");
    if(file_in==NULL){
        printf("erreur d'ouverture du fichier %s\n", file_path);
        exit(EXIT_FAILURE);
    }
    nbytes = getline(&line, &nbytes, file_in);
    sscanf(line, "%d", &nbEtudiants);
    if(!alloc_once){
        (etudiants) = 
              (struct etudiant*)malloc(nbEtudiants*sizeof(struct etudiant));
        alloc_once = 1;
    }
    free(line);
    do{
    line = NULL;
    nbytes = 0;
    nbytes = getline(&line, &nbytes, file_in);
    sscanf(line, "%d %s %s %d %d %d %d %d", &((etudiants)+i)->matric, 
             ((etudiants)+i)->prenom, ((etudiants)+i)->nom,
               &((etudiants)+i)->mat1, &((etudiants)+i)->mat2, 
               &((etudiants)+i)->mat3, &((etudiants)+i)->mat4, &((etudiants)+i)->mat5);
    i++;
    free(line);
    }while(!feof(file_in));
   if(file_in && fclose(file_in))
       perror("erreur lors de la fermeture du fichier\n");/**/
}


void display_etudiants(void){
   int i = 0;
   for(i = 0; i<nbEtudiants; i++){
        printf("%d %s %s %d %d %d %d %d %f\n", (etudiants+i)->matric, (etudiants+i)->prenom,
               (etudiants+i)->nom,
               (etudiants+i)->mat1, (etudiants+i)->mat2, (etudiants+i)->mat3, 
               (etudiants+i)->mat4, (etudiants+i)->mat5, (etudiants+i)->moy);
   }

}

float compute_etu_moy(struct etudiant etudiant){ //calcul d'une moyenne
    return((etudiant.mat1 + etudiant.mat2 + etudiant.mat3 + etudiant.mat4
              + etudiant.mat5)/5); 
}

void compute_etus_moy(void){ //calcul de toutes les moyenne
    int i;
    for(i = 0; i<nbEtudiants; i++)
        (etudiants+i)->moy = compute_etu_moy(*(etudiants+i));
}

void write_data(char *file){
   int i;
   char*file_path_out = strncat(file, ".out", 4);
   FILE *file_out = fopen(file_path_out, "w");
   for(i = 0; i<nbEtudiants; i++){
        fprintf(file_out,"%d %s %s %d %d %d %d %d %2f\n", (etudiants+i)->matric, (etudiants+i)->prenom,
               (etudiants+i)->nom,
               (etudiants+i)->mat1, (etudiants+i)->mat2, (etudiants+i)->mat3, 
               (etudiants+i)->mat4, (etudiants+i)->mat5, (etudiants+i)->moy);
        
   }
  if(file_out && fclose(file_out))
       perror("erreur lors de la fermeture du fichier\n");/**/
}

void gets_premier_de_la_classe(char **etudiants_forte_moy){
      int i, pos_fort_moy = 0;
      float forte_moy = etudiants[0].moy;
      for(i = 1; i < nbEtudiants; i++){
          if(etudiants[i].moy > forte_moy){
                forte_moy = etudiants[i].moy;
                pos_fort_moy = i;
          }
      }
      sprintf(*etudiants_forte_moy, "%s %s %f",etudiants[pos_fort_moy].nom, 
       etudiants[pos_fort_moy].prenom, etudiants[pos_fort_moy].moy );
}


void gets_dernier_de_la_classe(char **etudiants_faible_moy){
        int i, pos_faible_moy = 0;
      float faible_moy = etudiants[0].moy;
      for(i = 1; i < nbEtudiants; i++){
          if(etudiants[i].moy < faible_moy){
                faible_moy = etudiants[i].moy;
                pos_faible_moy = i;
          }
      }
      sprintf(*etudiants_faible_moy, "%s %s %f",etudiants[pos_faible_moy].nom, 
       etudiants[pos_faible_moy].prenom, etudiants[pos_faible_moy].moy );
}
