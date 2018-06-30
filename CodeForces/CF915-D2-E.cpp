#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef double f80;
#define fi first
#define se second
#define pii pair<int,int>
#define pb push_back
const int mod = 1e9 + 7;

struct node{
    node *l, *r;
    unsigned char lazy: 2;
    int w;
    node(){
        l = r = NULL;
        lazy = 0;
        w = 0;
    }
} *tr;
deque<node> cache;
node *getnode(){
    cache.emplace_back();
    return &cache.back();
}
void push_down(node * &cur, int s,int e){
    if(cur -> lazy){
        cur -> w = (cur -> lazy == 1) ? e - s + 1 : 0;
        if(s != e){
            if(!cur -> l)
                cur -> l = getnode();
            cur -> l -> lazy = cur -> lazy;
            if(!cur -> r)
                cur -> r = getnode();
            cur -> r -> lazy = cur -> lazy;
        }
        cur -> lazy = 0;
    }
}
void update(node * &cur, int s,int e,int l,int r,int k){
    if(!cur)
        cur = getnode();
    push_down(cur, s, e);
    if(s > r || e < l)
        return;
    if(l <= s && e <= r){
        cur -> lazy = k;
        push_down(cur, s, e);
        return;
    }
    int m = (s + e) >> 1;
    update(cur -> l, s, m, l, r, k);
    update(cur -> r, m + 1, e, l, r, k);
    cur -> w = cur -> l -> w + cur -> r -> w;
}
signed main(){
    //freopen("inp.txt", "r", stdin);
    int n, q, l, r, k;
    scanf("%d %d", &n, &q);
    for(int i = 1; i <= q; i++){
        scanf("%d %d %d", &l, &r, &k);
        update(tr, 1, n, l, r, k);
        printf("%d\n", n - tr -> w);
    }
    return 0;
}
