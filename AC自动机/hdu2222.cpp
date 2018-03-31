#include <cstdio>
#include <cstring>
#include <queue>

#define CH 26
#define MAXN 500005
using namespace std;

struct Trie
{
    int next[MAXN][CH], fail[MAXN], end[MAXN];
    int root;
    int tot;
    int newnode()
    {
        for (int i=0;i<CH;i++)
            next[tot][i]=-1;
        end[tot++]=0;
        return tot-1;
    }
    void init()
    {
        tot=0;
        root=newnode();
    }
    void insert(char buf[])
    {
        int len=strlen(buf);
        int now=root;
        for (int i=0;i<len;i++)
        {
            int k=buf[i]-'a';
            if (next[now][k]==-1)
                next[now][k]=newnode();
            now=next[now][k];
        }
        end[now]++;
    }

    void build()
    {
        queue<int> que;
        fail[root]=root;
        for (int i=0;i<CH;i++)
        {
            if (next[root][i]==-1)
                next[root][i]=root;
            else
            {
                fail[next[root][i]]=root;
                que.push(next[root][i]);
            }
        }

        while (!que.empty())
        {
            int now=que.front();
            que.pop();
            for (int i=0;i<CH;i++)
            {
                if (next[now][i]==-1)
                    next[now][i]=next[fail[now]][i];
                else
                {
                    fail[next[now][i]]=next[fail[now]][i];
                    que.push(next[now][i]);
                }
            }
        }
    }

    int query(char buf[])
    {
        int len=strlen(buf);
        int now=root;
        int res=0;
        for (int i=0;i<len;i++)
        {
            now=next[now][buf[i]-'a'];
            int temp=now;
            while (temp!=root)
            {
                res+=end[temp];
                end[temp]=0;
                temp=fail[temp];
            }
        }
        return res;
    }
};

Trie ac;
char buf[MAXN+MAXN];
int T,N;

int main()
{
    scanf("%d",&T);
    while (T--)
    {
        scanf("%d",&N);
        ac.init();
        for (int i=0;i<N;i++)
        {
            scanf("%s",buf);
            ac.insert(buf);
        }
        ac.build();
        scanf("%s",buf);
        printf("%d\n", ac.query(buf));
    }
    return 0;
}