/* 
    快速幂算法中矩阵上应用
    MOD mat维数 根据题意改变 
*/
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

Matrix pow_M(Matrix a, int n)
{
    Matrix ret(a.n);
    for (int i=0;i<ret.n;i++)
        ret.mat[i][i]=1;
    Matrix tmp(a);
    while (n>0)
    {
        if (n&1) ret=ret*tmp;
        tmp=tmp*tmp;
        n>>=1;
    }
    return ret;
}