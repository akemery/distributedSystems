#define LINE_SIZE 1000
#define STRING_SIZE 100
struct etudiant{
    char nom[STRING_SIZE];
    char prenom[STRING_SIZE];
    int matric;
    int mat1, mat2, mat3, mat4, mat5;
    float moy;
};

void read_data(char *file_path);
void display_etudiants(void);
float compute_etu_moy(struct etudiant);
void compute_etus_moy(void);
void write_data(char *file);
void gets_premier_de_la_classe(char **etudiants_forte_moy);
void gets_dernier_de_la_classe(char **etudiants_faible_moy);

struct etudiant *etudiants;
int nbEtudiants;
int alloc_once = 0;
