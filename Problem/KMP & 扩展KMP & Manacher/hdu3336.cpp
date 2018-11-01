/*
当_next[j]+1 != _next[j+1] 即不符合递推规律时
这时候就是当前子串最长的公共前后缀了
前缀个数就是字符串的长度
*/
#include <cstdio>
#include <cstring>

#define MAXN 200005
char s[MAXN];
int _next[MAXN];
int T,n,ans;

void kmp_pre(char x[],int m)
{
    int i,j;
    j=_next[0]=-1;
    i=0;
    while (i<m)
    {
        while (j!=-1 && x[i]!=x[j]) j=_next[j];
        _next[++i]=++j;
    }
}

int main()
{
    scanf("%d",&T);
    while (T--)
    {
        memset(_next,0,sizeof(_next));
        scanf("%d%s",&n,s);
        int l=strlen(s);
        kmp_pre(s,l);
        ans=l+_next[l];
        for (int i=0; i<l; i++)
            if (_next[i]>0 && _next[i]+1!=_next[i+1])
                ans+=_next[i];

        printf("%d\n", ans%10007); 
    }
    return 0;
}