long long C(int n,int m,int mod) {
    if (m*2>n) m=n-m;
    long long ret=1;
    for (int i=1;i<=m;i++) {
        ret*=(n-i+1)%mod;
        while (ret%i!=0) ret+=mod;
        ret/=i;
        ret%=mod;
    }
    return ret;
}