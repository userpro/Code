inline LL sum(LL a,LL b) { // 递归二分求等比数列
    if (b==0) return 1;
    if (b&1) return ((1+qpow(a,b/2+1))%mod*sum(a,b/2))%mod;
    return ((1+qpow(a,b/2+1))%mod*sum(a,b/2-1)%mod+qpow(a,b/2))%mod;
}
// 或者可以使用逆元直接计算等比数列求和公式