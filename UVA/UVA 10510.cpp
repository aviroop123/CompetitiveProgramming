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
const int N = 10005;
const int inf = 1e9;

vi<int> g[N], rg[N];
int tot, tt;
int t[N], color[N], low[N][2];
bitset<N> vis;
bool valid;
void dfs0(int u,vi<int> g[]){
    vis[u] = 1;
    t[u] = ++tt;
    tot++;
    for(int v : g[u]){
        if(!vis[v])
            dfs0(v, g);
    }
}
void add(int u,int val){
    if(low[u][0] >= val){
        low[u][1] = low[u][0];
        low[u][0] = val;
    }
    else if(low[u][1] > val)
        low[u][1] = val;
}
void dfs(int u){
    color[u] = 1;
    for(int v : g[u]){
        if(color[v] == 1){
            add(u, t[v]);
        }
    }
    for(int v : g[u]){
        if(!color[v]){
            dfs(v);
            add(u, low[v][0]);
            add(u, low[v][1]);
            if(low[v][1] <= t[u])
                valid = 0;
        }
        else if(color[v] == 2){
            valid = 0;
        }
    }
    color[u] = 2;
}
signed main(){
    IO;
    if(LOCAL){
        freopen("inp.txt", "r", stdin);
    }
    int t;
    cin >> t;
    while(t--){
        int n, m;
        cin >> n >> m;
        forn(i, 1, n){
            g[i].clear();
            rg[i].clear();
        }
        fill(color + 1, color + n + 1, 0);
        forn(i, 1, n)
            low[i][0] = low[i][1] = inf;
        forn(i, 1, m){
            int u, v;
            cin >> u >> v;
            u++, v++;
            g[u].pb(v);
            rg[v].pb(u);
        }
        tot = 0;
        vis.reset();
        dfs0(1, rg);
        if(tot < n)
        {
            cout << "NO" << endl;
            continue;
        }
        tot = 0;
        vis.reset();
        tt = 0;
        dfs0(1, g);
        if(tot < n){
            cout << "NO" << endl;
            continue;
        }
        valid = 1;
        dfs(1);
        if(valid)
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
    }
    return 0;
}
