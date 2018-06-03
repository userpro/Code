#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <stack>
#include <vector>
#include <cmath>
#include <map>
#include <string>
#include <iostream>
using namespace std;
#define INF (1<<29)
#define LL long long
#define CLR(a,b) memset(a,b,sizeof(a))

#define MAX 1010
struct Node
{
    double x,y;
    double st,ed;
}nodes[MAX];
bool vis[MAX];
int n,d;

bool _cmp(const Node &n1,const Node &n2)
{
    return n1.ed<n2.ed;
}

int main()
{
    int cas=1;
    double len=0,max_d;
    while (scanf("%d%d",&n,&d)!=EOF && (n || d))
    {
        max_d=0;
        for (int i=0;i<n;i++)
        {
            scanf("%lf%lf",&nodes[i].x,&nodes[i].y);
            len=sqrt(1.0*d*d-nodes[i].y*nodes[i].y);
            max_d=max(1.0*max_d,nodes[i].y);
            nodes[i].st=nodes[i].x-len;
            nodes[i].ed=nodes[i].x+len;
        }
        sort(nodes,nodes+n,_cmp);
        printf("Case %d: ", cas++);
        if (max_d>d || d<0)
        {
            printf("-1\n");
            continue;
        }
        CLR(vis,0);        
        int ans=0;
        for (int i=0;i<n;i++)
        {
            if (!vis[i])
            {
                vis[i]=true;
                for (int j=0;j<n;j++)
                    if (!vis[j]&&nodes[j].st<=nodes[i].ed)
                        vis[j]=true;
                ans++;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}