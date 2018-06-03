#include <vector>

using namespace std;

void solve(int n)
{
    vector<int> v;
    for (int i = 2; i*i <= n; ++i)
    {
        if (n%i==0)
        {
            v.push_back(i);
            while (n%i==0) n/=i;
        }
    }
    if (n>1) v.push_back(n);
}