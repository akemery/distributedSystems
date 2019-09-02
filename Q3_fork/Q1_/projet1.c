/**Ce programme lit en argument un fichier qui contient les notes des etudiants
 * il permet de :
 * - d'afficher les etudiant
 * - de calculer leur moyenne
 * 20/08/18
 * Auteur: Assogba Emery Kouassi assogba.emery@gmail.com*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "projet1.h"

int main(int argc, char *argv[])
{
    if(argc!=2){
       printf("USAGE projet1 data1.in\n");
       exit(1);
    }
    read_data(argv[1]);
    compute_etus_moy();
    write_data(argv[1]);
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
