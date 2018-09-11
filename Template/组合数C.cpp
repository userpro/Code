#include <cstdio>
typedef long long LL;
LL C[40][40];

void _init()
{
    C[0][0]=C[1][0]=C[1][1]=1;
    for (int i=2;i<40;i++)
    {
        C[i][0]=1;
        for (int j=1;j<i;j++)
            C[i][j]=C[i-1][j-1]+C[i-1][j];
        C[i][i]=1;
    }
}
