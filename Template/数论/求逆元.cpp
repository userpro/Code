// https://www.cnblogs.com/chendl111/p/5671470.html
typedef long long LL;

// 扩展欧几里得算法求逆元
// gcd(a, b) > 1时逆不存在
LL ex_gcd_inverse(LL a, LL b, LL &x, LL &y) {
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
LL qpow(LL a, LL p, LL mod) {
    LL res=1;
    while (p) {
        if (p&1) res=res*a%mod;
        a=a*a%mod;
        p>>=1;
    }
    return res;
}

// 递推 1~n
LL inv[N];
void get_inverse(LL n, LL p) {
    inv[1] = 1;
    for (int i = 2; i <= n; ++i) {
        inv[i] = (p - p / i) * inv[p % i] % p;
    }
}

// 反向递推 n!~1!
LL invf[N], factor[N];
void get_factorial_inverse(LL n, LL p) {
    factor[0] = 1;
    for (int i = 1; i <= n; ++i) {
        factor[i] = i * factor[i - 1] % p;
    }
    invf[n] = qpow(factor[n], p);
    for (int i = n-1; i >= 0; --i) {
        invf[i] = invf[i + 1] * (i + 1) % p;
    }
}