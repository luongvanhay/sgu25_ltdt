#include <iostream>
#include <fstream>
using namespace std;

#define FI "text2.INP"
#define FO "text2.OUT"
#define MAXN 1000

int a[MAXN][MAXN];
int n;
int degIn[MAXN], degOut[MAXN];

void nhap() {
    ifstream fi(FI);
    fi >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fi >> a[i][j];
        }
    }
    fi.close();
}

void tinhBac() {
    for (int i = 0; i < n; i++) {
        degIn[i] = degOut[i] = 0;
        for (int j = 0; j < n; j++) {
            if (a[i][j] == 1) {
                degOut[i]++;   // i có cạnh đi ra
                degIn[j]++;    // j có cạnh đi vào
            }
        }
    }
}

void xuat() {
    ofstream fo(FO);
    fo << n << "\n";
    for (int i = 0; i < n; i++) {
        fo << degIn[i] << " " << degOut[i] << "\n";
    }
    fo.close();
}

int main() {
    nhap();
    tinhBac();
    xuat();
    return 0;
}
