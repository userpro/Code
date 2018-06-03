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

int R,n;
int num[1010];
int main()
{
    while (scanf("%d%d",&R,&n)!=EOF && (R!=-1 || n!=-1))
    {
        for (int i=0;i<n;i++)
            scanf("%d",&num[i]);
        sort(num,num+n);
        int ans=0;
        for (int i=0;i<n;i++)
        {
            int tmp=num[i]+R;
            int j=i+1;
            while (j<n&&num[j]<=tmp)
                j++;
            j--;
            int tmp2=num[j]+R;
            while (j<n&&num[j]<=tmp2)
                j++;
            j--;
            i=j;
            ans++;
        }
        printf("%d\n", ans);
    }
    return 0;
}