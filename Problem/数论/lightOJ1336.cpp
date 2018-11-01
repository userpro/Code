// 整数分解 n = p1^a1 * p2^a2 * ... * pn^an
// 数x的因子和 f(x)= （1+p1+p1^2+p1^3+...+p1^a1）*(1+p2+p2^2+...+p2^a2)*...*(1+pn+pn^2+...+pn^an);

// 因为偶数乘偶数还是偶数, 奇数乘奇数还是奇数, 奇数乘偶数是偶数, 所有必须让每个括号内都是奇数, 然后减去约数和为奇数的个数就是答案了.

// 1.当x有素因子2的时候, 2所对应的括号内的和肯定是一个奇数, 因为偶数加1一定是奇数.

// 2.除了2以外, 所有的素数都是奇数, 要使x得其他素因子对应的括号内的和为奇数, 就必须保证x有偶数个该素因子, 即ai必须为偶数.

// 3.满足上面两个条件的数, 就是一个平方数, 也就是说约数和为奇数的数x, 它必定是一个平方数, 当然这个数x乘上2也是满足2*x的约数和为奇数的.

// 所以只要减去用n减去sqrt(n)和sqrt(n/2)就是答案了.也可以找n以内的平方数的个数, 以及2*平方数不超过n的数的所有个数和, 用n减完之后就是答案.
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>

using namespace std;
#define LL long long
LL n,t;

int main()
{
    while (scanf("%lld",&t)!=EOF)
    {
        for (int ii=1;ii<=t;ii++)
        {
            scanf("%lld",&n);
            LL ans=n;
            ans-=(int)sqrt(n);
            ans-=(int)sqrt(n/2);
            printf("Case %d: %lld\n", ii, ans);
        }
    }
    return 0;
}