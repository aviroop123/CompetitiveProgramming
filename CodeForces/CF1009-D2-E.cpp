#include<bits/stdc++.h>
using namespace std;

#define pb emplace_back
#define fi first
#define se second
#define all(x) x.begin(), x.end()
#define vi vector
#define IO ios :: sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define forn(i, l, r) for(int i = l; i <= r; i++)
#define pii pair<int,int>
#define f80 long double
#define LOCAL 0

typedef long long int ll;
#define int long long int

const int mod = 998244353;
const int N = 1000005;
const int inf = 1e9;

int pwr(int a,int b){
    if(b < 0)
        return 0;
    int ans = 1;
    while(b){
        if(b & 1)
            ans = (ans * a) % mod;
        a = (a * a) % mod;
        b >>= 1;
    }
    return ans;
}
int a[N];
signed main(){
    IO;
    if(LOCAL){
        freopen("inp.txt", "r", stdin);
    }
    int n;
    cin >> n;
    forn(i, 1, n){
        cin >> a[i];
        a[i] += a[i - 1];
        a[i] %= mod;
    }
    int ans = 0;
    forn(i, 1, n){
        int val = (a[i] * pwr(2, n - i - 2)) % mod;
        val = (val * (n - i - 1)) % mod;
        ans = (ans + val) % mod;
        val = (a[i] * pwr(2, n - i)) % mod;
        ans = (ans + val) % mod;
    }
    cout << ans;
    return 0;
}
