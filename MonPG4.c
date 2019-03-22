#include <stdio.h>

int main(int argc, char const *argv[])
{
    int n,m;

    printf("Bienvenue dans le programme de calcul du PGCD !\n");

    printf("Entrez le premier nombre: ");
    scanf("%d", &n);

    printf("Entrez le deuxième nombre: ");
    scanf("%d", &m);

    printf("Le PGCD est de : %d\n", pgcd(n,m));
}

int pgcd(int n, int m)
{
  if(m==0)
     return n;
  return pgcd(m, n%m);
}
