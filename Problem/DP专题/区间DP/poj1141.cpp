#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
#include <map>
#include <iostream>
using namespace std;
#define INF (1<<29)
#define LL long long
#define CLR(a,b) memset(a,b,sizeof(a))

#define MAXN 110
char s[MAXN];
int dp[MAXN][MAXN],path[MAXN][MAXN];

void output(int l,int r)
{
    if (l>r)
        return;
    if (l==r)
    {
        if (s[l]=='('||s[l]==')')
            printf("()");
        else
            printf("[]");
        return;
    }
    if (path[l][r]==-1)
    {
        putchar(s[l]);
        output(l+1,r-1);
        putchar(s[r]);
    }
    else
    {
        output(l,path[l][r]);
        output(path[l][r]+1,r);
    }
}

int main()
{
    while (gets(s+1))
    {
        int len=strlen(s+1);
        CLR(dp,0);
        for (int i=1;i<=len;i++)
            dp[i][i]=1;
        for (int l=1;l<len;l++)
            for (int i=1;i<=len-l;i++)
            {
                int j=i+l;
                dp[i][j]=INF;
                if ((s[i]=='['&&s[j]==']')||(s[i]=='('&&s[j]==')'))
                    if (dp[i+1][j-1]<dp[i][j])
                    {
                        dp[i][j]=dp[i+1][j-1];
                        path[i][j]=-1;
                    }

                for (int k=i;k<j;k++)
                    if (dp[i][k]+dp[k+1][j]<dp[i][j])
                    {
                        dp[i][j]=dp[i][k]+dp[k+1][j];
                        path[i][j]=k;
                    }
            }

        output(1,len);
        putchar('\n');
    }
    return 0;
}