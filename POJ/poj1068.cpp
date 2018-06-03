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

int t,n;
char s[200];
int num[200];
int main()
{
    while (scanf("%d",&t)!=EOF)
    {
        while (t--)
        {
            CLR(s,0);
            scanf("%d",&n);
            int idx=0;
            for (int i=0;i<n;i++)
            {
                scanf("%d",&num[i]);
                int cnt=num[i];
                idx=0;
                while (cnt>0)
                {
                    if (s[idx]=='(')
                        cnt--;
                    else if (!s[idx])
                        s[idx]='(', cnt--;
                    idx++;
                }
                s[num[i]+i]=')';
            }
            int len=n+num[n-1];
            s[len]=0;

            for (int i=0;i<len;i++)
                if (s[i]==')')
                {
                    int ans=0;
                    for (int j=i;j>=0;j--)
                        if (s[j]=='(')
                        {
                            s[j]=0;
                            break;
                        } else if (s[j]==')')
                            ans++;
                    printf("%d ", ans);
                }
            printf("\n");
        }
    }
    return 0;
}