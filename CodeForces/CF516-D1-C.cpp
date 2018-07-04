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

#define int long long int
//typedef long long int ll;

typedef pair<int,int> pii;
typedef long double f80;

const int mod = 1e9 + 7;
const int N = 200005;

int val[N], val1[N], d[N], h[N];
pii tr[4 * N], tr1[4 * N];
pii merge(pii a, pii b){
    if(a.fi < b.fi)
        return b;
    return a;
}
void build(int nd,int s,int e){
    if(s == e){
        tr[nd] = {val[s], s};
        tr1[nd] = {val1[s], s};
        return;
    }
    int m = (s + e) >> 1, nd1 = nd << 1, nd2 = nd1 | 1;
    build(nd1, s, m);
    build(nd2, m + 1, e);
    tr[nd] = merge(tr[nd1], tr[nd2]);
    tr1[nd] = merge(tr1[nd1], tr1[nd2]);
}
pii query(int nd,int s,int e,int l,int r,bool k){
    if(s > r || e < l || l > r)
        return {-1e16, 0};
    else if(l <= s && e <= r)
        return ((k) ? tr[nd] : tr1[nd]);
    int m = (s + e) >> 1, nd1 = nd << 1, nd2 = nd1 | 1;
    return merge(query(nd1, s, m, l, r, k), query(nd2, m + 1, e, l, r, k));
}
main(){
    IO;
    if(LOCAL){
        freopen("inp.txt", "r", stdin);
    }
    int n, m;
    cin >> n >> m;
    forn(i, 1, n)
        cin >> d[i], d[i + n] = d[i];
    forn(i, 1, n)
        cin >> h[i], h[i + n] = h[i];
    n <<= 1;
    forn(i, 1, n)
        val[i] = 2 * h[i] + d[i - 1], val1[i] = 2 * h[i] - d[i - 1], d[i] += d[i - 1];
    build(1, 1, n);
    while(m--){
        int u, v, uu, vv;
        cin >> u >> v;
        if(u <= v)
            uu = v + 1, vv = u + n / 2 - 1;
        else
            uu = v + 1, vv = u - 1;
        pii q = query(1, 1, n, uu, vv, 1);
        pii q1 = merge(query(1, 1, n, uu, q.se - 1, 0), query(1, 1, n, q.se + 1, vv, 0));
        pii q2 = query(1, 1, n, uu, vv, 0);
        pii q3 = merge(query(1, 1, n, uu, q2.se - 1, 1), query(1, 1, n, q2.se + 1, vv, 1));
        cout << max(q.fi + q1.fi, q2.fi + q3.fi) << endl;
    }
    return 0;
}
