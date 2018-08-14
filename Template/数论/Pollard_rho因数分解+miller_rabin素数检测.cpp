#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long LL;

// (a*b) % m
LL mod_mult(LL a,LL b,LL m)
{
    LL res=0;
    LL exp=a%m;
    while (b)
    {
        if (b&1)
        {
            res+=exp;
            if (res>m) res-=m;
        }
        exp<<=1;
        if (exp>m) exp-=m;
        b>>=1;
    }
    return res;
}

// (a^b) % m
LL mod_exp(LL a,LL b,LL m)
{
    LL res=1;
    LL exp=a%m;
    while (b)
    {
        if (b&1) res=mod_mult(res,exp,m);
        exp=mod_mult(exp,exp,m);
        b>>=1;
    }
    return res;
}


// Method:    miller_rabin
// Qualifier: Rabin-Miller强伪素数测试
// Parameter: LL n 待检测的数
// Parameter: LL times 
// Returns:   bool 是否是素数
bool miller_rabin(LL n,LL times)
{
    if (n<2) return false;
    if (n==2) return true;
    if (!(n&1)) return false;
    LL q=n-1;
    int k=0;
    while (q%2==0)
    {
        k++;
        q>>=1;
    }
    // n - 1 = 2^k * q (q是奇素数)
    // n是素数的话，一定满足下面条件
    // (i)  a^q ≡ 1 (mod n)
    // (ii) a^q, a^2q,..., a^(k-1)q 中的某一个对n求模为-1
    //
    // 所以当不满足(i)(ii)中的任何一个的时候, 就有3/4的概率是合成数
    //
    for (int i=0;i<times;i++)
    {
        LL a=rand()%(n-1)+1; // 从1,..,n-1随机挑一个数
        LL x=mod_exp(a,q,n);
        // 检查条件(i)
        if (x==1) continue;
        // 检查条件(ii)
        bool found=false;
        for (int j=0;j<k;j++)
        {
            if (x==n-1)
            {
                found=true;
                break;
            }
            x=mod_mult(x,x,n);
        }
        if (found) continue;
        return false;
    }
    return true;
}

LL gcd(LL a,LL b)
{
    return b==0?a:gcd(b,a%b);
}

// Method:     Pollard_rho 
// Qualifier:  Pollard 因数分解算法
// Parameter:  LL n 要分解的数
// Parameter   LL a 随机数(一般取1)
// Returns:    n的一个因子
// 第一种 floyd判环
LL pollard_rho1(LL n,int a)
{
    LL x=2,y=2,d=1;
    while (d==1)
    {
        x=mod_mult(x,x,n)+a;
        y=mod_mult(y,y,n)+a;
        y=mod_mult(y,y,n)+a;
        d=gcd((x-y>=0?x-y:y-x), n);
    }
    if (d==n) return pollard_rho(n,a+1);
    return d;
}

// 第二种 brent判环（更高效）
LL pollard_rho2(LL n, int a){
    LL x = 2, y = 2, d = 1, k = 0, i = 1;
    while(d == 1){
        ++k;
        x = mod_mult(x, x, n) + a;
        d = gcd(x >= y ? x - y : y - x, n);
        if(k == i){
            y = x;
            i <<= 1;
        }
    }
    if(d == n) return pollard_rho2(n, a + 1);
    return d;
}