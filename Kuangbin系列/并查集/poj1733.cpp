#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;
#define HASHN 10007
#define MAXN 10010
int F[MAXN];
int val[MAXN];
int N, M;

struct HASHMAP
{
    int head[HASHN];
    int next[MAXN];
    int size;
    int state[MAXN];
    void init()
    {
        size=0;
        memset(head,-1,sizeof(head));
    }
    int push(int st)
    {
        int i,j=st%HASHN;
        for (i=head[j]; i!=-1; i=next[i])
            if (state[i]==st)
                return i;
        state[size]=st;
        next[size]=head[j];
        head[j]=size++;
        return size-1;
    }
}hm;

int findd(int x)
{
    if (-1==F[x]) return x;
    int t=findd(F[x]);
    val[x]^=val[F[x]];
    return F[x]=t;
}

int main()
{
    while (scanf("%d%d", &N, &M)==2)
    {
        hm.init();
        memset(F,-1,sizeof(F));
        memset(val,0,sizeof(val));
        int u,v,tmp,ans=M;
        char str[20];
        for (int i = 0; i < M; ++i)
        {
            scanf("%d%d%s", &u, &v, str);
            if (ans<M) continue;
            if (u>v) swap(u,v);
            u=hm.push(u-1);
            v=hm.push(v);

            if (str[0]=='e') tmp=0;
            else tmp=1;

            int a=findd(u);
            int b=findd(v);
            if (a==b)
            {
                if ((val[u]^val[v])!=tmp)
                    ans=i;
            } else {
                F[b]=a;
                val[b]=val[u]^val[v]^tmp;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}