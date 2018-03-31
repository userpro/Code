struct matrix 
  {
    int n,m;
    long long a[N][N];
    matrix (){n=0;m=0;memset(a,0,sizeof(a));}
    matrix (int _n,int _m):n(_n),m(_m)
      {
        memset(a,0,sizeof(a));
      }
    long long *operator [](int x) { return a[x];}
  	matrix operator * (matrix b) 
      {
        matrix c=matrix(n,b.m);
        for (int i=0;i<n;++i)
          for (int j=0;j<b.m;++j)
            for (int k=0;k<m;++k)
              c[i][j]+=a[i][k]*b[k][j],c[i][j]%=P;
        return c;
      }
    matrix operator ^ (long long T) 
      {
        matrix a,b=matrix(n,m);a=*this;
        for (int i=0;i<n;++i) b[i][i]=1;
        while (T) 
          {
            if (T&1) b=b*a;
            a=a*a;
            T/=2;
          }
        return b;
      }
  };