// g++ -std=c++17 -O2 solve.cpp -o solve
#include <bits/stdc++.h>
using namespace std;

int main(){
    const int MAXN = 1000;
    vector<bool> is_prime(MAXN+1, true);
    is_prime[0]=is_prime[1]=false;
    vector<int> primes;
    for(int i=2;i<=MAXN;i++){
        if(is_prime[i]){
            primes.push_back(i);
            if(1LL*i*i <= MAXN)
                for(int j=i*i;j<=MAXN;j+=i) is_prime[j]=false;
        }
    }

    int n;
    while(cin>>n){
        bool first = true;
        for(int p: primes){
            if(p>n) break;
            long long power = p;
            long long cnt = 0;
            while(power <= n){
                cnt += n / power;
                power *= p;
            }
            if(!first) cout << ' ';
            cout << cnt;
            first = false;
        }
        cout << '\n';
    }
    return 0;
}




