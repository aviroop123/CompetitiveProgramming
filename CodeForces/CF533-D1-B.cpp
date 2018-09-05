#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef long double f80;
#define int long long int
#define pb push_back
#define fi first
#define se second
#define all(x) x.begin(), x.end()
#define fr(i, a, b) for(int i = a; i <= b; i++)
#define IO ios :: sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define endl '\n'
#define vi vector

const int N = 2e5 + 5;
vi<int> g[N];
int dp[2][N], a[N], p[N];

void dfs(int u){
    int t0 = 0, t1 = -1e18;
    for(int v : g[u]){
        dfs(v);
        int t2 = max(t0 + dp[0][v], t1 + dp[1][v]);
        int t3 = max(t1 + dp[0][v], t0 + dp[1][v]);
        t0 = t2, t1 = t3;
    }
    //cout << u << " " << t0 << " " << t1 << endl;
    dp[1][u] = max(t0 + a[u], t1);
    dp[0][u] = t0;
}

signed main(){
    //freopen("inp.txt", "r", stdin);
    IO;
    int n;
    cin >> n;
    fr(i, 1, n){
        cin >> p[i] >> a[i];
        if(p[i] > 0)
            g[p[i]].pb(i);
    }
    dfs(1);
    cout << max(dp[0][1],dp[1][1]);
    return 0;
}
