void kmp_pre(int n)
{
    int i,j;
    j=nx[0]=-1;
    i=0;
    while (i<n)
    {
        while (j!=-1 && a[i]!=a[j]) j=nx[j];
        nx[++i]=++j;
    }
}

int kmp_count(int n, int m)
{
    prekmp(n);
    int i,j,ans;
    i=j=ans=0;
    while (i<m)
    {
        if (j==-1 || x[j]==y[i])
        {
            i++; j++;
        } else {
            j=nx[j];
        }
        if (j>=n)
        {
            ans++;
            j=nx[j];
        }
    }
    return ans;
}