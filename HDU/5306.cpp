#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
#define pb emplace_back
#define fi first
#define se second
const int mod = 1e9 + 7;
#define all(x) (x).begin(),(x).end()
typedef long double f80;
const int inf = 2147483647;
#define pii pair<int,int>

const int N = 1000001;
int a[N];
struct node{
    int cnt, val[2];
    ll sum;
    node(){
        cnt = sum = 0;
    }
} tr[4 * N];
int lazy[4 * N];
void update(int nd){
    int nd1 = nd << 1, nd2 = nd1 | 1;
    tr[nd].sum = tr[nd1].sum + tr[nd2].sum;
    tr[nd].cnt = 0, tr[nd].val[0] = tr[nd].val[1] = -inf;
    for(int j = 0; j < 2; j++){
        for(int i = 0; i < 2; i++){
            if(tr[nd1 + i].val[j] > tr[nd].val[0])
            {
                tr[nd].val[1] = tr[nd].val[0];
                tr[nd].val[0] = tr[nd1 + i].val[j];
                tr[nd].cnt = tr[nd1 + i].cnt;
            }
            else if(tr[nd1 + i].val[j] == tr[nd].val[0]){
                tr[nd].cnt += tr[nd1 + i].cnt;
            }
            else if(tr[nd1 + i].val[j] > tr[nd].val[1])
                tr[nd].val[1] = tr[nd1 + i].val[j];
        }
    }
}
void tag(int nd,int x){
    lazy[nd] = min(lazy[nd], x);
}
void pushdown(int nd,int s,int e){
    if(lazy[nd] >= tr[nd].val[0])
        return;
    int nd1 = nd << 1, nd2 = nd1 | 1;
    tr[nd].sum -= ll(tr[nd].val[0] - lazy[nd]) * tr[nd].cnt;
    tr[nd].val[0] = lazy[nd];
    if(s != e){
        lazy[nd1] = min(lazy[nd1], lazy[nd]);
        lazy[nd2] = min(lazy[nd2], lazy[nd]);
    }
    lazy[nd] = inf;
}
void build(int nd,int s,int e){
    lazy[nd] = inf;
    if(s == e){
        tr[nd].val[0] = a[s], tr[nd].val[1] = -inf;
        tr[nd].cnt = 1;
        tr[nd].sum = a[s];
        return;
    }
    int m = (s + e) >> 1, nd1 = nd << 1, nd2 = nd1 | 1;
    build(nd1, s, m);
    build(nd2, m + 1, e);
    update(nd);
}
struct te{
    int nd, s, e;
} q[100];
int n, m;
void update(int nd,int s,int e,int l,int r,int x){
    pushdown(nd, s, e);
    if(s > r || e < l || tr[nd].val[0] <= x) // breakdown condition
        return;
    else if(l <= s && e <= r && tr[nd].val[1] < x) // tag condition
    {
        tag(nd, x);
        pushdown(nd, s, e);
        return;
    }
    int m = (s + e) >> 1, nd1 = nd << 1, nd2 = nd1 | 1;
    update(nd1, s, m, l, r, x);
    update(nd2, m + 1, e, l, r, x);
    update(nd);
}
ll sum(int l,int r){
    int ss = 0, ee = 0;
    q[ee++] = {1, 1, n};
    ll ans = 0;
    while(ss < ee){
        auto u = q[ss++];
        if(u.s > r || u.e < l) continue;
        pushdown(u.nd, u.s, u.e);
        if(l <= u.s && u.e <= r){ ans += tr[u.nd].sum; continue; }
        int m = (u.s + u.e) >> 1;
        q[ee++] = {u.nd << 1, u.s, m};
        q[ee++] = {u.nd << 1 | 1, m + 1, u.e};
    }
    return ans;
}
int maxq(int l,int r){
    int ss = 0, ee = 0;
    q[ee++] = {1, 1, n};
    int ans = 0;
    while(ss < ee){
        auto u = q[ss++];
        if(u.s > r || u.e < l) continue;
        pushdown(u.nd, u.s, u.e);
        if(l <= u.s && u.e <= r){ ans = max(ans, tr[u.nd].val[0]); continue; }
        int m = (u.s + u.e) >> 1;
        q[ee++] = {u.nd << 1, u.s, m};
        q[ee++] = {u.nd << 1 | 1, m + 1, u.e};
    }
    return ans;
}
signed main()
{
    //freopen("inp.txt", "r", stdin);
    //ios :: sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int tt;
    scanf("%d", &tt);
    while(tt--)
    {
    scanf("%d %d", &n, &m);
    for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
    build(1, 1, n);
    while(m--){
        int t, l, r, x;
        scanf("%d %d %d", &t, &l, &r);
        if(t == 0){
            scanf("%d", &x);
            update(1, 1, n, l, r, x);
        }
        else if(t == 2)
            printf("%lld\n", sum(l, r));
        else
            printf("%d\n", maxq(l, r));
    }
    }
    return 0;
}
