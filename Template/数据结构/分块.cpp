#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn=1e6+10;
LL num[maxn],add[maxn],sum[maxn];
int pos[maxn],L[maxn],R[maxn];
int n,m;
char op[5];

void change(int l,int r,LL val) {
    int p1=pos[l],p2=pos[r];
    if (p1==p2) {
        for (int i=l;i<=r;i++) num[i]+=val;
        sum[p1]+=val*(r-l+1);
    } else {
        for (int i=p1+1;i<=p2-1;i++) add[i]+=val;
        for (int i=l;i<=R[p1];i++) num[i]+=val;
        sum[p1]+=val*(R[p1]-l+1);
        for (int i=L[p2];i<=r;i++) num[i]+=val;
        sum[p2]+=val*(r-L[p2]+1);
    }
}

LL query(int l,int r) {
    LL res=0;
    int p1=pos[l],p2=pos[r];
    if (p1==p2) {
        for (int i=l;i<=r;i++) res+=num[i];
        res+=add[p1]*(r-l+1);
    } else {
        for (int i=p1+1;i<=p2-1;i++) res+=sum[i]+add[i]*(R[i]-L[i]+1);
        for (int i=l;i<=R[p1];i++) res+=num[i];
        res+=add[p1]*(R[p1]-l+1);
        for (int i=L[p2];i<=r;i++) res+=num[i];
        res+=add[p2]*(r-L[p2]+1);
    }
    return res;
}

int main() {
    scanf("%d%d",&n,&m);
    for (int i=1;i<=n;i++) scanf("%lld",&num[i]);
    int t=sqrt(n);
    for (int i=1;i<=t;i++) {
        L[i]=(i-1)*t+1;
        R[i]=i*t;
    }
    if (R[t]<n) t++, L[t]=R[t-1]+1, R[t]=n;
    for (int i=1;i<=t;i++)
        for (int j=L[i];j<=R[i];j++) {
            sum[i]+=num[j];
            pos[j]=i;
        }

    int u,v,w;
    for (int i=1;i<=m;i++) {
        scanf("%s%d%d",op,&u,&v);
        if (op[0]=='Q') printf("%lld\n", query(u,v));
        else if (op[0]=='C') scanf("%d",&w),change(u,v,w);
    }
    return 0;
}

