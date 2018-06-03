#include <cstdio>
#include <cstring>
#include <algorithm>
#define LL long long
#define MAXN 100010
#define CLR(a,b) memset(a,b,sizeof(a))

LL num[MAXN];
struct SegTree
{
    #define Mid ((l+r)>>1)
    #define lson l,m,rt<<1
    #define rson m+1,r,rt<<1|1
    LL _sum[MAXN<<2], _lazy[MAXN<<2];

    void PushDown(int rt)
    {
        if (_lazy[rt])
        {
            _sum[rt << 1] += _lazy[rt];  
            _sum[rt << 1 | 1] += _lazy[rt];  
            _lazy[rt << 1] += _lazy[rt];  
            _lazy[rt << 1 | 1] += _lazy[rt];  
            _lazy[rt] = 0; 
        }
    }

    inline void PushUp(int rt)
    {
        _sum[rt]=_sum[rt<<1]+_sum[rt<<1|1];
    }

    void Build(LL l, LL r, LL rt)
    {
        _lazy[rt]=0;
        if (l==r)
        {
            _sum[rt]=num[l];
            return;
        }
        LL m=Mid;
        Build(lson);
        Build(rson);
        PushUp(rt);
    }

    void UpdateRange(LL L, LL R, LL val, LL l, LL r, LL rt)
    {
        if (L<=l && r<=R)
        {
            _sum[rt]+=val;
            _lazy[rt]+=val;
            return;
        }
        PushDown(rt);
        LL m=Mid;
        if (L<=m) UpdateRange(L,R,val,lson);
        if (R>m) UpdateRange(L,R,val,rson);
        PushUp(rt);
    }

    void UpdateOne(LL pos, LL val, LL l, LL r, LL rt)
    {
        if (l==r && r==pos)
        {
            _sum[rt]=val;
            return;
        }
        LL m=Mid;
        if (pos<=m) UpdateOne(pos,val,lson);
        else UpdateOne(pos,val,rson);
        PushUp(rt);
    }

    LL Query(LL L, LL R, LL l, LL r, LL rt)
    {
        if (L<=l && r<=R)
            return _sum[rt];
        PushDown(rt);
        LL m=Mid;
        LL ans=0;
        if (L<=m) ans+=Query(L,R,lson);
        if (R>m) ans+=Query(L,R,rson);
        return ans;
    }
};

SegTree st;
int main()
{
    return 0;
}