/*
base64 解码 + AC
*/
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

#define MAXN 520
#define MAXM 130
#define CH   256
#define MAX_CASE_LINE 70
#define MAX_TARGET_LINE 2100

struct Trie
{
    int next[MAXN * MAX_CASE_LINE][CH], 
        fail[MAXN * MAX_CASE_LINE], end[MAXN * MAX_CASE_LINE];
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
    void insert(unsigned char s[], int tot, int id)
    {
        int len=tot;
        int now=root;
        for (int i=0;i<len;++i)
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

    bool used[MAXN];
    int query(unsigned char s[], int tot, int n)
    {
        memset(used,false,sizeof(used));
        int len=tot;
        int now=root;
        for (int i=0;i<len;i++)
        {
            now=next[now][s[i]];
            int temp=now;
            while (temp!=root)
            {
                if (end[temp]!=-1)
                    used[end[temp]]=true;
                temp=fail[temp];
            }
        }
        int ans=0;
        for (int i=0;i<n;i++)
            if (used[i])
                ans++;
        return ans;
    }
};

unsigned char get_c(unsigned char c)
{
    if (c >= '0' && c <= '9') return c-'0'+52;
    if (c >= 'a' && c <= 'z') return c-'a'+26;
    if (c >= 'A' && c <= 'Z') return c-'A';
    if (c == '+') return 62;
    if (c == '/') return 63;
    return 0; // '='
}

int tot;
void decode_base64(unsigned char s1[], unsigned char s2[])
{
    int t=0;
    int len = strlen((char*)s1);
    while (s1[len - 1] == '=') len--;
    for (int i=0;i<len;i++)
        s1[i]=get_c(s1[i]);

    for (int i=0;i<len;i+=4)
    {
        s2[t++]=((s1[i]<<2)|(s1[i+1]>>4));
        if(i+2 < len)
            s2[t++]=( (s1[i+1]<<4)|(s1[i+2]>>2) );
        if(i+3 < len)
            s2[t++]= ( (s1[i+2]<<6)|s1[i+3] );
    }
    tot=t;
}

Trie ac;
unsigned char s1[MAX_TARGET_LINE*2], s2[MAX_TARGET_LINE*2];
int N,M;

int main()
{
    while (scanf("%d",&N)!=EOF)
    {
        ac.init();
        for (int i=0;i<N;i++)
        {
            scanf("%s",s1);
            decode_base64(s1, s2);
            ac.insert(s2, tot, i);
        }
        ac.build();
        scanf("%d",&M);
        for (int i=0;i<M;i++)
        {
            scanf("%s",s1);
            decode_base64(s1, s2);
            printf("%d\n", ac.query(s2, tot, N));
        }
        printf("\n");
    }
    return 0;
}