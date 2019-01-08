// codeforce 992D 暴力剪枝思维
#include <cstdio>
#include <cstring>
#include <climits>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn=2e5+10;
int n,k;
LL a[maxn],nx[maxn];
inline bool overflow(LL a,LL b) { return a>LLONG_MAX/b; } // 检查溢出
int main() {
    while (~scanf("%d%d",&n,&k)) {
        for (int i=1;i<=n;i++) scanf("%I64d",&a[i]);
        int x=n+1;
        for (int i=n;i>=1;i--) {
            nx[i]=x;
            if (a[i]!=1) x=i;
        }
        int ans=0;
        for (int i=1;i<=n;i++) {
            int cnt=1;
            LL p=1,s=0;
            for (int j=i;cnt<=64 && j<=n;j=nx[j],cnt++) {
                if (overflow(p,a[j])) break;
                p*=a[j];
                s+=a[j];
                LL add=nx[j]-j-1;
                if (p%k==0) { // 利用了连续1的单调性
                    if (p>=s*k && p<=(s+add)*k) ans++;
                }
                s+=add;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
