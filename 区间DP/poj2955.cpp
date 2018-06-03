#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
#include <cmath>
#include <map>
#include <iostream>
using namespace std;
#define INF (1<<29)
#define LL long long
#define CLR(a,b) memset(a,b,sizeof(a))

#define MAXN 150
char s[MAXN];
int dp[MAXN][MAXN];

bool isOk(int i,int j)
{
    return (s[i]=='('&&s[j]==')')||(s[i]=='['&&s[j]==']');
}

int main()
{
    while (scanf("%s",s)!=EOF)
    {
        if (s[0]=='e')
            break;
        int n=strlen(s);
        CLR(dp,0);
        for (int len=0;len<n;len++)
            for (int i=0;i+len<n;i++)
            {
                int j=i+len;
                if (isOk(i,j))
                    dp[i][j]=dp[i+1][j-1]+2;
                for (int k=i;k<j;k++)
                    dp[i][j]=max(dp[i][j],dp[i][k]+dp[k+1][j]);
            }

        printf("%d\n", dp[0][n-1]);
    }
    return 0;
}