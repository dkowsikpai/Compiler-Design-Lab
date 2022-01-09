#include <stdio.h>

int countbit1(unsigned int);
int countbit2(unsigned int);

void main()
{
    unsigned int n;

    int x;
    char ch;
    printf("\nEnter N\n");
    scanf("%u", &n);
    printf("\n1. Loop Roll\n2. Loop UnRoll\n");
    printf("\nEnter your choice\n");
    scanf(" %c", &ch);
    switch (ch)
    {
    case '1':
        x = countbit1(n);
        printf("\nLoop Roll: Count of 1's: %d\n", x);
        break;
    case '2':
        x = countbit2(n);
        printf("\nLoop UnRoll: Count of 1's : %d\n", x);
        break;
    default:
        printf("\nWrong Choice\n");
    }
}

int countbit1(unsigned int n)
{
    int bits = 0, i = 0;
    while (n != 0)
    {
        if (n & 1)
            bits++;
        n >>= 1;
        i++;
    }
    printf("\nNumber of iterations %d", i);
    return bits;
}

int countbit2(unsigned int n)
{
    int bits = 0, i = 0;
    while (n != 0)
    {
        if (n & 1)
            bits++;
        if (n & 2)
            bits++;
        if (n & 4)
            bits++;
        if (n & 8)
            bits++;
        n >>= 4;
        i++;
    }
    printf("\nNumber of iterations %d", i);
    return bits;
}
