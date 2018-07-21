#include<bits/stdc++.h>
using namespace std;

#define pb emplace_back
#define fi first
#define se second
#define all(x) x.begin(), x.end()
#define vi vector
#define forn(i, l, r) for(int i = l; i <= r; i++)
#define IO ios :: sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define pii pair<int,int>
#define f80 double
#define LOCAL 0
#define endl '\n'

typedef long long int ll;
#define int long long int

const int mod = 1e9 + 7;
const int N = 2000005;
const int inf = 2e9;

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
int fact[N], ifact[N];
int ncr(int n,int r){
    int ans = (fact[n] * ifact[n - r]) % mod;
    return (ans * ifact[r]) % mod;
} 
signed main(){
    IO;
    if(LOCAL){
        freopen("inp.txt", "r", stdin);
    }
    int t;
    cin >> t;
    fact[0] = 1;
    forn(i, 1, N - 1){
        fact[i] = (fact[i - 1] * i) % mod;
    }
    ifact[N - 1] = pwr(fact[N - 1], mod - 2);
    for(int i = N - 2; i >= 0; i--){
        ifact[i] = (ifact[i + 1] * (i + 1)) % mod;
    }
    while(t--){
        int n;
        cin >> n;
        int ans = (n * ncr(2 * n - 1, n - 1)) % mod;
        cout << ans << endl;
    }
    return 0;
}
