// https://blog.csdn.net/niushuai666/article/details/6624672/

void RMQ1(int num) //预处理->O(nlogn)  
{  
    for(int j = 1; j < 20; ++j)  
        for(int i = 1; i <= num; ++i)  
            if(i + (1 << j) - 1 <= num)  
            {  
                maxsum[i][j] = max(maxsum[i][j - 1], maxsum[i + (1 << (j - 1))][j - 1]);  
                minsum[i][j] = min(minsum[i][j - 1], minsum[i + (1 << (j - 1))][j - 1]);  
            }  
} 

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