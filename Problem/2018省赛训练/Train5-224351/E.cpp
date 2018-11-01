#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
#include <map>
#include <iostream>
using namespace std;
#define INF (1<<29)
#define LL long long
#define CLR(a,b) memset(a,b,sizeof(a))
#define MAX 400

float a[MAX][MAX], b[MAX][MAX], cur[MAX];
int T, n, m, k;

int getDiease(int x)
{
    float p[MAX];
    for(int i=0; i<n; i++) p[i] = cur[i] * b[i][x-1];
    float max = p[0];
    int tmp=0;
    for(int i=1; i<n; i++) if(p[i]>max) {max = p[i]; tmp = i;}
    return tmp;
}

int main()
{ 
    int d[MAX];
    cin >> T;
    while(T--)
    {
        cin >> n >> m >> k;
        for(int i=0; i<n; i++) for(int j=0; j<n; j++) cin >> a[i][j];
        for(int i=0; i<n; i++) for(int j=0; j<m; j++) cin >> b[i][j];
        for(int i=0; i<n; i++) cin >> cur[i];
        for(int i=0; i<k; i++) cin >> d[i];
        for(int i=0; i<k; i++)
        {
            int x = d[i];
            int di = getDiease(x);
            if(i) cout << ' ';
               cout << di+1;
            for(int j=0; j<n; j++) cur[j] = a[j][di];
        }
        cout << endl;
    }
    return 0;
}