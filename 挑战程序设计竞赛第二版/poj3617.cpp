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

int n;
char s[10010];
int main()
{
    while (scanf("%d",&n)!=EOF)
    {
        char c;
        for (int i=0;i<n;i++)
        {
            getchar();
            scanf("%c",&c);
            s[i]=c;
        }
        s[n]=0;

        int l=0,r=n-1;
        bool left=true;
        int cnt=0;
        while (l<=r)
        {
            for (int i=0;l+i<r;i++)
                if (s[l+i]>s[r-i])
                {
                    left=false;
                    break;
                }
                else if (s[l+i]<s[r-i])
                {
                    left=true;
                    break;
                }

            cnt++;
            if (left) printf("%c", s[l++]);
            else printf("%c", s[r--]);
            if (cnt>=80)
            {
                printf("\n");
                cnt=0;
            }
        }
        printf("\n");
    }
    return 0;
}