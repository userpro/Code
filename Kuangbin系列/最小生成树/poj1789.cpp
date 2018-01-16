#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;
#define MAXN 2010
struct Edge
{
    int u,v,c;
    Edge(int _u,int _v,int _c):u(_u),v(_v),c(_c) {}
};
vector<Edge> E;
int N;
int F[MAXN];
char str[MAXN][10];

int dis(char s1[10],char s2[10])
{
    int l1=strlen(s1),l2=strlen(s2);
    int cnt=0,
        l=l1>l2?l1:l2;
    for (int i = 0; i < l1; ++i)
        if (s1[i]!=s2[i])
            cnt++;
    return cnt;
}

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
    while (scanf("%d",&N)==1 && N)
    {
        E.clear();
        memset(F,-1,sizeof(F));
        memset(str,0,sizeof(str));
        for (int i = 0; i < N; ++i)
        {
            scanf("%s",str[i]);
            for (int j = 0; j < i; ++j)
                E.push_back(Edge(i,j,dis(str[i],str[j])));
        }
        sort(E.begin(), E.end(), cmp);

        int ans=0;
        for (int i = 0; i < E.size(); ++i)
        {
            int a=findd(E[i].u),b=findd(E[i].v);
            if (a!=b)
            {
                F[a]=b;
                ans+=E[i].c;
            }
        }
        printf("The highest possible quality is 1/%d.\n", ans);
    }
    return 0;
}