#include <cstdio>
#include <cstring>

using namespace std;
#define max(a,b) (a>b?a:b)
#define MAXN 510
#define MAXM 2010
int N,M;
int F[MAXN], val[MAXN], F1[MAXM], F2[MAXM];
char OP[MAXM];

int findd(int x)
{
    if (-1==F[x]) return x;
    int t=findd(F[x]);
    val[x]=(val[x]+val[F[x]])%3;
    return F[x]=t;
}

int main()
{
    while (scanf("%d%d",&N,&M)==2)
    {
        memset(F1,0,sizeof(F1));
        memset(F2,0,sizeof(F2));
        memset(OP,0,sizeof(OP));

        for (int i = 0; i < M; ++i)
            scanf("%d%c%d",&F1[i],&OP[i],&F2[i]);

        char c;
        int idx=0,cnt=0,flag=1,inx=0,temp;
        for (int i = 0; i < N; ++i)
        {
            flag=1;
            memset(F,-1,sizeof(F));
            memset(val,0,sizeof(val));
            for (int j = 0; j < M; ++j)
            {
                if (F1[j]==i||F2[j]==i) continue;
                c = OP[j];
                if (c=='=') temp=0;
                else if (c=='<') temp=1;
                else if (c=='>') temp=2;

                int u=F1[j],v=F2[j];
                int a=findd(u), b=findd(v);
                if (a!=b)
                {
                    F[a]=b;
                    val[a]=(temp-val[u]+val[v]+3)%3;
                } else if ((val[u]-val[v]+3)%3!=temp)
                {
                    flag=0;
                    inx=max(inx,j+1);
                    break;
                }
            }
            if (flag)
            {
                idx=i;
                cnt++;
            }
        }

        if (cnt>1)
            printf("Can not determine\n");
        else if (cnt==1)
            printf("Player %d can be determined to be the judge after %d lines\n", idx,inx);
        else if (cnt<1)
            printf("Impossible\n");
    }
    return 0;
}