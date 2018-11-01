#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
#define MAXN 60
int b[MAXN],a[MAXN];
int n;

void _init()
{
    memset(b,0,sizeof(b));
    memset(a,0,sizeof(a));
    a[1]=1;a[2]=1;a[3]=1;
    b[1]=2;b[2]=3;b[3]=4;
    for (int i=4;i<=MAXN;i++)
    {
        a[i]=a[i-3]+a[i-1];
        b[i]=b[i-1]+a[i];
    }
}

int main()
{
    _init();
    while (scanf("%d",&n)!=EOF && n)
    {
        printf("%d\n", b[n]-a[n]);
    }
    return 0;
}