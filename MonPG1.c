#include <stdio.h>

int main(int argc, char const *argv[])
{
    int n;
    printf("Entrez un nombre n : \n");
    scanf("%d", &n);

    int fibo = fibonnacci(n);
    printf("Fibonnacci : %d\n", fibo);

    return 0;
}

int fibonnacci(int n){
    int tmp, i = 0, j = 1;
    for(int k = 0; k < n; k++)
    {
        tmp = i + j;
        i = j;
        j = tmp;
    }
    return i;
}
