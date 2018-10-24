#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn=4096+12;
int n,m;
int ap[maxn][maxn];

void update(int x,int y,int z) {
    for (int i=x;i<=n;i+=i&-i)
        for (int j=y;j<=m;j+=j&-j)
            ap[i][j]+=z;
}

int query(int x,int y) {
    int sum=0;
    for (int i=x;i;i-=i&-i)
        for (int j=y;j;j-=j&-j)
            sum+=ap[i][j];
    return sum;
}

int main() {
    memset(ap,0,sizeof(ap));
    scanf("%d%d",&n,&m);
    int t1,a,b,c,d;
    while (scanf("%d",&t1)!=EOF) {
        scanf("%d%d%d",&a,&b,&c);
        if (t1==1) {
            update(a,b,c);
        } else if (t1==2) {
            scanf("%d",&d);
            if (a>c) swap(a,c);
            if (b>d) swap(b,d);
            printf("%d\n", query(c,d)-query(a-1,d)-query(c,b-1)+query(a-1,b-1));
        }
    }
    return 0;
}
