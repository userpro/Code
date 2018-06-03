#define LL long long

LL qpow(LL x,LL y)
{
    LL res = 1;
    while(y){
        if(y&1) res = x * res % mod;
        x = x * x % mod;
        y >>= 1;
    }
    return res;
}