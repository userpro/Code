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

int T,N,M;
char buf[5];
int mp[16];
bool isAC[16];
struct Node
{
    int h,m;
} mpp[16];
int main()
{
    while (scanf("%d",&T)!=EOF)
    {
        int hour,minus,timu;
        while (T--)
        {
            CLR(mp,0);
            CLR(isAC,0);
            CLR(mpp,0);
            scanf("%d%d",&N,&M);
            for (int i=0;i<M;i++)
            {
                scanf("%d %d:%d %s",&timu,&hour,&minus,buf);
                timu-=1000;
                if (buf[0]=='A' && !isAC[timu])
                {
                    isAC[timu]=1;
                    mp[timu]+=hour*60+minus;
                }
                else if (buf[0]!='A' && !isAC[timu])
                {
                    mp[timu]+=20;
                }
                mpp[timu].h=hour, mpp[timu].m=minus;
            }

            int ans=0,num=0;
            for (int i=0;i<16;i++)
            {
                if (isAC[i])
                {
                    num++;
                    ans+=mp[i];
                }
            }
            printf("%d %d\n", num,ans);
        }
    }
    return 0;
}