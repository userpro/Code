#include<iostream>
#include<cstring>
#include<cstdio>
#include<cstdlib>
const int maxn=1e6+5;
const int maxm=1e7+5;
int n;
/* Eratosthenes 筛法 */
bool visit[maxm];
int p1[maxn]; // p1的大小大概估计一下再开数组。大概是（x/lnx） 
int pnum; // 素数个数
void getprime1(int x) {
    memset(visit, false, sizeof(visit));
    int num = 0;
    for (int i = 2; i <= x; ++i) {
        if ( !visit[i] )  p1[num++] = i;
        for (int j = 0; j <= num && i * p1[j] <= x ; j++) {
            visit[ i  *  p1[j] ]  =  true;
            if (i % p1[j] == 0) break;
        }
    }
    pnum = num;
}
// 最常用!!!!!!!!
bool p2[maxn];
void getprime2(int x) {
    memset(p2,1,sizeof(p2));
    p2[0]=p2[1]=0;
    for (int i=2;i<x;i++) {
        if (!p2[i] || i>x/i) continue;
        for (int j=i+i;j<x;j+=i)
            p2[j]=0;
    }
}
/* 线性筛法 */
int v[maxn],p3[maxn];
int getprime3(int n) {
    memset(v,0,sizeof(v)); // 最小质因子
    int m=0;    // 质数数量
    for (int i=2;i<=n;i++) {
        if (v[i]==0) {
            v[i]=i; p3[++m]=i;
        }
        for (int j=1;j<=m;j++) { // 给当前数i乘上一个质因子
            if (p3[j]>v[i] || p3[j]>n/i) break; // i有比p3[j]更小的质因子,或者超出n的范围
            v[i*p3[j]]=p3[j];
        }
    }
    return m;
}
int main() {
    scanf("%d",&n);
    getprime2(n);
    for (int i = 0; i < n; ++i) {
        if (p2[i]) printf("%d ", i);
    }
    printf("\n");
    
    int num=getprime3(n);
    for (int i=1;i<=num;i++) printf("%d ", p3[i]);
    printf("\n");
    return 0;
}