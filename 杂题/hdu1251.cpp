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

#define MAXN 400010

char buf[MAXN];
int sum[MAXN];
int tree[MAXN][26];
int tot;

void insert(int n)
{
    int root=0;
    for (int i=0;i<n;i++)
    {
        int id=buf[i]-'a';
        if (!tree[root][id])
            tree[root][id]=++tot;
        sum[tree[root][id]]++;
        root=tree[root][id];
    }
}

int find(int n)
{
    int root=0;
    for (int i=0;i<n;i++)
    {
        int id=buf[i]-'a';
        if (!tree[root][id])
            return 0;
        root=tree[root][id];
    }
    return sum[root];
}

int main()
{
    char c;
    int cnt=0;
    tot=0;
    CLR(sum,0);
    CLR(tree,0);
    bool flag=false;
    while(gets(buf))
    {
        int ln=strlen(buf);
        if(!flag)
        {
            if(ln) insert(ln);
            else flag=1;
        }
        else printf("%d\n",find(ln));
    }
    return 0;
}