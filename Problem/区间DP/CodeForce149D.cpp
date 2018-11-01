// https://blog.csdn.net/stay_accept/article/details/51338117

// 给出的括号序列，括号的匹配都是固定的，也就是说只需要给这些固定匹配的括号按照上面限制涂色就好啦。

// 　　可以定义 dp[l][r][x][y] 表示区间 [l, r] 在左端点涂x色，右端点涂y色的情况下的方案数。其中0代表不涂色， 1代表涂红色， 2代表涂蓝色。

// 　　窝们可以把括号序列可以分为两类分别进行状态转移：

// 　　括号套括号，状态转移是：dp[l][r][x][y] += dp[l+1][r-1][x'][y'] (0<=x'<3, x'!=x, 0<=y'<3, y!=y')

// 　　多个匹配串连起来，转台转移是：dp[l][r][x][y] += dp[l][nu][x'][y'] * dp[nu][r][x''][y''] (nu是l对应的另一边括号)

// 　　当l+1 == r的时候有：dp[l][r][0][1] = 1;　　dp[l][r][1][0] = 1;

// 　　　　　　　　　　　　 dp[l][r][0][2] = 1;　　dp[l][r][2][0] = 1;

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

#define MOD 1000000007
#define MAXN 750
char s[MAXN];
LL dp[MAXN][MAXN][3][3],a[MAXN],b[MAXN];
int main()
{
    while (scanf("%s",s+1)!=EOF)
    {
        int n=strlen(s+1);
        CLR(a,0); CLR(b,0);
        CLR(dp,0);

        int p=1;
        for (int i=1;i<=n;i++)
        {
            if (s[i]=='(')
                a[p++]=i;
            else
            {
                b[a[p-1]]=i;
                b[i]=a[p-1];
                p--;
            }
        }

        for (int i=1;i<n;i++)
        {
            if (b[i]==i+1)
            {
                dp[i][i+1][0][1]=dp[i][i+1][1][0]=1;
                dp[i][i+1][0][2]=dp[i][i+1][2][0]=1;
            }
        }

        for (int l=2;l<=n;l++)
            for (int i=1;i+l-1<=n;i++)
            {
                int j=i+l-1;
                if (b[i]==j)
                {
                    dp[i][j][0][1]+=(dp[i+1][j-1][0][0]+dp[i+1][j-1][0][2]+dp[i+1][j-1][1][0]+dp[i+1][j-1][1][2]+dp[i+1][j-1][2][0]+dp[i+1][j-1][2][2])%MOD;
                    dp[i][j][1][0]+=(dp[i+1][j-1][0][0]+dp[i+1][j-1][0][1]+dp[i+1][j-1][0][2]+dp[i+1][j-1][2][0]+dp[i+1][j-1][2][1]+dp[i+1][j-1][2][2])%MOD;
                    dp[i][j][0][2]+=(dp[i+1][j-1][0][0]+dp[i+1][j-1][0][1]+dp[i+1][j-1][1][0]+dp[i+1][j-1][1][1]+dp[i+1][j-1][2][0]+dp[i+1][j-1][2][2])%MOD;
                    dp[i][j][2][0]+=(dp[i+1][j-1][0][0]+dp[i+1][j-1][0][1]+dp[i+1][j-1][0][2]+dp[i+1][j-1][1][0]+dp[i+1][j-1][1][1]+dp[i+1][j-1][1][2])%MOD;
                }
                else if (b[i]<j)
                {
                    for (int x=0;x<3;x++)
                        for (int y=0;y<3;y++)
                            for (int xx=0;xx<3;xx++)
                                for (int yy=0;yy<3;yy++)
                                    if (xx==0||yy==0||xx!=yy)
                                        dp[i][j][x][y]=(dp[i][j][x][y]+dp[i][b[i]][x][xx]*dp[b[i]+1][j][y][yy]%MOD)%MOD;
                }
            }

        LL ans=0;
        for (int i=0;i<3;i++)
            for (int j=0;j<3;j++)
                ans=(ans+dp[1][n][i][j])%MOD;
        printf("%lld\n", ans);
    }
    return 0;
}