// codeforces946E-神奇构造
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn=2e5+10;
int t;
int cnt[maxn][10];
char s[maxn];
void solve(int len) {
    for (int i=len;i>=1;i--) {
        for (int j=s[i]-'0'-1;j>=0;j--) {
            if (i==1&&j==0) continue;
            int odd=0;
            for (int k=0;k<10;k++) odd+=cnt[i-1][k]^(j==k);
            if (odd<=len-i) {
                for (int k=1;k<i;k++) putchar(s[k]);
                putchar(j+'0');
                for (int k=i+1;k<=len-odd;k++) putchar('9');
                for (int k=9;k>=0;k--) if (cnt[i-1][k]^(j==k)) putchar(k+'0');
                putchar('\n');
                return;
            }
        }
    }
    for (int i=1;i<=len-2;i++) putchar('9');
    putchar('\n');
    return;
}
int main() {
    while (~scanf("%d",&t)) {
        while (t--) {
            // memset(cnt,0,sizeof(cnt));
            scanf("%s",s+1);
            int len=strlen(s+1);
            for (int i=1;i<=len;i++) {
                int tmp=s[i]-'0';
                for (int j=0;j<10;j++) cnt[i][j]=cnt[i-1][j]^(j==tmp);
            }
            solve(len);
        }
    }
    return 0;
}