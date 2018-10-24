#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn=1e5+10;
const int maxm=1e6+10;
int n,m;
int a[maxn],f[maxn][25],logN[maxn];

int main() {
    scanf("%d%d",&n,&m);
    for (int i=1;i<=n;i++) scanf("%d",&a[i]);

    logN[0]=-1;
    for (int i=1;i<=n;i++) logN[i]=logN[i>>1]+1,f[i][0]=a[i];
    for (int j=1;j<25;j++)
        for (int i=1;i+(1<<j)-1<=n;i++)
            f[i][j]=max(f[i][j-1],f[i+(1<<(j-1))][j-1]);

    int l,r;
    for (int i=1;i<=m;i++) {
        scanf("%d%d",&l,&r);
        int s=logN[r-l+1];
        printf("%d\n", max(f[l][s],f[r-(1<<s)+1][s]));
    }    
    return 0;
}
