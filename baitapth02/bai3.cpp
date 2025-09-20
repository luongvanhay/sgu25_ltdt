#include <iostream>
#include <fstream>
using namespace std;

#define FI "text3.INP"
#define FO "text3.OUT"
#define MAXN 100000

int n;
int deg[MAXN];

void nhap() {
    ifstream fi(FI);
    fi >> n;
    for (int i = 1; i <= n; i++) {
        deg[i] = 0;
        int x;
        while (fi >> x) {
            if (x == -1) break; 
            deg[i]++;
        }
    }
    fi.close();
}

void xuat() {
    ofstream fo(FO);
    fo << n << "\n";
    for (int i = 1; i <= n; i++) {
        fo << deg[i] << "\n";
    }
    fo.close();
}

int main() {
    nhap();
    xuat();
    return 0;
}
