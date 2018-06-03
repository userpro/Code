#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;
#define MAXN 10000010
#define uint unsigned int
uint n,m,A,B,C,x,y,z;
struct Query
{
    int n;
    int id;
} query[110];

uint num[MAXN];
uint ans[110];

unsigned rng61() {
  unsigned t;
  x ^= x << 16;
  x ^= x >> 5;
  x ^= x << 1;
  t = x;
  x = y;
  y = z;
  z = t ^ x ^ y;
  return z;
}

bool cmp(const Query& q1,const Query& q2)
{
    return q1.id<q2.id;
}

bool cmp1(const Query& q1,const Query& q2)
{
    return q1.n<q2.n;
}


int main()
{
    int cnt=1;
    while (scanf("%u%u%u%u%u",&n,&m,&A,&B,&C)!=EOF)
    {
        x = A, y = B, z = C;
        for (int i=0;i<n;i++)
            num[i]=rng61();

        for (int i=0;i<m;i++)
        {
            scanf("%d",&query[i].n);
            query[i].id=i;
        }
        sort(query,query+m,cmp1);
        printf("Case #%d:", cnt++);

        query[m].id=m; 
        query[m].n=n;
        
        for (int i=m-1;i>=0;i--)
        {
            if (query[i+1].n==query[i].n)
            {
                ans[query[i].id]=ans[query[i+1].id];
                continue;
            }
            nth_element(num, num+query[i].n, num+query[i+1].n);
            ans[query[i].id]=num[query[i].n];
        }

        for (int i=0;i<m;i++)
            printf(" %u", ans[i]);
        printf("\n");
    }
    return 0; 
}