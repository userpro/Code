const int maxn = 2e5 + 10;
const double pi = acos(-1);

ll c[maxn];
ll d[maxn];

struct cplx {
    double r, i;
    cplx(double r = 0, double i = 0) : r(r), i(i) {}
    cplx operator + (const cplx &a) const {
        return cplx(r + a.r, i + a.i);
    }
    cplx operator - (const cplx &a) const {
        return cplx(r - a.r, i - a.i);
    }
    cplx operator * (const cplx &a) const {
        return cplx(r * a.r - i * a.i, r * a.i + i * a.r);
    }
} a[maxn << 2], b[maxn << 2];

void rader(cplx *f, int len)
{
    int j = len >> 1;
    for(int i = 1; i < len - 1; i++)
    {
        if(i < j) swap(f[i], f[j]);
        int k = len >> 1;
        while(j >= k)
        {
            j -= k;
            k >>= 1;
        }
        if(j < k) j += k;
    }
}

void FFT(cplx *f, int len, int t)
{
    rader(f, len);
    for(int h = 2; h <= len; h <<= 1)
    {
        cplx wn(cos(- t * 2 * pi / h), sin(- t * 2 * pi / h));
        for(int j = 0; j < len; j += h)
        {
            cplx e(1, 0);
            for(int k = j; k < j + h / 2; k++)
            {
                cplx u = f[k];
                cplx v = e * f[k + h / 2];
                f[k] = u + v;
                f[k + h / 2] = u - v;
                e = e * wn;
            }
        }
    }
    if(t == -1) for(int i = 0; i < len; i++) f[i].r /= len;
}

void Conv(cplx *a, cplx *b, int len)
{
    FFT(a, len, 1);
    FFT(b, len, 1);
    for(int i = 0; i < len; i++) a[i] = a[i] * b[i];
    FFT(a, len, -1);
}