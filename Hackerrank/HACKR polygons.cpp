#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef long double f80;
#define pb emplace_back
#define fi first
#define se second
const int mod = 1e6 + 3;
#define int long long int

int fact[mod];
int max_e(int n){
    int e = 0;
    while(n){
        n /= mod;
        e += n;
    }
    return e;
}
int pwr(int a,int b){
    int ans = 1;
    while(b){
        if(b & 1)
            ans = (ans * a) % mod;
        a = (a * a) % mod;
        b >>= 1;
    }
    return ans;
}
int ff(int n){
    if(n < mod)
        return fact[n];
    int ans = (((n / mod) & 1) ? mod - 1 : 1);
    ans = (ans * fact[n % mod]) % mod;
    ans = (ans * ff(n / mod)) % mod;
    return ans;
}
int ncr(int n,int k){
    int ans = (ff(n) * pwr(ff(k), mod - 2)) % mod;
    ans = (ans * pwr(ff(n - k), mod - 2)) % mod;
    return ans;
}
int solve(int n,int k){
    if(n - 3 < k)
        return 0;
    int e1 = max_e(n - 3) - max_e(k) - max_e(n - 3 - k);
    int e2 = max_e(n + k - 1) - max_e(k) - max_e(n - 1);
    int e3 = 0;
    int k1 = k + 1;
    while(k1 % mod == 0){
        k1 /= mod;
        e3++;
    }
    if(e1 + e2 - e3 > 0)
        return 0;
    int f = pwr(k1, mod - 2);
    f = (f * ncr(n - 3, k)) % mod;
    f = (f * ncr(n + k - 1, k)) % mod;
    return f;
}
signed main(){
    //freopen("inp.txt", "r", stdin);
    ios :: sync_with_stdio(0);
    fact[0] = 1;
    for(int i = 1; i < mod; i++)
        fact[i] = (fact[i - 1] * i) % mod;
    int t;
    cin >> t;
    while(t--){
        int n, k;
        cin >> n >> k;
        cout << solve(n, k) << endl;
    }
    return 0;
}
