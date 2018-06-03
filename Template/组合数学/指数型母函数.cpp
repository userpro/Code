// 有n种物品, 并且知道每种物品的数量。要求从中选出m件物品的排列数。例如有两种物品A,B, 并且数量都是1, 从中选2件物品, 则排列有"AB","BA"两种。 

// Input
// 每组输入数据有两行, 第一行是二个数n,m(1<=m,n<=10), 表示物品数, 第二行有n个数, 分别表示这n件物品的数量。

// Output
// 对应每组数据输出排列数。(任何运算不会超出2^31的范围)

// Sample Input
// 2 2 1 1

// Sample Output
// 2
#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

const int N = 100;
double c1[N], c2[N],a[N];
int val[N];
void Factorial()
{
    a[0]=1;
    a[1]=1;
    for(int i = 2; i <=20; i++)
    {
        a[i]=a[i-1]*i;
    }
}
int main()
{
    int n, m, i, j, k;
    Factorial();
    while(~scanf("%d%d", &n, &m))
    {
        for(i = 0; i < n; ++ i)
        {
            scanf("%d", &val[i]);
        }
        memset(c1, 0, sizeof(c1));
        memset(c2, 0, sizeof(c2));

        for(i = 0; i <= val[0]; ++i)
        {
            c1[i] = 1.0/a[i];
        }
        for(i = 1; i < n; i++)
        {
            for(j = 0; j <= m; ++j)
                for(k = 0; k + j <= m && k <= val[i]; ++k)
                    c2[j + k] += c1[j]/a[k];
                
            for(j = 0; j <= m; ++j)
            {
                c1[j] = c2[j];
                c2[j] = 0;
            }
        }
        printf("%.0lf\n", c1[m]*a[m]);
    }
    return 0;
}