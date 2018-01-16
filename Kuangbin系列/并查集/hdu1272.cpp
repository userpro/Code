#include <cstdio>
#include <cstring>

#define MAXN 100010
int F[MAXN];
bool V[MAXN];

int findd(int x)
{
    if (-1==F[x]) return x;
    return F[x]=findd(F[x]);
}

int main()
{
    int u,v,flag=1,edgenum=0,cnt=0;
    memset(F,-1,sizeof(F));
    memset(V,0,sizeof(V));
    while (1)
    {
        scanf("%d%d",&u,&v);
        if (u==-1&&v==-1) break;
        if (u==0&&v==0) 
        {
            memset(F,-1,sizeof(F));
            memset(V,0,sizeof(V));
            if (flag && cnt==0 && edgenum==0)
                printf("Yes\n");
            else if (flag && edgenum+1==cnt)
                printf("Yes\n");
            else
                printf("No\n");
            flag=1; edgenum=0; cnt=0;
            continue;
        }

        if (!V[u]) { cnt++; V[u]=1; }
        if (!V[v]) { cnt++; V[v]=1; }
        int a=findd(u),b=findd(v);
        if (a!=b)
            F[a]=b;
        else
            flag=0;
        edgenum++;
    }
    return 0;
}