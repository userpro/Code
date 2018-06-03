// 先预处理

// mn[i][j]记录区间最小值，mx[i][j]记录区间最大值，则如果mx-mn+1和区间数字数量相同则该区间可以被归到一个小段

// f[i][j]记录(i,j)段最多可以被分成几个小段，sav[i]记录从i开始的上次的可行区间的右端点

// 然后就可以进行求解了

// 设要交换的区间为seg_a,seg_b。

// 一开始先求seg_a的左右端点即i和j，则seg_a必须满足可行，即f[i][j]!=0，同时必须满足，seg_a为最左边的段或者seg_a左边的段包括了(1,i-1)的数字

// 对于每个可行的seg_a，设k为seg_a中的最大值，则

// 1.如果k==n的话，那么seg_b是最右边的段

// 2.否则seg_b右边的段为seg(k+1,n),且必须包括(k+1,n)中的所有数

// 然后枚举seg_b的左端点t使seg_b合法，又必须满足mn[t][k]==i，才能保证seg_a和seg_b交换后整个数列从1~n递增
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
#include <cmath>
#include <map>
#include <string>
#include <iostream>
using namespace std;
#define INF (1<<29)
#define LL long long
#define CLR(a,b) memset(a,b,sizeof(a))

const int M=3044;
 
int n;
int s[M];
int f[M][M],mn[M][M],mx[M][M];
int sav[M],ans;
 
void init()
{
    memset(f,0,sizeof(f));
    int i,j,k;
    for(i=1;i<=n;i++)
    {
        sav[i]=i;
        f[i][i]=1;
        mn[i][i]=mx[i][i]=s[i];
    }
    for(i=1;i<=n;i++)
        for(j=i+1;j<=n;j++)
        {
            mx[i][j]=max(mx[i][j-1],s[j]);
            mn[i][j]=min(mn[i][j-1],s[j]);
        }
    for(i=2;i<=n;i++)
        for(j=1;j+i-1<=n;j++)
        {
            k=j+i-1;
            if(mx[j][k]-mn[j][k]+1!=k-j+1)
                f[j][k]=0;
            else
            {
                if(mn[j][k]<mn[j][sav[j]])
                    f[j][k]=1;
                else
                    f[j][k]=f[j][sav[j]]+f[sav[j]+1][k];
                sav[j]=k;
            }          
        }
}
 
void solve()
{
    ans=max(1,f[1][n]);
    int i,j,k,t,tmp;
    //swap (i,j) , (t,k)
    for(i=1;i<=n;i++)
        for(j=i;j<=n;j++)
            if(f[i][j] && (i==1 || (f[1][i-1] && mn[1][i-1]==1)))   //be sure the first seg is start from 1 or the seg(i,j)
            {
                k=mx[i][j];
                if(k==n || (f[k+1][n] && mx[k+1][n]==n))
                    for(t=j+1;t<=k;t++)
                        if(mn[t][k]==i && f[t][k])
                            ans=max(ans,f[1][i-1]+1/*seg[i][j]]*/+f[j+1][t-1]+1/*seg[t][k]*/+f[k+1][n]);
            }
}
 
int main()
{
    int T,i,j;
    cin>>T;
    while(T--)
    {
        scanf("%d",&n);
        for(i=1;i<=n;i++)
            scanf("%d",&s[i]);
        init();
        solve();
        cout<<ans<<endl;
    }
    return 0;
}