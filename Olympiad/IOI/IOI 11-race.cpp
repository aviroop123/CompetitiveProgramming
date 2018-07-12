// The solution uses centroid decomposition to decompose the tree into O(n) paths. Complexity : O(n * log^2(n))

#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef long double f80;
//#define int long long int
#define fi first
#define se second
#define pb emplace_back
#define forn(i, x, y) for(int i = x; i <= y; i++)
#define vi vector
#define pii pair
#define spd ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)


const int N = 200005;
int h[N][2], l[N], sz[N];
map<ll,int> gbl[N];
vi<pii<ll,int>> vg;
bool edges[N];
vi<int> g[N];
int adj(int u,int e){
    return (h[e][0] == u) ? h[e][1] : h[e][0];
}
void dfs1(int u,int p){
    sz[u] = 1;
    for(int e: g[u]){
        if(edges[e]) continue;
        int v = adj(u, e);
        if(v == p) continue;
        dfs1(v, u);
        sz[u] += sz[v];
    }
}
int get_centroid(int u,int p,int tot){
    for(int e: g[u]){
        if(edges[e]) continue;
        int v = adj(u, e);
        if(v == p) continue;
        if(sz[v] > (tot / 2))
            return get_centroid(v, u, tot);
    }
    return u;
}
int dfs2(int u,int p,int d,ll val,map<ll,int> &gbl, vi<pii<ll,int>> &vg,int k){
    vg.pb(val, d);
    int ans = 1e7;
    if(gbl.count(k - val))
        ans = min(ans, gbl[k - val] + d);
    if(val == k)
        ans = min(ans, d);
    for(int e: g[u]){
        if(edges[e]) continue;
        int v = adj(u, e);
        if(v == p) continue;
        ans = min(ans, dfs2(v, u, d + 1, val + l[e], gbl, vg, k));
    }
    return ans;
}
int solve(int u,int k){
    dfs1(u, 0);
    int c = get_centroid(u, 0, sz[u]);
    int ans = 1e7;
    for(int e: g[c]){
        if(edges[e]) continue;
        edges[e] = 1;
        int v = adj(c, e);
        vg.clear();
        ans = min(ans, dfs2(v, 0, 1, l[e], gbl[c], vg, k));
        for(auto it: vg){
            if(gbl[c].count(it.fi))
                gbl[c][it.fi] = min(gbl[c][it.fi], it.se);
            else
                gbl[c][it.fi] = it.se;
        }
        ans = min(ans, solve(v, k));
    }
    gbl[c].clear();
    return ans;
}
signed main(){
    //freopen("inp.txt", "r", stdin);
    int n, k;
    scanf("%d %d",&n, &k);
    forn(i, 0, n - 2){
        scanf("%d %d %d", &h[i][0], &h[i][1], &l[i]);
        h[i][0]++, h[i][1]++;
        g[h[i][0]].pb(i);
        g[h[i][1]].pb(i);
    }
    int ans = solve(1, k);
    if(ans == 1e7) ans = -1;
    printf("%d", ans);
    return 0;
}
