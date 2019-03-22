#include <stdio.h>

int main(int argc, char const *argv[])
{
    int n,m;
    
    printf("Bienvenue dans le programme de calcul du PGCD !\n");

    printf("Entrez le premier nombre: ");
    scanf("%d\n", &n);*

    printf("Entrez le deuxième nombre: ");
    scanf("%d", &m);

    pgcd(n,m);
}

int pgcd(int n, int m)
{
  if(m==0)
     return n;
  return pgcd(m, n%m);
}
