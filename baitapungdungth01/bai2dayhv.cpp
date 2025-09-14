#include <bits/stdc++.h>
using namespace std;

int main() {
    int N;
    cin >> N;
    vector<int> A(N);
    vector<bool> check(N + 1, false); // đánh dấu số đã xuất hiện

    for (int i = 0; i < N; i++) {
        cin >> A[i];
        if (A[i] < 1 || A[i] > N) {
            cout << "NO";
            return 0;
        }
        if (check[A[i]]) { // trùng lặp
            cout << "NO";
            return 0;
        }
        check[A[i]] = true;
    }

    // nếu đủ 1..N
    cout << "YES";
    return 0;
}
