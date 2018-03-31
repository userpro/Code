#include <iostream>
#include <cstring>
using namespace std;
int main()
{
    char s[100];
    int length = 0, count = 0, i = 0;
    while (cin >> s && s[0] != '#')
    {
        count = 0;
        length = strlen(s);
        for ( i = 0; i < length-1; ++i)
            if (s[i] == '1')
                count++;

        if (s[length - 1] == 'e')
        {
            if (count % 2 == 0 )
                s[length - 1] = '0';
            else
                s[length - 1] = '1';
        } else if(s[length - 1] == 'o'){
            if (count % 2 == 0)
                s[length - 1] = '1';
            else
                s[length - 1] = '0';
        }
        s[length] = '\0';
        cout << s << endl;
    }
    return 0;
}