#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn=1e6+100;
char x[maxn],y[maxn];
int nx[maxn];

// x 模版串  y 主串
void kmp_pre(char x[],int m,int nx[]) {
    int i,j;
    j=nx[0]=-1;
    i=0;
    while (i<m) {
        while (j!=-1 && x[i]!=x[j]) j=nx[j];
        nx[++i]=++j;
    }
}

int kmp_count(char x[],int m,char y[],int n) {
    kmp_pre(x,m,nx);
    int i,j,ans;
    i=j=ans=0;
    while (i<n) {
        while (j!=-1 && y[i]!=x[j])  j=nx[j];
        ++i, ++j;

        if (j>=m) {
            ans++;
            j=nx[j];
        }
    }
    return ans;
}

int main() {
    scanf("%s%s",y,x);
    int n=strlen(y),m=strlen(x);
    kmp_pre(x,m,nx);
    printf("%d\n", kmp_count(x,m,y,n));
    return 0;
}