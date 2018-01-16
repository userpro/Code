#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;
#define MAXN 110
struct Edge
{
    int u,v,c;
    Edge(int _u,int _v,int _c):u(_u),v(_v),c(_c) {}
};
int T,N,M;
int F[MAXN];
vector<Edge> E;
bool used[MAXN*MAXN];

int findd(int x)
{
    if (-1==F[x]) return x;
    return F[x]=findd(F[x]);
}

bool cmp(Edge e1,Edge e2)
{
    return e1.c<e2.c;
}

int main()
{
    int u,v,c;
    scanf("%d",&T);
    while (T--)
    {
        E.clear();
        scanf("%d%d",&N,&M);
        for (int i = 0; i < M; ++i)
        {
            scanf("%d%d%d",&u,&v,&c);
            E.push_back(Edge(u,v,c));
        }
        sort(E.begin(), E.end(), cmp);

        int ans=0;
        memset(F,-1,sizeof(F));
        vector<int> eg;
        for (int i = 0; i < E.size(); ++i)
        {
            int a=findd(E[i].u),b=findd(E[i].v);
            if (a!=b)
            {
                F[a]=b;
                ans+=E[i].c;
                eg.push_back(i);
            }
        }

        int flag=1,tans=0,cnt=0;
        memset(used,0,sizeof(used));
        for (int i = 0; i < eg.size(); ++i)
        {
            memset(F,-1,sizeof(F));
            tans=0; cnt=0;
            used[eg[i]]=1;
            for (int j = 0; j < E.size(); ++j)
            {
                if (used[j]) continue;
                int a=findd(E[j].u),b=findd(E[j].v);
                if (a!=b)
                {
                    F[a]=b;
                    tans+=E[j].c;
                    cnt++;
                }
            }
            if (tans==ans&&cnt==N-1)
            {
                flag=0;
                break;
            }
            used[eg[i]]=0;
        }
        if (flag)
            printf("%d\n", ans);
        else
            printf("Not Unique!\n");
    }
    return 0;
}