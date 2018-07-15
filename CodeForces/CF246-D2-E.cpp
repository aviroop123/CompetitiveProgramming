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
const int N = 100005;
const int inf = INT_MAX;

map<string,int> m;
int val[N], ans[N], lol[N], depth[N], sz[N];
vector<set<int>> v[N];
vector<pii> query[N];
vi<int> g[N], roots;
void dfs0(int u,int d){
    depth[u] = d;
    sz[u] = 1;
    for(int v : g[u]){
        dfs0(v, d + 1);
        sz[u] = max(sz[u], sz[v] + 1);
    }
}
void solve(int u){
    int sz = v[lol[u]].size();
    for(pii x : query[u]){
        if(sz - 1 >= x.se){
            ans[x.fi] = v[lol[u]][sz - 1 - x.se].size();
        }
    }
}
void dfs(int u){
    int h_child = -1, tot = -1;
    for(int v : g[u]){
        if(sz[v] > tot){
            h_child = v, tot = sz[v];
        }
    }
    if(h_child == -1){
        v[u].pb();
        v[u][0].insert(val[u]);
        lol[u] = u;
        solve(u);
        return;
    }
    else{
        dfs(h_child);
        lol[u] = lol[h_child];
    }
    for(int v1 : g[u]){
        if(v1 != h_child){
            dfs(v1);
            int j = v[lol[u]].size() - 1;
            for(int i = v[lol[v1]].size() - 1; i >= 0; i--){
                for(int x : v[lol[v1]][i]){
                    v[lol[u]][j].insert(x);
                }
                j--;
            }
            v[lol[v1]].clear();
        }
    }
    v[lol[u]].pb();
    int sz = v[lol[u]].size();
    v[lol[u]][sz - 1].insert(val[u]);
    solve(u);
}
signed main(){
    IO;
    if(LOCAL){
        freopen("inp.txt", "r", stdin);
    }
    int n;
    cin >> n;
    int r;
    forn(i, 1, n){
        string s;
        cin >> s;
        if(!m.count(s))
            m[s] = m.size();
        val[i] = m[s];
        int p;
        cin >> p;
        if(p == 0)
            roots.pb(i);
        else
            g[p].pb(i);
    }
    int q;
    cin >> q;
    forn(i, 1, q){
        int v, k;
        cin >> v >> k;
        query[v].pb(i, k);
    }
    for(int r : roots)
    {
    dfs0(r, 0);
    dfs(r);
    }
    forn(i, 1, q)
        cout << ans[i] << endl;
    return 0;
}
