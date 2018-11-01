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
#define eps 0.0001
#define CLR(a,b) memset(a,b,sizeof(a))

LL T,N;
int main(int argc, char const *argv[])
{
    scanf("%lld",&T);
    for (int jj=1;jj<=T;jj++)
    {
        int ans=0;
        scanf("%lld",&N);
        int i;
        for(i=0; (((LL)1)<<i)<=N; i++);
        printf("Case %d: %d\n", jj,i);
    }
    return 0;
}