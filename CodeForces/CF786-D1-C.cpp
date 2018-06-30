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
} *version[2 * N];
deque<node> cache;
int a[N], p[N], temp[N], n;
node *getnode(){
    cache.emplace_back();
    return &cache.back();
}
void build(node * &cur, int s,int e){
    cur = getnode();
    if(e == n + 1)
        cur -> x = n;
    if(s == e) return;
    int m = (s + e) >> 1;
    build(cur -> l, s, m);
    build(cur -> r, m + 1, e);
}
void update(node * &cur, node * &prev, int s, int e, int idx,int val){
    cur = getnode();
    cur -> x = prev -> x + val;
    if(s == e) return;
    int m = (s + e) >> 1;
    if(idx <= m){
        update(cur -> l, prev -> l, s, m, idx, val);
        cur -> r = prev -> r;
    }
    else{
        update(cur -> r, prev -> r, m + 1, e, idx, val);
        cur -> l = prev -> l;
    }
}
int query(node * &cur, int s,int e,int &k){
    if(cur -> x < k){
        k -= cur -> x;
        return n + 1;
    }
    if(s == e)
        return s;
    int m = (s + e) >> 1;
    int q = query(cur -> l, s, m, k);
    if(q == n + 1)
        q = query(cur -> r, m + 1, e, k);
    return q;
}
int get(int pp,int k){
    return query(version[2 * pp], 0, n + 1, k);
}
signed main(){
    //freopen("inp.txt", "r", stdin);
    ios :: sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n;
    for(int i = 1; i <= n; i++){
        cin >> a[i];
        temp[a[i]] = n + 1;
    }
    for(int i = n; i >= 1; i--){
        p[i] = temp[a[i]];
        temp[a[i]] = i;
    }
    build(version[2 * n + 2], 0, n + 1);
    for(int i = n; i >= 1; i--){
        update(version[2 * i + 1], version[2 * i + 2], 0, n + 1, p[i], -1);
        update(version[2 * i], version[2 * i + 1], 0, n + 1, i, 1);
    }
    for(int k = 1; k <= n; k++){
        int pp = 1, ans = 0;
        while(pp <= n){
            int j = get(pp, k + 1);
            pp = j;
            ans++;
        }
        cout << ans << " ";
    }
    return 0;
}
