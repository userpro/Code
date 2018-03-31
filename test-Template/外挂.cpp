#include <time.h>
clock_t start=clock(); cout<<(double)(clock()-start)/CLOCKS_PER_SEC<<endl;

inline int read() 
  {
    char ch;int x;
    while (ch=getchar(),!(ch>='0' && ch<='9'));x=ch-'0';
    while (ch=getchar(),ch>='0' && ch<='9') x*=10,x+=ch-'0';
    return x;
  }
inline void read(int &x) 
  {
    char ch; int s=1;x=0;
    while (ch=getchar(),(ch<'0' || ch>'9') && (ch!='-'));
    if (ch=='-') s=-1; else x =ch-'0';
    while (ch=getchar(),ch>='0' && ch<='9') x*=10,x+=ch-'0';
    x*=s;
  }