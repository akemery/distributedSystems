#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "projet1.h"

int main(int argc, char *argv[])
{
    char data1_in[9],data2_in[9],data3_in[9];
    if(argc!=4){
       printf("USAGE projet1 data1.in data2.in data3.in\n");
       exit(1);
    }

    
    sscanf(argv[1], "%s", data1_in);
    sscanf(argv[2], "%s", data2_in);
    sscanf(argv[3], "%s", data3_in);
    read_data(data1_in);
    compute_etus_moy();
    write_data(data1_in);

    read_data(data2_in);
    compute_etus_moy();
    write_data(data2_in);
  
     read_data(data3_in);
    compute_etus_moy();
    write_data(data3_in);/**/
    fcloseall();
    free(etudiants);
}

void read_data(char *file_path){
    char *line;
    size_t nbytes = 0;
    int i = 0;
    printf("filename %s\n", file_path);
    FILE *file_in = fopen(file_path, "r");
    if(file_in==NULL){
        printf("erreur d'ouverture du fichier %s\n", file_path);
    }
    nbytes = getline(&line, &nbytes, file_in);
    sscanf(line, "%d", &nbEtudiants);
    if(!alloc_once){
        printf("execute hi\n");
        (etudiants) = 
              (struct etudiant*)malloc(nbEtudiants*sizeof(struct etudiant));
        alloc_once = 1;
    }

    do{
    nbytes = getline(&line, &nbytes, file_in);
    sscanf(line, "%d %s %s %d %d %d %d %d", &((etudiants)+i)->matric, 
             ((etudiants)+i)->prenom, ((etudiants)+i)->nom,
               &((etudiants)+i)->mat1, &((etudiants)+i)->mat2, 
               &((etudiants)+i)->mat3, &((etudiants)+i)->mat4, &((etudiants)+i)->mat5);
    i++;
    printf("hihi %d\n",i);
    }while(!feof(file_in));
    printf("before end read filename %s\n", file_path);
   if(file_in == NULL)
       printf("NULL end read filename %s\n", file_path);
   /*if(file_in && fclose(file_in))
       perror("erreur lors de la fermeture du fichier\n");*/
    printf("end read filename %s\n", file_path);
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

float compute_etu_moy(struct etudiant etudiant){
    return((etudiant.mat1 + etudiant.mat2 + etudiant.mat3 + etudiant.mat4
              + etudiant.mat5)/5); 
}

void compute_etus_moy(void){
    int i;
    for(i = 0; i<nbEtudiants; i++)
        (etudiants+i)->moy = compute_etu_moy(*(etudiants+i));
}

void write_data(char *file){
    int i;
   char*file_path_out = strncat(file, ".out", 4);
   printf("filename out %s\n", file_path_out);
   FILE *file_out = fopen(file_path_out, "w");
   for(i = 0; i<nbEtudiants; i++){
        fprintf(file_out,"%d %s %s %d %d %d %d %d %2f\n", (etudiants+i)->matric, (etudiants+i)->prenom,
               (etudiants+i)->nom,
               (etudiants+i)->mat1, (etudiants+i)->mat2, (etudiants+i)->mat3, 
               (etudiants+i)->mat4, (etudiants+i)->mat5, (etudiants+i)->moy);
        
   }
    if(file_out == NULL)
       printf("NULL end read filename %s\n", file_path_out);
  /*if(file_out && fclose(file_out))
       perror("erreur lors de la fermeture du fichier\n");*/
}
