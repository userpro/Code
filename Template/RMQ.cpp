void RMQ(int _n)
{
    int i,j,k;
    for (i=1;i<=_n;i++)
        rmax[i][0]=f[i];
    k=log((double)(_n+1))/log(2.0);
    for (j=1;j<=k;j++)
        for (i=1;i+(1<<j)-1<=_n;i++)
            rmax[i][j]=max(rmax[i][j-1], rmax[i+(1<<(j-1))][j-1]);
}

int rmq_max(int l,int r)
{
    if (l>r)
        return 0;
    int k=log((double)(r-l+1))/log(2.0);
    return max(rmax[l][k], rmax[r-(1<<k)+1][k]);
}