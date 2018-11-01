/*
枚举子串 kmp
*/

#include <cstdio>
#include <cstring>

#define MAXM 20
#define MAXN 100
char s[MAXM][MAXN], ss[MAXN], ans[MAXN];
int _next[MAXN];
bool B[MAXM];
int n,m,mm,flag;

void kmp_pre(char s[], int m)
{
    int i,j;
    j=_next[0]=-1;
    i=0;
    while (i<m)
    {
        while (j!=-1 && s[i]!=s[j]) j=_next[j];
        _next[++i]=++j;
    }
}

bool kmp_match(char s1[], int n, char s2[], int m)
{
    int i,j;
    i=j=0;
    while (i<n)
    {
        while (j!=-1 && s1[i]!=s2[j]) j=_next[j];
        ++i; ++j;
        if (j>=m)
            return true;
    }
    return false;
}

int main()
{
    scanf("%d",&n);
    while (n--)
    {
        scanf("%d",&m);
        mm=m;
        memset(_next,0,sizeof(_next));
        memset(ans,0,sizeof(ans));
        int len=60;
        flag=0;
        while (m--) scanf("%s",s[m]);
        // 枚举子串长度 至少为3
        for (int i = len; i >= 3; --i)
        {
            // 子串开始下标
            for (int j = 0; j <= len-i; ++j)
            {
                memset(B,0,sizeof(B));
                strncpy(ss,s[0]+j,i);
                ss[i]=0;
                kmp_pre(ss,i);
                // 其他主串
                for (int k = 1; k < mm; ++k)
                {
                    if (kmp_match(s[k],len,ss,i))
                        B[k]=1;
                }

                int bflag=1;
                for (int k = 1; k < mm; ++k)
                {
                    if (!B[k])
                    {
                        bflag=0;
                        break;
                    }
                }
                if (bflag) 
                {
                    flag=1;
                    if (strlen(ans)<i)
                        strcpy(ans,ss);
                    else if (strcmp(ans,ss)>0)
                        strcpy(ans,ss);
                }
            }

            if (flag) break;
        }
        if (flag)
            printf("%s\n", ans);
        else
            printf("no significant commonalities\n");
    }
    return 0;
}