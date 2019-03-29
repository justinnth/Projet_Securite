#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    int n;

    printf("Bienvenue dans le programme qui divise votre nombre par 4\n");

    printf("Entrez un nombre :");
    scanf("%d", &n);

    printf("%d/4 = %lf", n, (float) n/4);
}

