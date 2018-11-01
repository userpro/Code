#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

using namespace std;
#define mem(a,b) (memset(a,b,sizeof(a)))
struct Node
{
    int w;
    friend bool operator<(Node n1,Node n2)
    {
        return n1.w>n2.w;
    }
};
int a[30];
char s[500];
int T,N;

int main()
{
    scanf("%d",&T);
    while (T--)
    {
        mem(a,0); mem(s,0);
        scanf("%d%s",&N,s);
        int len=strlen(s);
        for (int i = 0; i < len; ++i)
            a[s[i]-'a'+1]++;

        priority_queue<Node> q;
        for (int i = 0; i < 30; ++i)
        {
            if (a[i])
            {
                Node t;
                t.w=a[i];
                q.push(t);
            }
        }

        int ans=0;
        if (q.size()==1)
        {
            ans=len;
        } else {
            while (q.size()>1)
            {
                int aa=q.top().w; q.pop();
                int bb=q.top().w; q.pop();
                Node t;
                t.w=aa+bb;
                ans+=t.w;
                q.push(t);
            }
        }

        if (ans<=N)
            printf("yes\n");
        else
            printf("no\n");
    }
    return 0;
}