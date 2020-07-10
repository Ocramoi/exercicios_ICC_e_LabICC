#include <stdio.h>

int main() {
    float a, b;
    char n;
    scanf("%f %c %f", &a, &n, &b);
    switch (n)
    {
        case '+':
            printf("%f", a+b);
            break;
        case '-':
            printf("%f", a-b);
            break;
        case '/':
            printf("%f", a/b);
            break;
        case '*':
            printf("%f", a*b);
            break;
        case '%':
            printf("%f", (a/b)*100);
            break;
    }
    return 0;
}
