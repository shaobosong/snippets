#include <stdio.h>

void f(){}

int main (int argc, char **argv)
{
    // int i0 = &10;

    // int i1;
    // int *pi1 = &(i1 + 1);

    int i2;
    int *pi2 = &i2 + 1;
    printf("%p\n", pi2);

    // int i3;
    // int *pi = &i3++;

    // register int r = 10;
    // int *pr = &r;

    // struct {
    //         unsigned int flag : 1;
    // } s;
    // unsigned int *p = &s.flag;

    // int exp1 = 0, exp2 = 1;
    // int *pexp = &(exp1 + exp2);

    int a[10];
    printf("%p\n", a);

    int (*pa)[10] = &a;
    printf("%p\n", pa);

    void (*pf1)() = f;
    printf("%p\n", pf1);

    void (*pf2)() = &f;
    printf("%p\n", pf2);

    return 0;
}
