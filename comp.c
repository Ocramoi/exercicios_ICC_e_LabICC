#include <stdio.h>
#include <math.h>

int main(int argc, char* argv[])
{
    int n;
    scanf("%d", &n);
    double vals[n][2], tam = 0;
    for(int k = 0; k < n; k++)
    {
        scanf("%lf %lf", &vals[k][0], &vals[k][1]);
    }
    for(int k = 0; k < n-1; k++)
    {
        tam += sqrt(pow(vals[k][0]-vals[k+1][0], 2.) + pow(vals[k][1]-vals[k+1][1], 2.));
    }
    printf("%.4lf", tam);
    return 0;
}