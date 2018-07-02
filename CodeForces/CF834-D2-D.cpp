#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef double f80;
#define fi first
#define se second
#define pii pair<int,int>
#define pb push_back
const int mod = 1e9 + 7;

const int NN = 55;
const int N = 35005;
int n, k;
struct node{
    node *l, *r;
    int x;
    node(){
        l = r = NULL;
        x = 0;
    }
} *version[N];
deque<node> cache;
node * getnode(){
    cache.emplace_back();
    return &cache.back();
}
void build(node * &cur, int s,int e){
    cur = getnode();
    if(s == e) return;
    int m = (s + e) >> 1;
    build(cur -> l, s, m);
    build(cur -> r, m + 1, e);
}
void update(node * &cur, node * &p, int s,int e,int idx){
    cur = getnode();
    cur -> x = p -> x + 1;
    if(s == e)
        return;
    int m = (s + e) >> 1;
    if(idx <= m){
        update(cur -> l, p -> l, s, m, idx);
        cur -> r = p -> r;
    }
    else{
        update(cur -> r, p -> r, m + 1, e, idx);
        cur -> l = p -> l;
    }
}
int query(node * &cur, int s,int e,int l,int r){
    if(s > r || e < l || cur == NULL)
        return 0;
    else if(l <= s && e <= r)
        return cur -> x;
    int m = (s + e) >> 1;
    return query(cur -> l, s, m, l, r) + query(cur -> r, m + 1, e, l, r);
}
int a[N], rr[N], ind[N];
unordered_map<int,int> comp;
int get_dist(int l,int r){
    if(l == r) return 1;
    return query(version[l], 0, n + 1, r + 1, n + 1) - (n - r);
}
int dp[NN][N];
void computedp(int k,int l,int r,int kl,int kr){
    int m = (l + r) >> 1;
    // compute dp[k][m]
    int bk = -1, val = -1;
    int j = min(kr, m - 1);
    int d = get_dist(j + 1, m);
    for(int i = j; i >= kl; i--){
        int vall = d + dp[k - 1][i];
        if(val < vall)
            bk = i, val = vall;
        if(rr[i] > m)
            d++;
    }
    dp[k][m] = val;
    // divide & conquer
    if(l < m)
        computedp(k, l, m - 1, kl, bk);
    if(r > m)
        computedp(k, m + 1, r, bk, kr);
}
signed main(){
    //freopen("inp.txt", "r", stdin);
    ios :: sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> k;
    build(version[n + 1], 0, n + 1);
    for(int i = 1; i <= n; i++){
        cin >> a[i];
        if(!comp.count(a[i]))
        {
            int sz = comp.size();
            comp[a[i]] = sz;
        }
        a[i] = comp[a[i]];
        dp[1][i] = comp.size();
        ind[a[i]] = n + 1;
    }
    for(int i = n; i >= 1; i--)
    {
        rr[i] = ind[a[i]];
        ind[a[i]] = i;
    }
    for(int i = n; i >= 1; i--){
        update(version[i], version[i + 1], 0, n + 1, rr[i]);
    }
    for(int j = 2; j <= k; j++){
        computedp(j, 1, n, 0, n - 1);
    }
    cout << dp[k][n];
    return 0;
}
