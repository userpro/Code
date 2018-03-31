/* 
图论:
给定一个有向图, 问从A点恰好走k步(允许重复经过边)到达B点的方案数mod p的值
把给定的图转为邻接矩阵, 即 A(i,j) = 1 当且仅当存在一条边 i->j.
令 C = A * A, 那么 C(i,j) = ΣA(i,k) * A(k,j), 实际上就等于从点i到点j恰好经过2条边的路径数(枚举k为中转点).
类似地, C * A(这里的C已经是A * A)的第i行第j列就表示从i到j经过3条边的路径数
同理, 如果要求经过k步的路径数, 我们只需要二分求出 A^k 即可.
*/

#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>

using namespace std;

const int MOD=100000;
struct Matrix
{
    int mat[110][110], n;
    Matrix() {}
    Matrix(int _n)
    {
        n = _n;
        for (int i=0;i<n;i++)
            for (int j=0;j<n;j++)
                mat[i][j]=0;
    }
    Matrix operator *(const Matrix &b) const
    {
        Matrix ret(n);
        for (int i=0;i<n;i++)
            for (int j=0;j<n;j++)
                for (int k=0;k<n;k++)
                {
                    int temp=(long long)mat[i][k]*b.mat[k][j]%MOD;
                    ret.mat[i][j]=(ret.mat[i][j]+temp)%MOD;
                }

        return ret;
    }
};

struct Trie
{
    int next[110][4],fail[110];
    bool end[110];
    int root,tot;
    int newnode()
    {
        for (int i=0;i<4;i++)
            next[tot][i]=-1;
        end[tot++]=false;
        return tot-1;
    }
    void init()
    {
        tot=0;
        root=newnode();
        memset(end,false,sizeof(end));
    }
    int getch(char ch)
    {
        switch (ch)
        {
            case 'A': return 0;
            case 'C': return 1;
            case 'G': return 2;
            case 'T': return 3;
        }
        return 0;
    }
    void insert(char s[])
    {
        int len=strlen(s);
        int now=root;
        for (int i=0;i<len;i++)
        {
            if (next[now][getch(s[i])]==-1)
                next[now][getch(s[i])]=newnode();
            now=next[now][getch(s[i])];
        }
        end[now]=true;
    }
    void build()
    {
        queue<int> que;
        for (int i=0;i<4;i++)
        {
            if (next[root][i]==-1)
                next[root][i]=root;
            else
            {
                fail[next[root][i]] = root;
                que.push(next[root][i]);
            }
        }

        while (!que.empty())
        {
            int now=que.front(); que.pop();
            if (end[fail[now]]==true)
                end[now]=true;
            for (int i=0;i<4;i++)
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
    Matrix getMatrix()
    {
        Matrix res(tot);
        for (int i=0;i<tot;i++)
            for (int j=0;j<4;j++)
                if (end[next[i][j]]==false)
                    res.mat[i][next[i][j]]++;

        return res;
    }
};

Trie ac;
char buf[20];

Matrix pow_M(Matrix a, int n)
{
    Matrix ret(a.n);
    for (int i=0;i<ret.n;i++)
        ret.mat[i][i]=1;
    Matrix tmp = a;
    while (n>0)
    {
        if (n&1) ret=ret*tmp;
        tmp=tmp*tmp;
        n>>=1;
    }
    return ret;
}

int main(int argc, char const *argv[])
{
    int n,m;
    while (scanf("%d%d",&m,&n)!=EOF)
    {
        ac.init();
        for (int i=0;i<m;i++)
        {
            scanf("%s",buf);
            ac.insert(buf);
        }
        ac.build();
        Matrix t=ac.getMatrix();
        t=pow_M(t,n);
        long long ans=0;
        for (int i=0;i<t.n;i++)
            ans=(ans+t.mat[0][i])%MOD;
        printf("%lld\n", ans);
    }
    return 0;
}