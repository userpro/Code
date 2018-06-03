// https://www.cnblogs.com/chendl111/p/5671470.html
#define LL long long

// 扩展欧几里得算法求逆元
// gcd(a, b) > 1时逆不存在
int ex_gcd_inverse(int a, int b, int &x, int &y) {
    int ret, tmp;
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    ret = ex_gcd_inverse(b, a % b, x, y);
    tmp = x;
    x = y;
    y = tmp - a / b * y;
    return ret;
}

// 由于费马小定理，a^(p-1)=1(mod p)-->1/a=a^(p-2)(mod p),
// 故a的逆元为a^p-2.
// 注意这个方法要求模的数必须为质数，传入a和mod-2即可得到结果
LL quick_inverse(LL n, LL p, LL mod) {
    LL ret = 1,exponent = p;
    for (LL i = exponent; i; i >>= 1, n = n * n % mod) {
        if (i & 1) {
            ret = ret * n % mod;
        }
    } 
    return ret;
}

// 递推 1~n
int inv[N];
void get_inverse(int n, int p) {
    inv[1] = 1;
    for (int i = 2; i <= n; ++i) {
        inv[i] = (p - p / i) * inv[p % i] % p;
    }
}

// 反向递推 n!~1!
int invf[N], factor[N];
void get_factorial_inverse(int n, int p) {
    factor[0] = 1;
    for (int i = 1; i <= n; ++i) {
        factor[i] = i * factor[i - 1] % p;
    }
    invf[n] = quick_inverse(factor[n], p);
    for (int i = n-1; i >= 0; --i) {
        invf[i] = invf[i + 1] * (i + 1) % p;
    }
}