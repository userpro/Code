// SG计算方法
// 1.可选步数为1~m的连续整数，直接取模即可，SG(x) = x % (m+1);
// 2.可选步数为任意步，SG(x) = x;
// 3.可选步数为一系列不连续的数，用getSG()计算
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
#define MAXN 1010
int m,n,p;
// f[]: 可以取走的石子个数  
// sg[]: 0~n的SG函数值  
// mex[]: mex{} 
int sg[MAXN];
int f[MAXN]; // f[]需要从小到大排序
int mex[MAXN];

void fb()
{
    f[0]=f[1]=1;
    for (int i=2;i<=20;i++)
        f[i]=f[i-1]+f[i-2];
}

void getSG(int n)
{
    memset(sg,0,sizeof(sg));
    for (int i=1;i<=n;i++)
    {
        memset(mex,0,sizeof(mex));
        for (int j=1;f[j]<=i;j++)
            mex[sg[i-f[j]]]=1;
        for (int j=0;j<=n;j++)
        {
            if (mex[j]==0)
            {
                sg[i]=j;
                break;
            }
        }
    }
}

int main()
{
    fb();
    getSG(MAXN);
    while (scanf("%d%d%d",&m,&n,&p) && (m||n||p))
    {
        if (sg[m]^sg[n]^sg[p])
            printf("Fibo\n");
        else
            printf("Nacci\n");
    }
    return 0;
}