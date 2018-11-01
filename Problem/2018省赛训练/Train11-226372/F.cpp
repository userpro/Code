/*
唯一分解定理的运用
x=b^P 求P的最大值(-2^31<=x<=2^31)
x=p1^s1*p2^s2*……*pk^sk
P=gcd(s1,s2,……,sk)
if x为质数 than P=1
if(x<0) P只能为奇数，while(n%2==0) P/=2
*/
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

const int maxn=1e6+5;
const int maxm=1e7+5;
bool visit[maxm];
int prime1[maxn];
int pnum;

void getprime1(int n)
{
    memset(visit, false, sizeof(visit));
    int num = 0;
    for (int i = 2; i <= n; ++i)
    {
        if ( !visit[i] )  prime1[num++] = i;
        for (int j = 1; j <= num && i * prime1[j] <= n ;  j++)
        {
            visit[ i  *  prime1[j] ]  =  true;
            if (i % prime1[j] == 0) break;
        }
    }
    pnum=num;
}

int gcd(int a,int b)
{
    return a%b==0?b:gcd(b,a%b);
}

int solve(LL n)
{
    bool flag=false;
    if (n<0)
    {
        n=-n;
        flag=true;
    }
    int ans=0;
    for (int i = 0; i<pnum&&prime1[i]*prime1[i] <= n; ++i)
    {
        if (n%prime1[i]==0)
        {
            int pow=0;
            while (n%prime1[i]==0)
            {
                n/=prime1[i];
                pow++;
            }

            if (ans==0)
                ans=pow;
            else
                ans=gcd(ans,pow);
        }
    }
    if (n>1) ans=1;
    if (flag)
    {
        while (ans%2==0) ans/=2;
    }
    return ans;
}

LL x;
int N;
int main()
{
    getprime1(maxm);
    int cnt=1;
    while (scanf("%d",&N)!=EOF)
    {
        while (N--)
        {
            scanf("%lld",&x);
            printf("Case %d: %d\n", cnt++,solve(x));
        }
    }
    return 0;
}