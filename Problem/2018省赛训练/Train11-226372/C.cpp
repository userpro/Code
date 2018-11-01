// 先对n个数排序, 那么最后的结果ans一定满足0<=ans<an-a1
// 第二如何判断ans就是我们需要求的值能, 我们用二分进行逼近. l=0, r=an-a1, mid=（l+r）/2；
// 二分如何逼近呢, 如何判断我们要求的答案ans是在[l,mid]还是在[mid,r]部分呢? 
// 很明显是原数组两个数相减的绝对值<mid个数, 和>mid的个数进行比较. （绝对值的个数<mid,ans在[mid,r]区间, 否则在[l,mid]区间内
// 如何判段两数绝对值<mid的个数呢? 
// 如何求一个数减去a[0]的值小于mid的个数, 我们找到一个a[i]>=a[0]+mid时最小的一个i, 那么数组[0,i)值减去a[0],都小于mid, 这样枚举i就可以求得两数相减差值小于mid的个数. 
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

#define MAX 1000010
int num[MAX];
int N,M;

bool calc(int mid)
{
    int sum=0;
    for (int i=0;i<N;i++)
        sum+=((lower_bound(num+i,num+N,num[i]+mid+1)-(num+i))-1);
    return sum>=M;
}

int main()
{
    while (scanf("%d",&N)!=EOF)
    {
        for (int i=0;i<N;i++)
            scanf("%d",&num[i]);
        M=((N*(N-1))/2+1)/2;
        sort(num,num+N);
        int l=0, r=num[N-1]-num[0];
        while (r-l>1)
        {
            int mid=(l+r)>>1;
            if (calc(mid))
                r=mid;
            else
                l=mid;
        }
        printf("%d\n", r);
    }
    return 0;
}