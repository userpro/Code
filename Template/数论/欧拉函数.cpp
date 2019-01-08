// 欧拉函数被定义为小于或等于n的数中与n互质的个数
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn=3e6+5;

int get_phi1(int x) {
    int ans=x;
    for (int i = 2; i*i <= x; ++i) {
        if (x%i==0) {
            ans=ans/i * (i-1);
            while (x%i==0) x/=i;
        }
    }
    if (x>1) ans=ans/x*(x-1);
    return ans;
}

long long phi[maxn];
void get_phi2(int x) {
    memset(phi,0,sizeof(phi));
    phi[1]=1;
    for (int i = 2; i <= x; ++i)
        if (!phi[i]) {
            for (int j = i; j <= x; j+=i) {
                if (!phi[j]) phi[j]=j;
                phi[j]=phi[j]/i * (i-1);
            }
        }
}

int main() {
    printf("%d\n", get_phi1(7));
    get_phi2(1000);
    for (int i = 0; i < 20; ++i)
        printf("%lld ", phi[i]);
    printf("\n");
    return 0;
}