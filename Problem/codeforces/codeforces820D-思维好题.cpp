// codeforces820D-思维好题
// 参考题解 https://www.cnblogs.com/TnT2333333/p/7091392.html
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn=1e6+10;
int a[maxn],pre[maxn];
int n;
int main() {
    while (~scanf("%d",&n)) {
        memset(pre,0,sizeof(pre));
        LL sum=0;
        for (int i=1;i<=n;i++) {
            scanf("%d",&a[i]);
            sum+=abs(a[i]-i);
            if (a[i]-i<=0) pre[0]++;
            else pre[a[i]-i]++;
        }
        LL cnt=pre[0];
        LL mn=sum,ans=0;
        for (int i=1;i<n;i++) {
            int pos=n-i+1;
            if (a[pos]-n<=0) cnt--;
            if (a[pos]-pos<=0) pre[0]--;
            else pre[a[pos]-pos]--;
            pre[min(a[pos]+i-1,n)]++;
            sum+=cnt;
            sum-=(n-cnt-1); // n-cnt-1个a[i]-i>0贡献减少的 
            // 从最后一个移到第一个额外处理
            sum-=abs(a[pos]-n);
            sum+=abs(a[pos]-1);
            cnt+=pre[i];
            if (sum<mn) {
                mn=sum;
                ans=i;
            }
        }
        printf("%I64d %I64d\n", mn,ans);
    }
    return 0;
}
