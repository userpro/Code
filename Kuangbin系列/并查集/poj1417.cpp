#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;
#define MAXN 610
vector<int> b[MAXN][2];
bool used[MAXN];
int N, P1, P2;
int F[MAXN], val[MAXN];
int pre[MAXN][MAXN], dp[MAXN][MAXN];
int a[MAXN][2];

int findd(int x)
{
    if (-1==F[x])
        return x;
    int t = findd(F[x]);
    val[x] = (val[x] + val[F[x]]+2)%2;
    return F[x] = t;
}

void unionn(int x, int y, int c)
{
    int a=findd(x), b=findd(y);
    if (a!=b)
    {
        F[a]=b;
        val[a]=(val[y]-val[x]+c+2)%2;
    }
}

int main()
{
    while (~scanf("%d%d%d", &N, &P1, &P2))
    {
        if (N==0 && P1==0 && P2==0) break;
        memset(val,0,sizeof(val));
        memset(F,-1,sizeof(F));
        int x1, y1, temp;
        char a1[10];
        for (int i = 1; i <= N; ++i)
        {
            scanf("%d%d%s", &x1, &y1, a1);
            if (a1[0]=='y') temp=0;
            else temp=1;
            unionn(x1,y1,temp);
        }

        for (int i = 0; i < MAXN; ++i)
        {
            b[i][0].clear();
            b[i][1].clear();
            a[i][0]=0;
            a[i][1]=0;
        }

        memset(used,0,sizeof(used));
        int cnt=1;
        for (int i = 1; i <= P1+P2; ++i)
        {
            if (!used[i])
            {
                int t = findd(i);
                for (int j = i; j <= P1+P2; ++j)
                {
                    if (findd(j)==t)
                    {
                        used[j]=1;
                        a[cnt][val[j]]++;
                        b[cnt][val[j]].push_back(j);
                    }
                }
                cnt++;
            }
        }

        memset(dp,0,sizeof(dp));
        dp[0][0]=1;
        for (int i = 1; i < cnt; ++i)
        {
            for (int j = P1; j>=0; --j)
            {
                if (j-a[i][0]>=0 && dp[i-1][j-a[i][0]])
                {
                    dp[i][j]+=dp[i-1][j-a[i][0]];
                    pre[i][j]=j-a[i][0];
                }
                if (j-a[i][1]>=0 && dp[i-1][j-a[i][1]])
                {
                    dp[i][j]+=dp[i-1][j-a[i][1]];
                    pre[i][j]=j-a[i][1];
                }
            }
        }
        if (dp[cnt-1][P1]!=1)
        {
            printf("no\n");
        } else {
            vector<int> ans;
            ans.clear();
            int t = P1;
            for (int i = cnt-1; i>=1; --i)
            {
                int temp=t-pre[i][t];
                if (temp==a[i][0])
                {
                    for (int j = 0; j < a[i][0]; ++j)
                        ans.push_back(b[i][0][j]);
                } else {
                    for (int j = 0; j < a[i][1]; ++j)
                        ans.push_back(b[i][1][j]);
                }
                t=pre[i][t];
            }
            sort(ans.begin(), ans.end());
            for (int i=0;i<ans.size();++i)
                printf("%d\n", ans[i]);
            printf("end\n");
        }
    }
    return 0;
}