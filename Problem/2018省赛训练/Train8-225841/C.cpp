// hdu6048

// 结论一：相邻的两个数字块交换位置改变序列逆序对数量的奇偶性。

// 结论二：白块左右移动不会改变逆序对的数量。

// 结论三：白块上下移动最终不会改变逆序对数量的奇偶性。因为白块每向上或向下移动一位相当于对应的数字块向下或向上移动m−1次，而白块一定是从右下角最终回到右下角，移动偶数次，数字块也移动偶数次，不会改变逆序对数量的奇偶性。

// 结论四：任何规模的拼图最终一定会成为只有右下角2×2的方格不确定的情况，枚举可能的6种情况，发现逆序对数量奇偶性相同的情况可以互达。

// 结论五：由以上结论可知，任何局面一定可以转化为右下角2×2方格不确定的情况而逆序对数量奇偶性不变，而最后有序情况的逆序对数量为0，因此只需判断最开始情况逆序对的数量，若为偶数就可以复原，反之不能复原。

// 求逆序对时，可以累加每个数字后面比它小的数字的个数，即累加每个数字对逆序对的贡献。设当前轮剩余的数字数量为tot，则这一轮可以取到的数字个数为(tot−1)/p+1，其中除第一个数不贡献逆序对数之外，其余的num=(tot−1)/p个数每个数贡献的逆序对数量构成首项为p−1，公差为p−1的等差数列，求和化简后的公式为num∗(num+1)/2∗(p−1)。
#include <iostream>  
#include <algorithm>  
#include <cstdio>  
#include <cstring>  
#include <cstdlib>  
#include <cmath>  
#include <ctime>  
#include <vector>  
#include <queue>  
#include <stack>  
#include <deque>  
#include <string>  
#include <map>  
#include <set>  
#include <list>  
using namespace std;  
#define INF 0x3f3f3f3f  
#define LL long long  
#define fi first  
#define se second  
#define mem(a,b) memset((a),(b),sizeof(a))  
  
int N,M,P;  
  
int main()  
{  
    int T_T;  
    scanf("%d",&T_T);  
    while(T_T--)  
    {  
        scanf("%d%d%d",&N,&M,&P);  
        int num=N*M-1, cnt=0;//剩下的数字数，逆序对数  
        while(num>P)  
        {  
            int n=(num-1)/P+1;//这一轮拿出的数字  
            cnt+=n*(n-1)/2*(P-1);//逆序对数  
            num-=n;  
        }  
        puts(cnt&1?"NO":"YES");  
    }  
      
    return 0;  
}  