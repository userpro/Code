#include <stdio.h>

using namespace std;
#define uint unsigned long long

uint gcd(uint a, uint b)
{
    if (b == 0) return a;
    return gcd(b, a%b);
}

uint lcm(uint a, uint b)
{
    return a*b/gcd(a,b);
}