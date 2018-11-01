#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;
#define MAXN 210
int N,M;
int sub_a[MAXN], plus_a[MAXN];
int dp[21][801];
vector<int> path[21][801];

int main()
{
    int cnt=1;
    while (scanf("%d%d",&N,&M)==2&&(N||M))
    {
        memset(dp,-1,sizeof(dp));
        int d,p;
        for (int i = 0; i < M; ++i)
            for (int j = 0; j < 801; ++j)
                path[i][j].clear();

        for (int i = 0; i < N; ++i)
        {
            scanf("%d%d",&d,&p);
            sub_a[i]=d-p;
            plus_a[i]=d+p;
        }

        int fix=20*M;
        dp[0][fix]=0;
        for (int i = 0; i < N; ++i) // 枚举每一个
        {
            for (int j = M-1; j >= 0; --j) // 背包逆推
            {
                for (int k = 0; k < fix*2; ++k)
                {
                    if (dp[j][k] >= 0)
                    {
                        if (dp[j+1][k+sub_a[i]]<=dp[j][k]+plus_a[i])
                        {
                            dp[j+1][k+sub_a[i]]=dp[j][k]+plus_a[i];
                            path[j+1][k+sub_a[i]]=path[j][k];
                            path[j+1][k+sub_a[i]].push_back(i);
                        }
                    }
                }
            }
        }

        int inx=0;
        for (int i = 0; dp[M][fix+i]==-1 && dp[M][fix-i]==-1; ++i,++inx)
            ;
        int temp=dp[M][fix+inx]>dp[M][fix-inx]?inx:-inx;
        int sumP=(dp[M][fix+temp]+temp)/2;
        int sumD=(dp[M][fix+temp]-temp)/2;
        printf("Jury #%d\n", cnt++);
        printf("Best jury has value %d for prosecution and value %d for defence:\n", sumP, sumD);
        for (int i = 0; i < M; ++i)
            printf(" %d", path[M][fix+temp][i]+1);
        printf("\n\n");
    }
    return 0;
}