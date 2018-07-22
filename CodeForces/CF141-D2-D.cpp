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
const int N = 200005;
const int inf = 2e9;

struct node{
    node *l, *r;
    int val, id;
    node():l(NULL), r(NULL), val(inf), id(0){}
} *tr1, *tr2;
void update(node * &cur, int s,int e,int idx,int val,int id){
    if(!cur)
        cur = new node();
    if(cur -> val >= val){
        cur -> val = val;
        cur -> id = id;
    }
    if(s == e)
        return;
    int m = (s + e) >> 1;
    if(idx <= m)
        update(cur -> l, s, m, idx, val, id);
    else
        update(cur -> r, m + 1, e, idx, val, id);
}
pii query(node * &cur, int s,int e,int l,int r){
    if(s > r || e < l || !cur)
        return {inf, 0};
    if(l <= s && e <= r)
        return {cur -> val, cur -> id};
    int m = (s + e) >> 1;
    pii q1 = query(cur -> l, s, m, l, r);
    pii q2 = query(cur -> r, m + 1, e, l, r);
    if(q1.fi <= q2.fi)
        return q1;
    return q2;
}
pii query(node *cur, int l,int r){
    return query(cur, 0, inf, l, r);
}
void update(node *cur, int idx, int val, int id){
    update(cur, 0, inf, idx, val, id);
}
int x[N], d[N], t[N], p[N];
pii z[N];
vector<int> ans;
signed main(){
    IO;
    if(LOCAL){
        freopen("inp.txt", "r", stdin);
        //freopen("out.txt", "w", stdout);
    }
    int n, l;
    cin >> n >> l;
    tr1 = new node();
    tr2 = new node();
    update(tr1, 0, 0, 0);
    update(tr2, 0, 0, 0);
    forn(i, 1, n){
        cin >> x[i] >> d[i] >> t[i] >> p[i];
        z[i].fi = x[i] + d[i], z[i].se = i;
    }
    sort(z + 1, z + n + 1);
    forn(j, 1, n){
        int i = z[j].se;
        if(x[i] - p[i] >= 0){
            pii q1 = query(tr2, x[i] - p[i], inf);
            q1.fi -= (x[i] - p[i]);
            pii q2 = query(tr1, 0, x[i] - p[i]);
            q2.fi += (x[i] - p[i]);
            int id, val;
            if(q1.fi <= q2.fi)
                val = q1.fi, id = q1.se;
            else
                val = q2.fi, id = q2.se;
            val += t[i] + p[i];
            update(tr1, x[i] + d[i], val - x[i] - d[i], i);
            update(tr2, x[i] + d[i], val + x[i] + d[i], i);
        }
    }
    pii q = query(tr1, 0, l);
    q.fi += l;
    cout << q.fi << endl;
    int pp = q.se;
    while(pp != 0){
        ans.pb(pp);
        int y = x[pp] - p[pp];
        pii q1 = query(tr1, 0, y);
        q1.fi += y;
        pii q2 = query(tr2, y, inf);
        q2.fi -= y;
        if(q1.fi <= q2.fi)
            pp = q1.se;
        else
            pp = q2.se;
    }
    reverse(all(ans));
    cout << ans.size() << endl;
    for(int x : ans)
        cout << x << " ";
    return 0;
}
