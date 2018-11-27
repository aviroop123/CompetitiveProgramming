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

const int N = 2e5 + 5;
const int LOGN = 18;
vector<int> g[N];
int dp[LOGN][N], depth[N], deg[N];
pii dfs(int u,int p,int d){
    pii ans = {u, d};
    dp[0][u] = p;
    depth[u] = depth[p] + 1;
    for(int v : g[u]){
        if(v != p){
            pii lol = dfs(v, u, d + 1);
            if(lol.se > ans.se)
                ans = lol;
        }
    }
    return ans;
}
int lca(int u,int v){
    if(depth[u] < depth[v]) swap(u, v);
    for(int k = LOGN - 1; k >= 0; k--)
        if(depth[dp[k][u]] >= depth[v]) u = dp[k][u];
    if(u == v) return u;
    for(int k = LOGN - 1; k >= 0; k--)
        if(dp[k][u] != dp[k][v]) u = dp[k][u], v = dp[k][v];
    return dp[0][u];
}
bool sp[N];
queue<int> q;
bool dfs1(int u,int p,int e){
    if(u == e){
        sp[u] = 1;
        return 1;
    }
    for(int v : g[u]){
        if(v != p){
            if(dfs1(v, u, e))
            {
                sp[u] = 1;
                return 1;
            }
        }
    }
    return 0;
}
int dist(int u,int v){
    return depth[u] + depth[v] - 2 * depth[lca(u, v)];
}
bool active[N];
vector<pair<pii,int>> vv;
void solve(){
    int n;
    cin >> n;
    fr(i, 1, n - 1){
        int u, v;
        cin >> u >> v;
        g[u].pb(v);
        g[v].pb(u);
        deg[u]++, deg[v]++;
    }
    pii e1 = dfs(1, 0, 0);
    pii e2 = dfs(e1.fi, 0, 0);
    fr(k, 1, LOGN - 1){
        fr(i, 1, n){
            dp[k][i] = dp[k - 1][dp[k - 1][i]];
        }
    }
    dfs1(e1.fi, 0, e2.fi);
    fr(i, 1, n){
        active[i] = 1;
        if(deg[i] == 1 && !sp[i]){
            q.push(i);
        }
    }
    int ans = 0;
    while(!q.empty()){
        int u = q.front();
        active[u] = 0;
        q.pop();
        int d1 = dist(u, e1.fi), d2 = dist(u, e2.fi);
        if(d1 > d2){
            vv.pb({{u, e1.fi}, u});
            ans += d1;
        }
        else{
            ans += d2;
            vv.pb({{u, e2.fi}, u});
        }
        for(int v : g[u]){
            deg[v]--;
            if(active[v] && !sp[v] && deg[v] == 1)
                q.push(v);
        }
    }
    int u = e1.fi;
    while(u != e2.fi){
        vv.pb({{u, e2.fi}, u});
        active[u] = 0;
        ans += dist(u, e2.fi);
        for(int v : g[u]){
            if(sp[v] && active[v]){
                u = v;
            }
        }
    }
    cout << ans << endl;
    for(auto it : vv){
        cout << it.fi.fi << " " << it.fi.se << " " << it.se << endl;
    }
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
