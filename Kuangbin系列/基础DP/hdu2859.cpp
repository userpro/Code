#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
#define maxn 1010
int n;
int dp[maxn][maxn];
char a[maxn][maxn];

int main()
{
    while (scanf("%d",&n)==1&&n)
    {
        memset(dp,0,sizeof(dp));
        memset(a,0,sizeof(a));
        for (int i = 0; i < n; ++i)
        {
            getchar();
            dp[0][i]=1;
            for (int j = 0; j < n; ++j)
                scanf("%c",&a[i][j]);
        }
        int ans=1;
        for (int i = 1; i < n; ++i)
        {
            for (int j = n-1; j >= 0; --j)
            {
                int x=j+1,y=i-1;
                int num=1;
                while (x>=0&&y>=0&&x<n&&y<n&&a[y][j]==a[i][x])
                {
                    num++; x++; y--;
                }
                if (num > dp[i-1][j+1])
                    dp[i][j]=dp[i-1][j+1]+1;
                else
                    dp[i][j]=num;
                ans=max(ans,dp[i][j]);
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}