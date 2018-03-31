#include <iostream>
#include <cstring>
#include <map>

#define MAX_E 1000
#define MAX_N 100
using namespace std;
typedef struct _pos
{
    int from, to;
    double rate;
}pos;
pos E[MAX_E];
double D[MAX_N];
int n, m, i, j, k, l;
double r;

bool Bellman_Ford(int start)
{
    memset(D, 0, sizeof(D));
    D[start] = 1;
    for (i = 1; i < n; ++i)
        for (j = 1; j <= m; ++j)
        {
            if (D[E[j].to] < D[E[j].from] * E[j].rate)
                D[E[j].to] = D[E[j].from] * E[j].rate;
            if (D[start] > 1) return true;
        }

    for (i = 1; i <= m; ++i)
        if (D[E[i].to] < D[E[i].from] * E[i].rate)
            return true;
    return false;
}

int main()
{
    k = 1;
    while (cin >> n && n)
    {
        map<string, int> M;
        pos tmp;
        string s1, s2;
        for (i = 1; i <= n; ++i)
        {
            cin >> s1;
            M[s1] = i;
        }
        cin >> m;
        j = 1;
        for (i = 1; i <= m; ++i)
        {
            cin >> s1 >> r >> s2;
            tmp.from = M[s1]; tmp.to = M[s2];
            tmp.rate = r;
            E[j++] = tmp;
        }

        cout << "Case " << k++ << ": ";
        for (l = 1; l <= n; ++l)
        {
            if (Bellman_Ford(l))
            {
                cout << "Yes" << endl;
                break;
            } 
            else if (l == n)
                cout << "No" << endl;
        }
    }
    return 0;
}