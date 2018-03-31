/*
    已知s1,s2
    求最大 (s1的前缀) == (s2的后缀)
    思路:
        s1 s2连起来 求next[len]
*/

#include <cstdio>
#include <cstring>

#define MAXN 50010
char s1[2*MAXN],s2[2*MAXN];
int _next[2*MAXN];
int ans;

void kmp_pre(char s[],int m)
{
    int i,j;
    j=_next[0]=-1;
    i=0;
    while (i<m)
    {
        while (j!=-1&&s[i]!=s[j]) j=_next[j];
        _next[++i]=++j;
    }
}

int main()
{
    while (scanf("%s%s",s1,s2) != EOF)
    {
        memset(_next,0,sizeof(_next));
        int len1 = strlen(s1), len2 = strlen(s2);
        strcat(s1,s2);
        int _len = len1+len2;
        kmp_pre(s1, _len);
        ans = _next[_len];
        while (ans>len1 || ans>len2) ans=_next[ans];
        if (ans==0)
            printf("0\n");
        else {
            s1[ans]=0;
            printf("%s %d\n", s1, ans);
        }
    }
    return 0;
}