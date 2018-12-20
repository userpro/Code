// JLOI2014-聪明的燕姿-约数和暴力枚举
/*
    质因数分解得质数因子Pi及其幂次ai, 穷举Pi及其对应的ai进行搜索
    1.若当前数可表示成一个并未搜索过的质数与1的和,则之前搜索过的数与这个质数的乘积符合题意
    2.对于每一个未被搜索过且平方小于当前数的质数,则枚举所有可能符合题意的ai进行递归搜索
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn=1e5+10;
bool isp[maxn];
int tot,p[maxn];
void getPrime() {
    memset(isp,0,sizeof(isp));
    tot=0;
    for (int i=2;i<maxn;i++) {
        if (!isp[i]) p[++tot]=i;
        for (int j=1;j<=tot && i*p[j]<maxn;j++) {
            isp[i*p[j]]=1;
            if (i%p[j]==0) break;
        }
    }
}

bool isPrime(int x) {
    if (x<maxn) return !isp[x];
    for (long long i=2;i*i<=x;i++)
        if (x%i==0) return false;
    return true;
}

int s,cnt;
int ans[maxn];
void dfs(int last,int sum,int now) {
    if (now==1) { ans[++cnt]=sum; return; }
    if (now-1>=p[last] && isPrime(now-1))
        ans[++cnt]=sum*(now-1);
    for (int i=last;i<=tot && p[i]*p[i]<=now;i++) {
        int tmp=p[i];
        for (int j=p[i]+1;j<=now;tmp*=p[i],j+=tmp)
            if (now%j==0)
                dfs(i+1,sum*tmp,now/j);
    }
}

int main() {
    getPrime();
    while (~scanf("%d",&s)) {
        cnt=0;
        dfs(1,1,s);
        sort(ans+1,ans+1+cnt);
        printf("%d\n", cnt);
        for (int i=1;i<=cnt;i++) printf("%d ", ans[i]);
        if (cnt) printf("\n");
    }
    return 0;
}
