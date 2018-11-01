// https://blog.csdn.net/wu_tongtong/article/details/77731671
// 设f[i][0]表示长度为i且结尾是高低的序列数 
// f[i][1]表示长度为i且开头是低高的序列数

// 假设我们现在要求长度为i的序列数,  
// 枚举第i个的插入位置j

// ans[i]+=f[j][0]*f[i-j-1][1]*C(i-1,j)
// C(i-1,j)是组合数（从i-1中取出j个）

// 那么现在的问题就变成了f[i][0/1]怎么求 
// 我们把一个序列抽象成01串, 1表示山峰, 0表示山谷

// i个高度排好后无非两种情况 
// 开始为低高或开始为高低, 那么排列的逆序也满足条件,  
// 也就是说结尾为高低的方法数和开始为低高的方法数相同 
// 而对于人数一定的情况, 开始为低高的人数和开始为高低的人数相等

// 证明： 
// 当n为偶数时：假设波峰开始的序列为1010.那么把它倒置一下就变成了0101了 
// 也就是说每一个1打头的对应着一个0打头的

// 当n为奇数时：假设波峰开始的序列为10101. 
// 假设第一个数大于最后一个数, 那我们把序列最后一个数放到最前 序列就变成01010. 
// 如果第一个数小于最后一个数把第一个数放到最后就行了

// 所以每一个1打头的对应着一个0打头的

// 所以f[i][0]=f[i][1]=ans[i]/2;

// 这样就可以完成递推了

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
#define LL long long
int P,cnt,nn;
LL dp[21][2],ans[21];
LL CC[21];

void _init()
{
    CC[0]=1;
    for (int i=1;i<=21;i++)
        CC[i]=i*CC[i-1];
}

LL C(int n,int m)
{
    if (n==m) return 1;
    if (m>n) return 0;
    return CC[n]/(CC[n-m]*CC[m]);
}

int main()
{
    int n;
    _init();
    while (scanf("%d",&P)!=EOF)
    {
        dp[0][0]=dp[0][1]=1;
        dp[1][0]=dp[1][1]=1;
        dp[2][0]=dp[2][1]=1;
        ans[0]=0;ans[1]=1;ans[2]=2;
        n=2;
        while (P--)
        {
            scanf("%d%d",&cnt,&nn);
            if (nn>n)
            {
                for (int i=n+1;i<=nn;i++)
                {
                    for (int j=0;j<i;j++)
                        ans[i]+=dp[j][0]*dp[i-j-1][1]*C(i-1,j);
                    dp[i][0]=dp[i][1]=ans[i]/2;
                }
                n=nn;
            }
            printf("%d %lld\n", cnt, ans[nn]);
        }
    }
    return 0;
}