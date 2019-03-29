#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    char str[100], rStr[100];
    int i, j, len;
    printf("Bienvenue dans le programme qui inverse votre chaine de caractères\n");
    printf("Entrez une chaine de caractères : ");
    scanf("%s", &str);

    j = 0;
    len = strlen(str);
    for (i = len - 1; i >= 0; i--)
    {
        rStr[j++] = str[i];
    }
    rStr[i] = '\0';

    printf("Chaine inversée : %s\n", rStr);
    return 0;
}
