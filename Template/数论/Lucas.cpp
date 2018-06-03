long long F[100010];  
void init(long long p)  
{  
    F[0] = 1;  
    for(int i = 1;i <= p;i++)  
        F[i] = F[i-1]*i % (1000000007);  
}  
long long inv(long long a,long long m)  
{  
    if(a == 1)return 1;  
    return inv(m%a,m)*(m-m/a)%m;  
}  

// 求解C(n,m)%p, n和m是非负整数, p是质数.
long long Lucas(long long n,long long m,long long p)  
{  
    long long ans = 1;  
    while(n&&m)  
    {  
        long long a = n%p;  
        long long b = m%p;  
        if(a < b)return 0;  
        ans = ans*F[a]%p*inv(F[b]*F[a-b]%p,p)%p;  
        n /= p;  
        m /= p;  
    }  
    return ans;  
}  