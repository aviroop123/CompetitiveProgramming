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
const int LOGN = 19;
const int inf = 1e13;

struct node{
    node *l, *r;
    int val;
    node() : l(NULL), r(NULL), val(0) {}
} *version[N];
int a[N];
int dp[LOGN][N], depth[N];
vi<int> g[N];
int getval(node *p){
    if(p == NULL)
        return 0;
    return p -> val;
}
void update(node *cur, node *p, int s, int e,int idx){ // good
    cur -> val ++;
    if(s == e)
        return;
    int m = (s + e) >> 1;
    if(idx <= m){
        cur -> l = new node();
        if(p == NULL){
            update(cur -> l, p, s, m, idx);
        }
        else{
            cur -> l -> val = getval(p -> l);
            update(cur -> l, p -> l, s, m, idx);
            cur -> r = p -> r;
        }
    }
    else{
        cur -> r = new node();
        if(p == NULL){
            update(cur -> r, p, m + 1, e, idx);
        }
        else{
            cur -> r -> val = getval(p -> r);
            update(cur -> r, p -> r, m + 1, e, idx);
            cur -> l = p -> l;
        }
    }
    cur -> val += getval(cur -> l) + getval(cur -> r);
}
int query1(node *cur, node *p, int s, int e, int r){ // good
    if(getval(cur) - getval(p) == 0 || e < r)
        return inf;
    if(s == e)
        return s;
    int m = (s + e) >> 1;
    node *p1 = NULL, *p2 = NULL;
    if(p != NULL){
        p1 = p -> l;
        p2 = p -> r;
    }
    int q = query1(cur -> l, p1, s, m, r);
    if(q == inf)
        q = query1(cur -> r, p2, m + 1, e, r);
    return q;
}
int query2(node *cur, node *p, int s, int e, int r){ // good
    if(getval(cur) - getval(p) == 0 || s > r)
        return -inf;
    if(s == e)
        return s;
    int m = (s + e) >> 1;
    node *p1 = NULL, *p2 = NULL;
    if(p != NULL){
        p1 = p -> l;
        p2 = p -> r;
    }
    int q = query2(cur -> r, p2, m + 1, e, r);
    if(q == -inf)
        q = query2(cur -> l, p1, s, m, r);
    return q;
}
void dfs0(int u,int p){ // good
    dp[0][u] = p;
    depth[u] = depth[p] + 1;
    update(version[u], version[p], 1, inf, a[u]);
    for(int v : g[u]){
        if(v != p){
            dfs0(v, u);
        }
    }
}
int lca(int u,int v){
    if(depth[u] < depth[v])
        swap(u, v);
    for(int i = LOGN - 1; i >= 0; i--){
        if(depth[dp[i][u]] >= depth[v])
            u = dp[i][u];
    }
    if(u == v)
        return u;
    for(int i = LOGN - 1; i >= 0; i--){
        if(dp[i][u] != dp[i][v])
            u = dp[i][u], v = dp[i][v];
    }
    return dp[0][u];
}
vi<int> queries;
signed main(){
    IO;
    if(LOCAL){
        freopen("inp.txt", "r", stdin);
        //freopen("out.txt", "w", stdout);
    }
    int t;
    cin >> t;
    while(t--){
        int n, q, ans = 0;
        cin >> n >> q;
        version[0] = new node();
        forn(i, 1, n){
        g[i].clear();
        version[i] = new node();
        cin >> a[i];
        }
        forn(i, 1, n - 1){
            int u, v;
            cin >> u >> v;
            g[u].pb(v);
            g[v].pb(u);
        }
        // good
        dfs0(1, 0);
        forn(j, 1, LOGN - 1)
            forn(i, 1, n)
                dp[j][i] = dp[j - 1][dp[j - 1][i]];
        // good
        while(q--){
            queries.clear();
            int r, k;
            cin >> r >> k;
            r ^= ans;
            int lc = -1;
            forn(j, 1, k){
                int u;
                cin >> u;
                u ^= ans;
                queries.pb(u);
                if(lc == -1)
                    lc = u;
                else
                    lc = lca(lc, u);
            }
            int val = inf;
            lc = dp[0][lc];
            for(int u : queries){
                val = min(val, query1(version[u], version[lc], 1, inf, r) - r);
                val = min(val, r - query2(version[u], version[lc], 1, inf, r));
            }
            ans = val;
            cout << ans << endl;
        }
    }
    return 0;
}
