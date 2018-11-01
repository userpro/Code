#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;
#define MAXN 110
struct Node
{
    int a;
    int b;
    int index;
} A[MAXN];
int n,w;

bool cmp1(Node& n1,Node& n2)
{
    return n1.a<n2.a;
}

bool cmp2(Node& n1,Node& n2)
{
    return n1.b<n2.b;
}

bool cmp3(Node& n1,Node& n2)
{
    return n1.index<n2.index;
}

int main()
{
    while (scanf("%d%d",&n,&w)!=EOF)
    {
        for (int i=1;i<=n;i++)
        {
            scanf("%d",&A[i].a);
            A[i].b=0;
            A[i].index=i;
        }
        sort(A+1,A+n+1,cmp1);
        int leave=w;
        for (int i=1;i<=n;i++)
        {
            A[i].b=(A[i].a+1)/2;
            leave-=A[i].b;
        }
        bool flag=false;
        if (leave>=0)
        {
            for (int i=n;i>=1&&leave>0;i--)
            {
                int tmp=A[i].a-A[i].b;
                if (leave>tmp)
                {
                    leave-=A[i].a-A[i].b;
                    A[i].b=A[i].a;
                }
                else
                {
                    A[i].b+=leave;
                    leave=0;
                }
            }
            if (leave>0)
                flag=false;
            else
                flag=true;
        }
        if (!flag)
            printf("-1\n");
        else
        {
            sort(A+1,A+n+1,cmp3);
            for (int i=1;i<=n;i++)
                printf("%d ", A[i].b);
            printf("\n");
        }
    }
    return 0;
}