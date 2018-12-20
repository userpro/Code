#include <cstdio>
#include <cstring>
const int maxel=1e5+10; // 位数
const int base=1e8;
int sav1[maxel],sav2[maxel];
void Print(int a[]) { // 打印高精度
    printf("%d", a[a[0]]);
    for (int i=a[0]-1;i>0;i--) for (int j=base/10;j>0;j/=10) 
        printf("%d",a[i]/j%10);
    printf("\n");
}
void Init(int a[],char s[],int len) { // 字符串转高精度
    for (int i=0;i<len;i++) {
        int j=(len-i+7)/8;
        a[j]=a[j]*10+s[i]-'0';
    }
    a[0]=(len+7)/8;
}
void Sub(int a[],int b[]) { // 高精度减法
    for (int i=1;i<=a[0];i++) {
        a[i]-=b[i];
        if (a[i]<0) { a[i+1]--; a[i]+=base; }
    }
    while (a[a[0]]==0 && a[0]>0) a[0]--;
}
void Add(int a[],int b[]) { // 高精度加法
    a[0]=(a[0]>b[0]?a[0]:b[0])+1;
    for (int i=1;i<=a[0];i++) {
        a[i]+=b[i], a[i+1]+=a[i]/base, a[i]%=base;
    }
    while (a[a[0]]==0 && a[0]>0) a[0]--;
}
int Comp(int a[],int b[]) { // 高精度比较
    if (a[0]>b[1]) return 1;
    if (a[0]<b[0]) return -1;
    for (int i=a[0];i>=1;i--)
        if (a[i]>b[i]) return 1;
        else if (a[i]<b[i]) return -1;
    return 0;
}
void DivHigh(int a[],int b[]) { // 高精度除以高精度
    sav1[0]=a[0]-b[0]+1;
    for(int i=sav1[0];i;i--) {
        memset(sav2,0,sizeof sav2);
        for(int j=1;j<=b[0];j++) sav2[j+i-1]=b[j];
        sav2[0]=b[0]+i-1;
        while(Comp(a,sav2)>=0) sav1[i]++,Sub(a,sav2);
    }
    while(!sav1[sav1[0]] && sav1[0]>1) sav1[0]--;
    for (int i=0;i<=sav1[0];i++) a[i]=sav1[i];
    return;
}
void DivLow(int a[],int k) { // 高精度除低精度
    int t=0;
    for (int i=a[0];i>=1;i--) {
        t=t*base+a[i];
        a[i]=t/k;
        t%=k;
    }
    while (a[a[0]]==0 & a[0]>0) a[0]--;
}
void MulHigh(int a[],int b[]) { // 高精度乘高精度
    memset(sav1,0,sizeof(sav1));
    for (int i=1;i<=a[0];i++)
        for (int j=1;j<=b[0];j++) {
            sav1[i+j-1]+=a[i]*b[j];
            sav1[i+j]+=sav1[i+j-1]/base;
            sav1[i+j-1]%=base;
        }
    sav1[0]=a[0]+b[0];
    while (sav1[sav1[0]]==0 && sav1[0]>0) sav1[0]--;
    for (int i=0;i<=sav1[0];i++) a[i]=sav1[i];
}
void MulLow(int a[],int k) { // 高精度乘单精度
    for (int i=1;i<=a[0];i++) a[i]*=k;
    for (int i=1;i<=a[0];i++) a[i+1]+=a[i]/base, a[i]%=base;
    while (a[a[0]+1]>0) {
        a[0]++; a[a[0]+1]=a[a[0]]/base; a[a[0]]%=base;
    }
}
int gcdT;
void Gcd(int a[],int b[],int t) { // 高精度gcd
    int tmp=Comp(a,b);
    if (tmp==0) { gcdT=t; return; }
    if (tmp<0) { Gcd(b,a,t); return; }
    int ta,tb;
    if (a[1]%2==0) { DivLow(a,2); ta=1; }
    else ta=0;
    if (b[1]%2==0) { DivLow(b,2); tb=1; }
    else tb=0;
    if (ta && tb) Gcd(a,b,t+1);
    else if (!ta && !tb) { Sub(a,b); Gcd(a,b,t); }
    else Gcd(a,b,t);
}
char s1[maxel],s2[maxel];
int a[maxel]={0},b[maxel]={0},f[maxel]={0};
void solve(int a[],int b[]) { // 求解高精度gcd
    Gcd(a,b,0);
    if (gcdT==0) Print(a);
    else {
        f[0]=f[1]=1;
        for (int i=1;i<=gcdT;i++) MulLow(f,2);
        MulHigh(f,a);
        Print(f);
    }
}
int main() {
    scanf("%s%s",s1,s2);
    int len1=strlen(s1),len2=strlen(s2);
    Init(a,s1,len1); Init(b,s2,len2);
    solve(a,b); // 求解高精度gcd
    // Add(a,b);
    // Print(a);
    return 0;
}
