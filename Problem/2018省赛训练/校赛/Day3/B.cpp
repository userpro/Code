#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;
const int MAXN = 1e5 + 10;
const int MOD = 1e9 + 7;
struct word
{
    int pos;///26个字母
    int time[MAXN];///各个字母在n个字符串中出现的位置和数量，数组下标是位置，对应的值是在该位置出现的次数
}quan[27];

bool cmp(word &a,word &b)///按从小到大的顺序排序结构体
{
    for(int i=MAXN-1; i>1; i--)///从高位往下比较各个字母出现的次数，高位出现的越多，最后乘的值越大
    {
        if(a.time[i]!=b.time[i])
        {
            return a.time[i]<b.time[i];
        }
    }
    return a.time[1]<b.time[1];
}

int main()
{
    int n,N=0;
    char str[MAXN];
    while(scanf("%d",&n)!=EOF)
    {
        int flag[27]={0};///来标记各个字母是否可以对应0
        for(int i=0; i<26; i++)
        {
            quan[i].pos=i;///将26字母按0到25存入结构体
            for(int j=0; j<MAXN; j++)
            {
                quan[i].time[j]=0;///将各个位置出现的次数赋值为0
            }
        }
        while(n--)
        {
            scanf("%s",str);
            int len;
            len=strlen(str);
            if(len>1)flag[str[0]-'a']=1;///如果字符串长度大于1，则第一位字母不能对应0，标记为1
            for(int i=0; i<len; i++)
            {
                int y;
                y=len-i;
                quan[str[i]-'a'].time[y]++;///将i位置的字母对应的数组位置加1
                while(quan[str[i]-'a'].time[y]==26)///当此位置数值大于1就需要往后一位进1
                {
                    quan[str[i]-'a'].time[y]=0;
                    y++;
                    quan[str[i]-'a'].time[y]++;///进1之后还要考虑进1之后是否会让下一位满26，所以用while判断下一位是否需要进1
                }
            }
        }
        sort(quan,quan+26,cmp);///将结构体按各个字母出现的位置及数量从小到大排序
        int op,m=1;
        long long sum=0,sumi=0,me;///不用long long会WA
        for(int i=0; i<26; i++)
        {
            if(flag[quan[i].pos]==0)
            {
                op=i;///op存放出现的位置及数量最小又可以对应0的字母在结构体数组中对应的下标
                break;
            }
        }
        for(int i=0; i<26; i++)
        {
            sumi=0;
            if(i==op)
            {
                me=0;///将i位对应0
            }
            else
            {
                me=m;///将各位一一对应1到25
                m++;
            }
            for(int j=MAXN-1;  j>0; j--)///将26进制转为10进制，第n位置需要乘以26的(n-1)次方，所以倒着计算，每次乘以1个26即可
            {
                sumi=(sumi*26)%MOD;///不断取余
                sumi=(sumi+(long long)quan[i].time[j]*me)%MOD;///将每位都乘以字母对应的数值并取余
            }
            sum=(sum+sumi)%MOD;///将每个字母计算得出的值加入总和
        }
        N++;
        printf("Case #%d: %lld\n",N,sum);///输出格式不能忘，因为这个坑错了好几次
    }
}