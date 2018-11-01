#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
#include <cmath>
#include <map>
#include <string>
#include <iostream>
using namespace std;
#define INF (1<<29)
#define LL long long
#define CLR(a,b) memset(a,b,sizeof(a))

typedef struct
{
    char w[16];
    int weight;
} word;

bool comp(const word &a, const word &b)
{return (a.weight>b.weight || (a.weight == b.weight && strcmp(a.w, b.w) < 0));}

int main()
{
    int t, n, m;
    LL h;
    word words[101];
    scanf("%d", &t);
    while(t--)
    {
        scanf("%d%d", &n, &m);
        for(int i=0; i<n; i++)
            scanf("%s%d", words[i].w, &words[i].weight);
        sort(words, words+n, comp);
        h = 0;
        for(int i=0; i<m; i++) h += (LL)(m-i) * words[i].weight;
        printf("%lld", h);
        for(int i=0; i<m; i++) printf(" %s", words[i].w);
        putchar('\n');
    }

    return 0;
}