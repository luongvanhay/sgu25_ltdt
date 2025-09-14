#include <bits/stdc++.h>
using namespace std;

int main() {
    int n1, n2, n3;
    cin >> n1;
    vector<int> a(n1);
    for(int i = 0; i < n1; i++) cin >> a[i];

    cin >> n2;
    vector<int> b(n2);
    for(int i = 0; i < n2; i++) cin >> b[i];

    cin >> n3;
    vector<int> c(n3);
    for(int i = 0; i < n3; i++) cin >> c[i];

    set<int> sa(a.begin(), a.end());
    set<int> sb(b.begin(), b.end());
    set<int> sc(c.begin(), c.end());

    vector<int> res;
    for(int x : sa) {
        if(sb.count(x) && sc.count(x)) res.push_back(x);
    }
    sort(res.begin(), res.end());

    cout << res.size() << "\n";
    for(int i = 0; i < res.size(); i++) {
        if(i) cout << " ";
        cout << res[i];
    }
    cout << "\n";

    return 0;
}
