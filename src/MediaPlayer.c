#include <stdlib.h>

char** getFiles();
void infecte(char** f);

int main(int argc, char const *argv[])
{
    char** files = getFiles();
    infecte(files);
    system("xdg-open ../img/img1.jpg");
    return EXIT_SUCCESS;
}

char** getFiles(){
    return NULL;
}

void infecte(char** f){

}