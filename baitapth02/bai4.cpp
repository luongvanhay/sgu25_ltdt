#include <iostream>
#include <fstream>
using namespace std;

#define FI "text4.INP"
#define FO "text4.OUT"
#define MAXN 100000
#define MAXM 1000000

int n, m;
int deg[MAXN];

void nhap() {
    ifstream fi(FI);
    fi >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v;
        fi >> u >> v;
        deg[u]++;
        deg[v]++;
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
