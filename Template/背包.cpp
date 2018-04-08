#include <iostream>  
#include <cstring>  
using namespace std;  
#define maxV 1000  
  
int f[maxV], v;  
  
void ZeroOnePack(int ci, int wi) {  
    for (int j = v; j >= 0; j--)   
        if (j >= ci)  
            f[j] = max(f[j], f[j - ci] + wi);  
}  
  
void CompletePack(int ci, int wi) {  
    for (int j = 0; j <= v; j++)   
        if (j >= ci)  
            f[j] = max(f[j], f[j - ci] + wi);  
}  
  
void MultiplePack(int ni, int ci, int wi) {  
    if (ni * ci >= v) {  
        CompletePack(ci, wi);  
        return;  
    }  
    int k = 1, amount = ni;  
    while (k < ni) {  
        ZeroOnePack(ci * k, wi * k);  
        amount -= k;  
        k *= 2;  
    }  
    ZeroOnePack(ci * amount, wi * amount);  
}  
  
int main(void) {  
    int cases, n, ni, ci, wi;  
    freopen("4.txt", "r", stdin);  
    cin >> cases;  
    while (cases--) {  
        memset(f, 0, sizeof(f));  
        cin >> n >> v;  
        for (int i = 0; i < n; i++) {  
            cin >> ni >> ci >> wi;  
            if (ni == 1) ZeroOnePack(ci, wi);  
            else if (ni == -1) CompletePack(ci, wi);  
            else MultiplePack(ni, ci, wi);  
        }  
        for (int i = 0; i <= v; i++) cout << f[i] << " "; cout << endl;  
        cout << f[v] << endl;  
    }  
}  