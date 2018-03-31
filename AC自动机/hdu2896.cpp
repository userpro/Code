#include <cstdio>
#include <cstring>
#include <queue>

#define CH 128
#define MAXC (210*500)
using namespace std;

struct Trie
{
    int next[MAXC][CH], fail[MAXC], end[MAXC];
    int root, tot;

    void init()
    {
        tot=0;
        root=newnode();
    }

    int newnode()
    {
        for (int i=0;i<CH;i++)
            next[tot][i]=-1;
        end[tot++]=-1;
        return tot-1;
    }

    void insert(char buf[], int id)
    {
        int len=strlen(buf);
        int now=root;
        for (int i=0;i<len;i++)
        {
            if (next[now][buf[i]]==-1)
                next[now][buf[i]]=newnode();
            now=next[now][buf[i]];
        }
        end[now]=id;
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

    bool used[510];
    bool query(char buf[], int n, int id)
    {
        bool flag=false;
        memset(used,0,sizeof(used));
        int len=strlen(buf);
        int now=root;
        int res=0;
        for (int i=0;i<len;i++)
        {
            now=next[now][buf[i]];
            int temp=now;
            while (temp!=root)
            {
                if (end[temp]!=-1)
                {
                    used[end[temp]]=true;
                    flag=true;
                }
                temp=fail[temp];
            }
        }
        if (!flag) return false;
        printf("web %d:", id);
        for (int i=0;i<=n;i++)
            if (used[i])
                printf(" %d", i);
        printf("\n");
        return true;
    }
};


#define MAXN 10010

Trie ac;
int N,M;
char s[MAXN];

int main()
{
    while (scanf("%d",&N)!=EOF)
    {
        ac.init();
        for (int i=0;i<N;i++)
        {
            scanf("%s",s);
            ac.insert(s,i+1);
        }
        ac.build();
        scanf("%d",&M);
        int total=0;
        for (int i=0;i<M;i++)
        {
            scanf("%s",s);
            if (ac.query(s,N,i+1))
                total++;
        }
        printf("total: %d\n", total);
    }
    return 0;
}