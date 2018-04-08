// 根据LCS的原理, 将每个字符都进行标记, 看两个字符串中对应的字符究竟处于什么状态, 然后输出, 
// 其标记为公共子串的字符只输出一次即可, 也是一道模板题了
// 回溯 LCS
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
#define MAXN 1010
char s1[MAXN],s2[MAXN];
int dp[MAXN][MAXN],mark[MAXN][MAXN];

void lcs(int len1,int len2)
{
    memset(dp,0,sizeof(dp));
    for (int i=0;i<=len1;i++)
        mark[i][0]=1;
    for (int i=0;i<=len2;i++)
        mark[0][i]=-1;
    for (int i=1;i<=len1;i++)
        for (int j=1;j<=len2;j++)
            if (s1[i-1]==s2[j-1])
            {
                dp[i][j]=dp[i-1][j-1]+1;
                mark[i][j]=0;
            }
            else
            {
                if (dp[i-1][j]>=dp[i][j-1])
                {
                    dp[i][j]=dp[i-1][j];
                    mark[i][j]=1;
                }
                else
                {
                    dp[i][j]=dp[i][j-1];
                    mark[i][j]=-1;
                }
            }
}

void printlcs(int i,int j)
{
    if (!i&&!j)
        return;
    if (mark[i][j]==0)
    {
        printlcs(i-1,j-1);
        printf("%c", s1[i-1]);
    }
    else if (mark[i][j]==1)
    {
        printlcs(i-1,j);
        printf("%c", s1[i-1]);
    }
    else
    {
        printlcs(i,j-1);
        printf("%c", s2[j-1]);
    }
}

int main()
{
    while (scanf("%s%s",s1,s2)!=EOF)
    {
        int len1=strlen(s1);
        int len2=strlen(s2);
        lcs(len1,len2);
        printlcs(len1,len2);
        printf("\n");
    }
    return 0;
}
