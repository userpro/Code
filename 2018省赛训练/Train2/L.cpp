#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;
int t,n,a;

int main()
{
    scanf("%d",&t);
    while (t--)
    {
        scanf("%d",&n);
        int ans=n;
        while (n--)
        {
            scanf("%d",&a);
            ans+=a;
        }
        printf("%d\n", ans);
    }
    return 0; 
}