// hdu1438-钥匙计数之一-状态压缩dp
#include <cstdio>
#include <cstring>
long long dp[32][(1<<4)+5][4][2];
///第几个槽，前面槽的状态（包含几个不同的深度），最后一个槽的深度，是否已经符合要求
int num[17];
int main()
{
    memset(num,0,sizeof(num));
    memset(dp,0,sizeof(dp));
    for(int i=0; i<16; i++)//2^4次方种状态;
        for(int j=0; j<4; j++)//深度个数4个;
            if(i&(1<<j))num[i]++;///找不同的状态不同深度数。从而找出合法的至少有3个深度不同
    for(int i=0; i<4; i++) ///初始化1只有1,2,3,4四个状态。
        dp[1][1<<i][i][0]=1;
    for(int i=2; i<32; i++) ///槽数
        for(int j=0; j<16; j++) ///不同深度状态
            for(int k=0; k<4; k++) ///前一个槽的最后一个深度
            {
                for(int l=0; l<4; l++) ///当前槽的最后一个的深度
                {
                    int cur=j|(1<<l);
                    dp[i][cur][l][1]+=dp[i-1][j][k][1];
                    if(k-l==3||k-l==-3) dp[i][cur][l][1]+=dp[i-1][j][k][0];
                    else dp[i][cur][l][0]+=dp[i-1][j][k][0];
                }
            }
    for(int i=2; i<32; i++) {
        long long ans=0;
        for(int j=0; j<16; j++)
            if(num[j]>=3)//挑出符合条件的超过2个不同深度
                for(int k=0; k<4; k++)
                    ans+=dp[i][j][k][1];
        printf("N%d: %lld\n", i,ans);
    }
}
