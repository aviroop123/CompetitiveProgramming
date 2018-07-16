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
#define f80 long double
#define LOCAL 0
#define endl '\n'

typedef long long int ll;
#define int long long int

const int mod = 1e9 + 7;
const int N = 200005;
const int inf = 1e9;

unordered_map<int,int> dp[21][21];
int a[21][21];
bool vis[21][21];
int n1, m1;
void go(int n,int m){
    if(vis[n][m]) return;
    vis[n][m] = 1;
    if(n == 1 && m == 1){
        dp[1][1][a[1][1]] = 1;
        return;
    }
    if(n > 1){
        go(n - 1, m);
        for(pii x : dp[n - 1][m]){
            dp[n][m][(x.fi ^ a[n][m])] += x.se;
        }
    }
    if(m > 1){
        go(n, m - 1);
        for(pii x : dp[n][m - 1]){
            dp[n][m][(x.fi ^ a[n][m])] += x.se;
        }
    }
}
int go1(int n,int m,int val){
    if(n <= 0 || m <= 0) return 0;
    if(vis[n][m]){
        int ans = 0;
        ans += dp[n][m][val];
        return ans;
    }
    val ^= a[n][m];
    int ans = go1(n - 1, m, val);
    ans += go1(n, m - 1, val);
    return ans;
}
signed main(){
    IO;
    if(LOCAL){
        freopen("inp.txt", "r", stdin);
    }
    int k;
    cin >> n1 >> m1 >> k;
    forn(i, 1, n1)
    forn(j, 1, m1)
    cin >> a[i][j];
    forn(i, 1, n1){
        if(m1 - i + 1 <= 0)
            break;
        go(i, m1 - i + 1);
    }
    int ans = go1(n1, m1, k);
    cout << ans;
    return 0;
}
