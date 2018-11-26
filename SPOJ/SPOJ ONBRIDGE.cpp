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

const int N = 5e4 + 5;
int dsu[N], dsub[N], par[N], sz[N], bridges;
void init(int n){
    bridges = 0;
    fr(i, 1, n){
        dsu[i] = i;
        dsub[i] = i;
        par[i] = -1;
        sz[i] = 1;
    }
}
int rootb(int u){
    if(u == -1) return -1;
    return (dsub[u] == u) ? u : (dsub[u] = rootb(dsub[u]));
}
int root(int u){
    u = rootb(u);
    return (dsu[u] == u) ? u : (dsu[u] = root(dsu[u]));
}
void makeroot(int u){
    int prev = -1, r = u;
    while(u != -1){
        int p = rootb(par[u]);
        par[u] = prev;
        dsu[u] = r;
        prev = u;
        u = p;
    }
    sz[r] = sz[u];
}
vector<int> p1, p2;
void mergepath(int u,int v){
    int uu = u, vv = v;
    while(uu != -1){
        p1.pb(uu);
        uu = rootb(par[uu]);
    }
    while(vv != -1){
        p2.pb(vv);
        vv = rootb(par[vv]);
    }
    reverse(all(p1));
    reverse(all(p2));
    int lca = -1;
    for(int i = 0; i < min(p1.size(), p2.size()); i++){
        if(p1[i] == p2[i]) lca = p1[i];
        else break;
    }
    assert(lca != -1);
    while(u != lca){
        dsub[u] = lca;
        u = rootb(par[u]);
        bridges--;
    }
    while(v != lca){
        dsub[v] = lca;
        v = rootb(par[v]);
        bridges--;
    }
    p1.clear();
    p2.clear();
}
void add(int u,int v){
    u = rootb(u), v = rootb(v);
    if(u == v) return; // same bcc ... no change
    int cu = root(u), cv = root(v);
    if(cu == cv){ // same component ... merge the cycle into 1 node
        mergepath(u, v);
    }
    else{
        bridges++;
        if(sz[cu] > sz[cv]){
            swap(cu, cv);
            swap(u, v);
        }
        makeroot(u);
        par[u] = dsu[u] = v;
        sz[cv] += sz[u];
    }
}
void solve(){
    int n, m;
    cin >> n >> m;
    init(n);
    fr(i, 1, m){
        int u, v;
        cin >> u >> v;
        u++, v++;
        add(u, v);
        cout << bridges << endl;
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
    cin >> t;
    // t = 1;
    fr(i, 1, t){
        solve();
    }
    cerr << endl << setprecision(10) << fixed << (double)(clock() - clk) / CLOCKS_PER_SEC;
    return 0;
}
