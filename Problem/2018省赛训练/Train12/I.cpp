// 输的人死掉!!
// 定义dp[i][j][k]三维分别表示三种人剩余的个数, 数组记录的值是当前这个状态出现的概率.
// 那么dp[r][s][p]=1.0, 这就是动态规划的初始状态.
// 设dp[i+1][j][k]转移到dp[i][j][k]的概率是p,定义sum=i*j+j*k+k*i,那么
// pi=(i+1)*j/sum
// 那么我们就得到如下的转移方程:
// dp[i][j][k]=dp[i+1][j][k]*pi+dp[i][j+1][k]*pj+dp[i][j][k+1]*pk
// 最终我们统计每种导致各种类型的人必胜的局势的概率, 输出结果即可. 
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <stack>
#include <vector>
#include <cmath>
#include <map>
#include <string>
#include <iostream>
using namespace std;
#define INF (1<<29)
#define LL long long
#define CLR(a,b) memset(a,b,sizeof(a))

#define MAX 110
int r,s,p;
double dp[MAX][MAX][MAX];
int main()
{
    while (scanf("%d%d%d",&r,&s,&p)!=EOF)
    {
        CLR(dp,0);
        dp[r][s][p]=1;
        for (int i=r;i>0;i--)
            for (int j=s;j>0;j--)
                for (int k=p;k>0;k--)
                {
                    double sum=i*j+j*k+k*i;
                    dp[i-1][j][k]+=dp[i][j][k]*(i*k/sum);
                    dp[i][j-1][k]+=dp[i][j][k]*(j*i/sum);
                    dp[i][j][k-1]+=dp[i][j][k]*(k*j/sum);
                }

        double ans1=0,ans2=0,ans3=0;
        for (int i=0;i<MAX;i++)
            for (int j=0;j<MAX;j++)
            {
                ans1+=dp[i][j][0];
                ans2+=dp[0][i][j];
                ans3+=dp[i][0][j];
            }

        printf("%.12f %.12f %.12f\n", ans1,ans2,ans3);
    }
    return 0;
}