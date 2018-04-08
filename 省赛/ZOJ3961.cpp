#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
#define MAXN 110
int T,n,m,x,y;
struct Node
{
    int x;
    int y;
    Node() : x(0),y(0) { }
    Node(int _x, int _y) : x(_x),y(_y) { }
    friend bool operator < (const Node& n1, const Node& n2)
    {
        if (n1.x==n2.x)
            return n1.y<n2.y;
        return n1.x<n2.x;
    }
} EA[MAXN],EB[MAXN];
int EAindex,EBindex;

void addA(int x,int y)
{
    EA[EAindex].x=x;
    EA[EAindex].y=y;
    EAindex++;
}

void addB(int x,int y)
{
    EB[EBindex].x=x;
    EB[EBindex].y=y;
    EBindex++;
}

int main()
{
    while (scanf("%d",&T)!=EOF)
    {
        while (T--)
        {
            EAindex=EBindex=0;
            int a,b;
            scanf("%d%d%d%d",&n,&m,&x,&y);
            for (int i=0;i<x;i++)
            {
                scanf("%d%d",&a,&b);
                addA(a,b);
            }
            for (int i=0;i<y;i++)
            {
                scanf("%d%d",&a,&b);
                addB(a,b);
            }
            sort(EA,EA+EAindex);
            sort(EB,EB+EBindex);
            int ans=0;
            for (int i=0;i<EAindex;i++)
            {
                for (int j=0;j<EBindex;j++)
                {
                    if (EA[i].y<EB[j].x) break;
                    int l=max(EA[i].x,EB[j].x);
                    int r=min(EA[i].y,EB[j].y);
                    if (r-l+1>=m)
                        ans+=(r-l+1)-m+1;
                }
            }
            printf("%d\n", ans);
        }
    }
    return 0;
}