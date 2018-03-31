#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

#define CH 128
#define MAXN 1010
#define MAXM 2000005

char s1[MAXN][60];
struct Trie
{
    int next[MAXN*50][CH], fail[MAXN*50], end[MAXN*50];
    int tot, root;
    int newnode()
    {
        for (int i=0;i<CH;i++)
            next[tot][i]=-1;
        end[tot++]=-1;
        return tot-1;
    }
    void init()
    {
        tot=0;
        root=newnode();
    }
    void insert(char s[], int id)
    {
        int len=strlen(s);
        int now=root;
        for (int i=0;i<len;i++)
        {
            if (next[now][s[i]]==-1)
                next[now][s[i]]=newnode();
            now=next[now][s[i]];
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
            int now=que.front(); que.pop();
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

    void query(char s[], int n)
    {
        int cnt[MAXN];
        memset(cnt,0,sizeof(cnt));
        int len=strlen(s);
        int now=root;
        for (int i=0;i<len;i++)
        {
            now=next[now][s[i]];
            int temp=now;
            while (temp!=root)
            {
                if (end[temp]!=-1)
                    cnt[end[temp]]++;
                temp=fail[temp];
            }
        }

        for (int i=0;i<=n;i++)
            if (cnt[i]>0)
                printf("%s: %d\n", s1[i], cnt[i]);
    }
};

Trie ac;
int n;
char s2[MAXM];

int main(int argc, char const *argv[])
{
    while (scanf("%d",&n)!=EOF)
    {
        ac.init();
        for (int i=0;i<n;i++)
        {
            scanf("%s",s1[i]);
            ac.insert(s1[i],i);
        }
        ac.build();
        scanf("%s",s2);
        ac.query(s2, n);
    }
    return 0;
}