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

int main()
{
    LL s[200001], last = 0;;
    
    int n, t, i;
    cin >> n;
    for(i=0; i<n; i++) {cin >> t; s[i] = last + t; last = s[i];}
    LL half = s[n-1]/2 + s[n-1]%2;
    for(i=0; i<n; i++) if(s[i] >= half) break;
    cout << i+1;

    return 0;
}