// Blog: https://cp-algorithms.com/graph/bridge-searching-online.html
#pragma GCC optimize ("Ofast")
#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
#define int long long int
#define pb push_back
#define fi first
#define se second
#define fr(i, a, b) for(int i = a; i <= b; i++)
#define all(x) x.begin(), x.end()
#define IO ios :: sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define pii pair<int,int>
const int mod = 1e9 + 7;
const int mod1 = 998244353;
typedef long double f80;
#ifndef LOCAL
#define endl '\n'
#endif
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

vector<int> poly;
vector<int> mul(vector<int> p1, vector<int> p2){
    vector<int> c(p1.size() + p2.size() - 1, 0);
    fr(i, 0, p1.size() - 1){
        fr(j, 0, p2.size() - 1){
            c[i + j] += (p1[i] * p2[j]) % mod;
            c[i + j] %= mod;
        }
    }
    return c;
}
bool lucky(int x){
    while(x){
        if(x % 10 != 4 && x % 10 != 7) return 0;
        x /= 10;
    }
    return 1;
}
const int N = 1e5 + 5;
int a[N], fact[N], ifact[N];
map<int,int> m;
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
int C(int n,int k){
    if(n < k) return 0;
    int ans = (fact[n] * ifact[k]) % mod;
    return (ans * ifact[n - k]) % mod;
}
void solve(){
    fact[0] = 1;
    fr(i, 1, N - 1){
        fact[i] = (i * fact[i - 1]) % mod;
    }
    ifact[N - 1] = pwr(fact[N - 1], mod - 2);
    for(int i = N - 2; i >= 0; i--){
        ifact[i] = (ifact[i + 1] * (i + 1)) % mod;
    }
    int n, k;
    cin >> n >> k;
    int tot = 0;
    fr(i, 1, n){
        cin >> a[i];
        if(lucky(a[i]))
            m[a[i]]++, tot++;
    }
    poly = {1};
    for(auto it : m)
        poly = mul(poly, {1, it.se});
    int ans = 0;
    for(int i = 0; i < min((int)poly.size(), k + 1); i++){
        ans += (C(n - tot, k - i) * poly[i]) % mod;
        ans %= mod;
    }
    cout << ans;
}
signed main()
{
    IO;
    #ifdef LOCAL
     freopen("inp.txt", "r", stdin);
     // freopen("out.txt", "w", stdout);
    #endif
    clock_t clk = clock();
    int t;
    // cin >> t;
    t = 1;
    fr(i, 1, t){
        solve();
    }
    cerr << endl << setprecision(10) << fixed << (double)(clock() - clk) / CLOCKS_PER_SEC;
    return 0;
}
