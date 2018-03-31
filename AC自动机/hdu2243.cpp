/*
因为对2^64取模, 所以定义数据类型为unsigned long long就可以了, 这样就实现了自动取模.
本题使用AC自动机类似得到状态转移的矩阵.
但是因为要求和,所以在POJ 2778 得到的L*L的矩阵中, 需要增加一维, 第L+1列全部为1
这样求出不包含模式串, 而且长度不超过m的, 然后总数减掉这个就是答案了.. 
所有无效的单词个数为 A + A^2 + ... + A^m 个.
而所有单词的个数为26 + 26^2 + … + 26^m 个.两个减一下即为答案.

f[n]=1 + 26^1 + 26^2 +...26^n
f[n]=26*f[n-1]+1
{f[n] 1} = {f[n-1] 1}[26 1;0 1]
此题的L<2^31.矩阵的幂不能是L+1次, 否则就超时了

补充:
等比矩阵求和, 有经典算法, 假定原矩阵为A, 阶数为n, 那么构造一个阶数为2n的矩阵, 如下

   | A  E |  其中O代表O矩阵, E代表单位矩阵, 这样, 求出的K次矩阵的右上n子矩阵正好是
   | O  E |  等比矩阵的K项和

那么这就可以求出来了.
求26^m次方 用矩阵 |26 1| 然后用矩阵快速幂
                |0  1|  
 */

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;

struct Matrix
{
    unsigned long long mat[40][40];
    int n;
    Matrix() {}
    Matrix(int _n)
    {
        n=_n;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                mat[i][j]=0;
    }
    Matrix operator *(const Matrix& b) const
    {
        Matrix ret(n);
        for (int i=0;i<n;i++)
            for (int j=0;j<n;j++)
                for (int k=0;k<n;k++)
                {
                    unsigned long long temp=mat[i][k]*b.mat[k][j];
                    ret.mat[i][j]+=temp;
                }

        return ret;
    }
};

#define CH 26
struct Trie
{
    int next[40][CH], fail[40];
    bool end[40];
    int tot, root;
    int newnode()
    {
        for (int i=0;i<CH;i++)
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
    void insert(char s[])
    {
        int len=strlen(s);
        int now=root;
        for (int i=0;i<len;i++)
        {
            if (next[now][s[i]-'a']==-1)
                next[now][s[i]-'a']=newnode();
            now=next[now][s[i]-'a'];
        }
        end[now]=true;
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
            if (end[fail[now]]==true)
                end[now]=true;
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
    Matrix getMatrix()
    {
        Matrix ret(tot+1);
        for (int i=0;i<tot;i++)
            for (int j=0;j<CH;j++)
                if (end[next[i][j]]==false)
                    ret.mat[i][next[i][j]]++;

        for (int i=0;i<tot+1;i++)
            ret.mat[i][tot]=1;
        return ret;
    }
};


Matrix powM(Matrix &a, int m)
{
    Matrix ret(a.n);
    for (int i=0;i<a.n;i++)
        ret.mat[i][i]=1;
    Matrix temp=a;
    while (m>0)
    {
        if (m&1) ret=ret*temp;
        temp=temp*temp;
        m>>=1;
    }
    return ret;
}


Trie ac;
int N, L;
char buf[40];
int main()
{
    while (scanf("%d%d",&N,&L)!=EOF)
    {
        ac.init();
        for (int i=0;i<N;i++)
        {
            scanf("%s",buf);
            ac.insert(buf);
        }
        ac.build();
        Matrix t=ac.getMatrix();
        t=powM(t,L);
        unsigned long long res=0;
        for (int i=0;i<t.n;i++)
            res+=t.mat[0][i];
        res--;

        t=Matrix(2);
        t.mat[0][0]=26;
        t.mat[0][1]=t.mat[1][1]=1;
        t=powM(t,L);
        unsigned long long ans=t.mat[0][1]+t.mat[0][0];
        ans--;
        ans-=res;
        printf("%llu\n", ans);
    }
    return 0;
}
