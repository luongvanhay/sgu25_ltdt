#include <bits/stdc++.h>
using namespace std;

long long so0_tancung(long long n) {   // Hàm tính số chữ số 0 tận cùng của N!
    long long a = 0;
    while(n > 0) {
        n /= 5;
        a += n;
    }
    return a;
}

int main() {
    long long n;
    while(cin >> n) {
        cout << so0_tancung(n) << "\n";
    }
    return 0;
}
