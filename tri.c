#include <stdio.h>
#include <math.h>

int main(int argc, char* argv[])
{
    int a, b, c;
    scanf("%d %d %d", &a, &b, &c);
    printf("%s", (powf((a > b && a > c) ? a : ((b > a && b > c) ? b : c), 2.) ==
                           powf(a, 2.) + powf(b, 2.) + powf(c, 2.) - powf((a > b && a > c) ? a : ((b > a && b > c) ? b : c), 2.)) ? "SIM" : "NAO");
    return 0;
}