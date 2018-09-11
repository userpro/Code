#include<iostream>
#include<cstring>
#include<cstdio>
#include<cstdlib>
const int maxn=1e6+5;
const int maxm=1e7+5;

int n;
bool visit[maxm];
int p1[maxn]; 
// p1的大小大概估计一下再开数组。大概是（x/lnx）
int pnum; // 素数个数

void getprime1(int n)
{
    memset(visit, false, sizeof(visit));
    int num = 0;
    for (int i = 2; i <= n; ++i)
    {
        if ( !visit[i] )  p1[num++] = i;
        for (int j = 0; j <= num && i * p1[j] <= n ;  j++)
        {
            visit[ i  *  p1[j] ]  =  true;
            if (i % p1[j] == 0) break; ///此处是重点，避免了很多的重复判断，比如i=9,现在素数是2,3,5,7,进入二重循环，visit[2*9]=1;visit[3*9]=1；这个时候9%3==0，要跳出。因为5*9可以用3*15来代替，如果这个时候计算了，i=15的时候又会被重复计算一次，所以这里大量避免了重复运算。
        }
    }
    pnum = num;
}

bool p2[maxn];
void getprime2(int n)
{
    memset(p2,1,sizeof(p2));
    p2[0]=p2[1]=0;
    for (int i=2;i<n;i++)
    {
        if (i>n/i) continue;
        for (int j=i+i;j<n;j+=i)
            p2[j]=0;
    }
}


int main()
{
    scanf("%d",&n);
    getprime2(n);
    for (int i = 0; i < n; ++i)
    {
        if (p2[i])
            printf("%d ", i);
    }
    return 0;
}