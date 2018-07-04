#include<bits/stdc++.h>
using namespace std;

#define pb emplace_back
#define fi first
#define se second
#define all(x) x.begin(), x.end()
#define vi vector
#define IO ios :: sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define LOCAL 0
#define forn(i, l, r) for(int i = l; i <= r; i++)
#define pii pair<int,int>
#define f80 long double

typedef long long int ll;
//#define int long long int

const int mod = 1e9 + 7;
const int N = 60;
const int inf = 1e8;

class StampsCollection{
public:
    vi<int> g[N], a[N], p, r;
    int dp[2][2][N];
    int n, m;
    bitset<N> vis;
    void get(int j, string s){
        int x = 0;
        for(int i = 0; i < s.size(); i++){
            if(s[i] == ' ')
            {
                a[x].pb(j);
                x = 0;
            }
            else
                x = 10 * x + s[i] - '0';
        }
        a[x].pb(j);
    }
    bool dfs(int u,int p){
        r.pb(u);
        vis[u] = 1;
        for(int v: g[u]){
            if(v == p) continue;
            if(vis[v])
                return 1;
            return dfs(v, u);
        }
        return 0;
    }
    int solve(int u){
        r.clear();
        bool b = dfs(u, -1);
        if(r.size() == 1){
            return p[r[0]];
        }
        if(r.size() == 2){
            return max(p[r[0]], p[r[1]]);
        }
        dp[0][0][1] = 0;
        dp[0][1][1] = -inf;
        dp[1][0][1] = -inf;
        dp[1][1][1] = p[r[0]];
        for(int i = 2; i <= r.size(); i++){
            for(int j = 0; j < 2; j++){
                dp[1][j][i] = dp[0][j][i - 1] + p[r[i - 1]];
                dp[0][j][i] = max(dp[0][j][i - 1], dp[1][j][i - 1]);
            }
        }
        int ans = max(dp[0][0][r.size()], dp[0][1][r.size()]);
        ans = max(ans, dp[1][0][r.size()]);
        if(!b)
            ans = max(ans, dp[1][1][r.size()]);
        return ans;
    }
    int sell(int _n,vector<string> v,vector<int> _p){
        n = _n, p = _p;
        m = v.size();
        forn(i, 0, m - 1)
            get(i, v[i]);
        forn(i, 0, n - 1)
        {
            if(a[i].size() == 2)
            {
                g[a[i][0]].pb(a[i][1]);
                g[a[i][1]].pb(a[i][0]);
            }
        }
        int ans = 0;
        forn(i, 0, m - 1){
            if(!vis[i] && (g[i].size() & 1))
                ans += solve(i);
        }
        forn(i, 0, m - 1){
            if(!vis[i])
                ans += solve(i);
        }
        return ans;
    }
};
