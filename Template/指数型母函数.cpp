#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

const int N = 100;
double c1[N], c2[N],a[N];
int val[N];
void Factorial()
{
    a[0]=1;
    a[1]=1;
    for(int i = 2; i <=20; i++)
    {
        a[i]=a[i-1]*i;
    }
}
int main()
{
    int n, m, i, j, k;
    Factorial();
    while(~scanf("%d%d", &n, &m))
    {
        for(i = 0; i < n; ++ i)
        {
            scanf("%d", &val[i]);
        }
        memset(c1, 0, sizeof(c1));
        memset(c2, 0, sizeof(c2));

        for(i = 0; i <= val[0]; ++i)
        {
            c1[i] = 1.0/a[i];
        }
        for(i = 1; i < n; i++)
        {
            for(j = 0; j <= m; ++j)
                for(k = 0; k + j <= m && k <= val[i]; ++k)
                    c2[j + k] += c1[j]/a[k];
                
            for(j = 0; j <= m; ++j)
            {
                c1[j] = c2[j];
                c2[j] = 0;
            }
        }
        printf("%.0lf\n", c1[m]*a[m]);
    }
    return 0;
}