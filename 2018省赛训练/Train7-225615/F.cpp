#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
#include <cmath>
#include <map>
#include <iostream>
#include <string>
using namespace std;
#define INF (1<<29)
#define LL long long
#define CLR(a,b) memset(a,b,sizeof(a))

int getDay(string s)
{
    if (s == "sunday") return 0;
    if (s == "monday") return 1;
    if (s == "tuesday") return 2;
    if (s == "wednesday") return 3;
    if (s == "thursday") return 4;
    if (s == "friday") return 5;
    if (s == "saturday") return 6;
}

int main()
{
    string s1, s2;
    int a, b;
    int days[12] = {0, 3, 3, 6, 1, 4, 6, 2, 5, 0, 3, 5};
    while (cin >> s1 >> s2)
    {
        a = getDay(s1);b = getDay(s2);
        if (a != b)
        {
            bool flag = false;
            for(int i=0; i<7; i++)
            {
                for(int j=0; j<11; j++)
                {
                    if ((days[j] + i) % 7 == a && (days[j+1] + i) % 7 == b)
                    {
                        flag = true;
                        break;
                    }
                }
                if (flag) break;
            }
            if (flag) cout << "YES"; else cout << "NO";
        }
        else cout << "YES";
        cout << endl;
    }
    return 0;
}