// codeforces846C-神奇暴力
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
const LL inf=1e17;
const int maxn=5010;
int n;
LL a[maxn],b[maxn];
inline LL cal(int l,int r) { return b[r-1]-b[l-1]; }
int main() {
    while (~scanf("%d",&n)) {
        b[0]=0;
        for (int i=1;i<=n;i++) scanf("%I64d",&a[i]),b[i]=b[i-1]+a[i];
        LL ans=-inf;
        int x1,x2,x3;
        for (int i=0;i<=n;i++) {
            LL k=b[i];
            int pos=i;
            for (int j=i;j<=n;j++) {
                if (k>b[j]) {
                    k=b[j]; pos=j;
                }
                LL cnt=cal(1,i+1)-cal(i+1,pos+1)+cal(pos+1,j+1)-cal(j+1,n+1);
                if (cnt>=ans) {
                    ans=cnt;
                    x1=i, x2=pos, x3=j;
                }
            }
        }
        printf("%d %d %d\n", x1,x2,x3);
    }
    return 0;
}