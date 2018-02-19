#include<iostream>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#define maxn 10000000
bool visit[maxn+1000000];
int prime1[maxn],n; ///prime1的大小大概估计一下再开数组。大概是（x/lnx）

void getprime1()
{
    memset(visit, false, sizeof(visit));
    int num = 0;
    for (int i = 2; i <= n; ++i)
    {
        if ( !visit[i] )  prime1[++num] = i;
        for (int j = 1; j <= num && i * prime1[j] <= n ;  j++)
        {
            visit[ i  *  prime1[j] ]  =  true;
            if (i % prime1[j] == 0) break; ///此处是重点，避免了很多的重复判断，比如i=9,现在素数是2,3,5,7,进入二重循环，visit[2*9]=1;visit[3*9]=1；这个时候9%3==0，要跳出。因为5*9可以用3*15来代替，如果这个时候计算了，i=15的时候又会被重复计算一次，所以这里大量避免了重复运算。
        }
    }
}

bool prime2[maxn+10];

void getprime2(int n)
{
    memset(prime2,1,sizeof(prime2));
    prime2[0]=prime2[1]=0;
    for (int i = 2; i < n; ++i)
    {
        if (prime2[i])
        {
            for (int j = i*i; j < n; j+=i)
                prime2[j]=0;
        }
    }
}

int main()
{
    scanf("%d",&n);
    getprime2(n);
    for (int i = 0; i < n; ++i)
    {
        if (prime2[i])
            printf("%d ", i);
    }
    return 0;
}