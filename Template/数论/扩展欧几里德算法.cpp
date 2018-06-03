// ax + by = gcd(a, b)
// 返回值是 gcd(a, b)
int extend_Euclid(int a, int b, int &x, int &y)
{
    if(b==0)
    {
        x = 1;
        y = 0;
        return a;
    }
    int r = extend_Euclid(b, a%b, y, x);
    y -= a/b*x; //这里已经是递归，回溯的过程了，x,y已经颠倒了
    return r;
}