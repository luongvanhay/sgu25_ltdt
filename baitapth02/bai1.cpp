#include<iostream>
#include<fstream>   
using namespace std;
#define FI "text.INP"
#define FO "text.OUT"
# define MAXN 1000

int a[MAXN][MAXN];
int n;
int deg[MAXN];
ifstream fi; 
ofstream fo;
void nhap() {
    ifstream fi(FI);
    fi >> n;
    for( int i=0; i<n;i++) {
        for( int j= 0; j<n; j++) {
            fi >> a[i][j];
        }
    }
    fi.close();
}  

void xuat() {
    ofstream fo(FO);
    fo << n << "\n";
    for( int i=0; i<n; i++){
        fo << deg[i]<< "\n";
    }
    fo.close();
}

void tinhbac(){
    for( int i=0; i<n; i++){
        deg[i]=0;
        for( int j=0; j<n; j++){
            if ( a[i][j]==1) deg[i]++;
        }
    }
}
int main() {
    nhap();
    tinhbac();
    xuat();
    return 0;
}



