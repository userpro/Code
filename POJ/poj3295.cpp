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

#define Get(t) (t=S.top(), S.pop())
char s[110];
int idx[256];
bool num[6]; // p q r s t
stack<bool> S;
int main()
{
    idx['p']=0, idx['q']=1, idx['r']=2, idx['s']=3, idx['t']=4;
    while (scanf("%s",s)!=EOF && s[0]!='0')
    {
        while (!S.empty()) S.pop();
        int len=strlen(s);
        bool x=false,w=false;
        bool flag=true;
        for (int i=0;i<1<<5;i++)
        {
            CLR(num,0);
            for (int j=0;j<5;j++)
            {
                if (i&(1<<j))
                    num[j]=1;
            }

            for (int j=len-1;j>=0;j--)
            {
                if (s[j]=='N')
                {
                    Get(x);
                    S.push(!x);
                } else if (s[j]=='K')
                {
                    Get(x); Get(w);
                    S.push(w && x);
                } else if (s[j]=='A')
                {
                    Get(x); Get(w);
                    S.push(w || x);
                } else if (s[j]=='C')
                {
                    Get(x); Get(w);
                    if (w && !x)
                        S.push(0);
                    else
                        S.push(1);
                } else if (s[j]=='E')
                {
                    Get(x); Get(w);
                    if ((w && x) || (!w && !x))
                        S.push(1);
                    else
                        S.push(0);
                } else
                {
                    S.push(num[idx[s[j]]]);
                }
            }

            bool tmp=S.top();
            while (!S.empty()) S.pop();
            if (!tmp)
            {
                flag=false;
                break;
            }
        }

        if (flag)
            printf("tautology\n");
        else
            printf("not\n");
    }
    return 0;
}