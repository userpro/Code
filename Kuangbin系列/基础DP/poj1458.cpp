#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
#define MAXN 1010
char X[MAXN],Z[MAXN];
int dp[MAXN][MAXN];

int main()
{
    while (scanf("%s%s",X,Z)==2)
    {
        memset(dp,0,sizeof(dp));
        int lenx=strlen(X);
        int lenz=strlen(Z);
        for (int i = 0; i < lenx; ++i)
        {
            for (int j = 0; j < lenz; ++j)
            {
                if (Z[j]==X[i])
                    dp[i+1][j+1]=dp[i][j]+1;
                else
                    dp[i+1][j+1]=max(dp[i][j+1],dp[i+1][j]);
            }
        }
        printf("%d\n", dp[lenx][lenz]);
    }
    return 0;
}