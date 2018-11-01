#include <iostream>
using namespace std;

int main(int argc, char const *argv[])
{
    int n, m, q;
    cin >> n;
    while (n--)
    {
        q = 0;
        cin >> m;
        while (m > 0)
        {
            if (m % 2 == 1)
            {
                q++;
                m = (m - 1) / 2;
            } else {
                m /= 2;
            }
        }
        cout << q << endl;
    }
    return 0;
}