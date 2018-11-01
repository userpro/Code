#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
#define MAXN 1010
char s1[MAXN],s2[MAXN];
int dp[MAXN][MAXN];

int main()
{
    while (scanf("%s%s",s1,s2)!=EOF)
    {
        memset(dp,0,sizeof(dp));
        int len1=strlen(s1);
        int len2=strlen(s2);
        for (int i=0;i<len1;i++)
            for (int j=0;j<len2;j++)
                if (s1[i]==s2[j])
                    dp[i+1][j+1]=dp[i][j]+1;
                else
                    dp[i+1][j+1]=max(dp[i+1][j],dp[i][j+1]);
        printf("%d\n", dp[len1][len2]);
    }
    return 0;
}