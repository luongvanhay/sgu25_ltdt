#include <bits/stdc++.h>
using namespace std;
int main() {
    int a;
    if(!(cin >> a)) return 0;
    string s;
    getline(cin, s);
    while(a--) {
        getline(cin, s);
        if((int)s.size() < 3) {
            cout << 0 << '\n';
            continue;
        }
        unordered_map<string,int> cnt;
        int best = 0;
        for(size_t i = 0; i + 3 <= s.size(); ++i) {
            string t = s.substr(i, 3);
            ++cnt[t];
            if(cnt[t] > best) best = cnt[t];
        }
        cout << best << '\n';
    }
    return 0;
}
