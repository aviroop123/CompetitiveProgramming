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
int rand(int l, int r){
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}
const int N = 2e5 + 5;
int lazy[4 * N], tr[4 * N];
int a[N], b[N], c[N];
void build(int nd,int s,int e){
    if(s == e){
        tr[nd] = b[s];
        return;
    }
    int m = (s + e) >> 1;
    build(nd << 1, s, m);
    build(nd << 1 | 1, m + 1, e);
    tr[nd] = min(tr[nd << 1], tr[nd << 1 | 1]);
}
void push_down(int nd,int s,int e){
    if(lazy[nd]){
        tr[nd] += lazy[nd];
        if(s != e){
            lazy[nd << 1] += lazy[nd];
            lazy[nd << 1 | 1] += lazy[nd];
        }
        lazy[nd] = 0;
    }
}
void update(int nd,int s,int e,int l,int r,int x){
    push_down(nd, s, e);
    if(s > r || e < l) return;
    if(l <= s && e <= r){
        lazy[nd] += x;
        push_down(nd, s, e);
        return;
    }
    int m = (s + e) >> 1;
    update(nd << 1, s, m, l, r, x);
    update(nd << 1 | 1, m + 1, e, l, r, x);
    tr[nd] = min(tr[nd << 1], tr[nd << 1 | 1]);
}
vector<pii> g[N];
void build1(int nd,int s,int e){
    if(s == e){
        tr[nd] = a[s] + c[s];
        return;
    }
    int m = (s + e) >> 1;
    build1(nd << 1, s, m);
    build1(nd << 1 | 1, m + 1, e);
    tr[nd] = min(tr[nd << 1], tr[nd << 1 | 1]);
}
void update1(int nd,int s,int e,int idx,int x){
    if(s == e){
        a[s] = x;
        tr[nd] = x + c[s];
        return;
    }
    int m = (s + e) >> 1;
    if(idx <= m)
        update1(nd << 1, s, m, idx, x);
    else
        update1(nd << 1 | 1, m + 1, e, idx, x);
    tr[nd] = min(tr[nd << 1], tr[nd << 1 | 1]);
}

void solve(){
    int n, m, q;
    cin >> n >> m >> q;
    fr(i, 1, n - 1){
        cin >> a[i] >> b[i];
    }
    build(1, 0, n - 1);
    fr(i, 1, m){
        int x, y, z;
        cin >> x >> y >> z;
        g[x].pb({y, z});
    }
    fr(i, 1, n){
        for(pii x : g[i]){
            update(1, 0, n - 1, 0, x.fi - 1, x.se);
        }
        c[i] = tr[1];
    }
    build1(1, 1, n);
    cout << tr[1] << endl;
    fr(i, 1, q){
        int v, x;
        cin >> v >> x;
        update1(1, 1, n, v, x);
        cout << tr[1] << endl;
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
