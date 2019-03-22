#include <stdio.h>

int main(int argc, char const *argv[])
{
    int n;
    printf("Bienvenue dans le programme d'affichage tous les nombres premiers jusqu'à n !\n");
    printf("Entrez un nombre entier supérieur à 0 : ");
    do
    {
        scanf("%d", &n);
    } while (n <= 0);

    for (int i = 2; i <= n; i++)
    {
        int premier = 1;
        for (int loop = 2; loop <= i; loop++)
        {
            if ((i % loop) == 0 && loop != i)
            {
                premier = 0;
            }
        }

        if (premier != 0)
        {
            printf("%d\n", i);
        }
    }

    return 0;
}
