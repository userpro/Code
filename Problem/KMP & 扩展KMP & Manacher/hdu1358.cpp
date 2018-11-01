/*
思路是先构造出 next[] 数组 
下标为 i 定义一个变量 j = i - next[i] 就是next数组下标和下标对应值的差 
如果这个差能整除下标 i 即 i%j==0 ,
则说明下标i之前的字符串（周期性字符串长度为 i）一定可以由一个前缀周期性的表示出来 
这个前缀的长度为刚才求得的那个差 即 j 则这个前缀出现的次数为 i/j. 所以最后输出i和i/j即可.
*/
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn=1e6+10;
int n;
int nx[maxn];
char a[maxn];

void kmp_pre(int n)
{
    int i,j;
    j=nx[0]=-1;
    i=0;
    while (i<n)
    {
        while (j!=-1 && a[i]!=a[j]) j=nx[j];
        nx[++i]=++j;
    }
}

int main()
{
    int num=0;
    while (scanf("%d",&n)==1 && n)
    {
        scanf("%s",a);
        printf("Test case #%d\n", ++num);
        kmp_pre(n);
        int x;
        for (int i = 0; i <= n; ++i)
        {
            if (nx[i]!=0 && nx[i]!=-1)
            {
                x=i-nx[i];
                if (i%x==0)
                {
                    printf("%d %d\n", i,i/x);
                }
            }
        }
        printf("\n");
    }
    return 0;
}