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
const int N = 50005;
const int inf = INT_MAX;

multiset<int> s[N];
vi<int> g[N];
int p[N], a[N], ans[N], lol[N], sz[N], n, m;

int add(int t,int x){
    int ans = inf;
    auto it = s[t].upper_bound(x);
    if(it != s[t].end()){
        ans = min(ans, (*it) - x);
    }
    if(it != s[t].begin()){
        it--;
        ans = min(ans, x - (*it));
    }
    s[t].insert(x);
    return ans;
}
void dfs(int u){
    if(u >= n - m + 1 && u <= n) // leaf
    {
        lol[u] = u;
        s[u].insert(a[u]);
        ans[u] = inf;
        return;
    }
    int h_child = -1, tot = -1;
    for(int v : g[u]){
        if(sz[v] > tot){
            tot = sz[v], h_child = v;
        }
    }
    dfs(h_child);
    ans[u] = ans[h_child];
    lol[u] = lol[h_child];
    for(int v : g[u]){
        if(v != h_child){
            dfs(v);
            for(int x : s[lol[v]]){
                ans[u] = min(ans[u], add(lol[u], x));
            }
            s[lol[v]].clear();
        }
    }
}
void dfs0(int u){
    sz[u] = 1;
    for(int v : g[u]){
        dfs0(v);
        sz[u] += sz[v];
    }
}
signed main(){
    IO;
    if(LOCAL){
        freopen("inp.txt", "r", stdin);
    }
    cin >> n >> m;
    forn(i, 2, n)
        cin >> p[i], g[p[i]].pb(i);
    forn(i, n - m + 1, n)
        cin >> a[i];
    dfs0(1);
    dfs(1);
    forn(i, 1, n - m)
        cout << ans[i] << " ";
    return 0;
}
