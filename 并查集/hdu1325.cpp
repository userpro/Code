//一开始一直超时，因为不是-1 -1结束，而是负数结束
//和1272的不同：这个加了方向
//判断是不是树，只要节点等于边+1；同时每个节点的入度小于2；
#include <cstring>
#include <cstdio>

#define MAXN 100005
int f[MAXN];
int a,b,flag,edgenum,vertxnum;

void _init()
{
    flag=1;
    edgenum=vertxnum=0;
    memset(f,0,sizeof(f));
}

int main()
{
    int cnt=0;
    _init();
    while (1)
    {
        scanf("%d%d",&a,&b);
        if (a<0 || b<0) break;
        if (a==0 && b==0)
        {
            if ((flag && vertxnum==edgenum+1) || (flag&&edgenum==0&&vertxnum==0))
                printf("Case %d is a tree.\n", ++cnt);
            else
                printf("Case %d is not a tree.\n", ++cnt);
            _init();
            continue;
        }

        if (f[b]-1==1) flag=0; // 环
        if (f[a]==0) vertxnum++;
        if (f[b]==0) vertxnum++;
        f[a]=100; f[b]=2; // f[a]=1 叶子结点状态和初始化状态之外
        edgenum++;
    }
    return 0;
}