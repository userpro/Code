#include <iostream>
using namespace std;

int main(int argc, char const *argv[])
{
    int n1, n2, n5;
    while (cin>>n1>>n2>>n5 && (n1+n2+n5))
    {
        if (n1>0)
            if (n1 + n2 * 2 >= 5)
                cout<<n1+n2*2+n5*5+1<<endl;
            else
                cout<<n1+n2*2+1<<endl;
        else
            cout<<1<<endl;
    }
    return 0;
}