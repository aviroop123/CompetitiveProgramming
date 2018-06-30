#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef double f80;
#define fi first
#define se second
#define pii pair<int,int>
#define pb push_back
const int mod = 1e9 + 7;

const int N = 100005;
struct node{
    int x;
    node *l, *r;
    node(){
        l = r = NULL;
        x = 0;
    }
} *version[N];
deque<node> cache;
int a[N], p[N], temp[N], n;
node *getnode(){
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
void update(node * &cur, node * &prev, int s, int e, int idx){
    cur = getnode();
    cur -> x = prev -> x + 1;
    if(s == e) return;
    int m = (s + e) >> 1;
    if(idx <= m){
        update(cur -> l, prev -> l, s, m, idx);
        cur -> r = prev -> r;
    }
    else{
        update(cur -> r, prev -> r, m + 1, e, idx);
        cur -> l = prev -> l;
    }
}
int query(node * &cur, int s,int e,int l,int r){
    if(s > r || l > r)
        return 0;
    else if(l <= s && e <= r)
        return cur -> x;
    int m = (s + e) >> 1;
    return query(cur -> l, s, m, l, r) + query(cur -> r, m + 1, e, l, r);
}
int getdist(int pp,int k){
    int val = query(version[n], 0, n, 0, pp - 1) - pp + 1;
    if(val <= k)
        return n;
    int l = pp, r = n;
    while(r - l > 1){
        int m = (l + r) >> 1;
        val = query(version[m], 0, n, 0, pp - 1) - pp + 1;
        if(val <= k)
            l = m;
        else
            r = m;
    }
    return l;
}
signed main(){
    //freopen("inp.txt", "r", stdin);
    ios :: sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n;
    for(int i = 1; i <= n; i++){
        cin >> a[i];
        p[i] = temp[a[i]];
        temp[a[i]] = i;
    }
    build(version[0], 0, n);
    for(int i = 1; i <= n; i++)
        update(version[i], version[i - 1], 0, n, p[i]);
    for(int k = 1; k <= n; k++){
        int pp = 1;
        int ans = 0;
        while(pp <= n){
            int j = getdist(pp, k);
            pp = j + 1;
            ans++;
        }
        cout << ans << " ";
    }
    return 0;
}
