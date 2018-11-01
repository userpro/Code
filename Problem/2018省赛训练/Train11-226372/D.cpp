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

#define MAX 300050
struct node
{
    int s,e;
    int index;
    friend bool operator < (const node& n1,const node& n2)
    {
        if (n1.s==n2.s)
            return n1.e<n2.e;
        return n1.s<n2.s;
    }
    friend bool operator > (const node& n1,const node& n2)
    {
        if (n1.s==n2.s)
            return n1.e>n2.e;
        return n1.s>n2.s;
    }
} nodes[MAX];
int N;
bool flag;

bool _cmp(const node& n1,const node& n2)
{
    if (n1.s==n2.s)
        return n1.e>n2.e;
    return n1.s<n2.s;
}

inline bool isin(const node& n1,const node& n2)
{
    return (n1.s>=n2.s && n1.e<=n2.e) || (n2.s>=n1.s && n2.e<=n1.e);
}

int main()
{
    while (scanf("%d",&N)!=EOF)
    {
        flag=false;
        for (int i=0;i<N;i++)
        {
            scanf("%d %d",&nodes[i].s,&nodes[i].e);
            nodes[i].index=i+1;
        }
        sort(nodes,nodes+N,_cmp);
        for (int i=1;i<N;i++)
        {
            if (isin(nodes[i],nodes[i-1]))
            {
                printf("%d %d\n", nodes[i].index, nodes[i-1].index);
                flag=true;
                break;
            }
        }
        if (!flag)
            printf("-1 -1\n");
    }
    return 0;
}