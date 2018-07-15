#include<bits/stdc++.h>
using namespace std;

#define pb emplace_back
#define fi first
#define se second
#define all(x) x.begin(), x.end()
#define vi vector
#define forn(i, l, r) for(int i = l; i <= r; i++)
#define pii pair<int,int>
#define f80 long double
#define LOCAL 0

typedef long long int ll;
//#define int long long int

const int mod = 1e9 + 7;
const int N = 1000005;
const int inf = 2e9;

map<pii,int> dp[2];
pii p[72];
void add(int i2,int s2,int s3,int val){
    if(!dp[i2].count({s2,s3}))
        dp[i2][{s2,s3}] = inf;
    dp[i2][{s2,s3}] = min(dp[i2][{s2,s3}], val);
}
signed main(){
    if(LOCAL){
        freopen("inp.txt", "r", stdin);
    }
    int t;
    scanf("%d", &t);
    while(t--){
        int n;
        scanf("%d", &n);
        int tot = 0;
        forn(i, 1, n){
            scanf("%d %d", &p[i].fi, &p[i].se);
            tot += p[i].se;
        }
        sort(p + 1, p + n + 1);
        reverse(p + 1, p + n + 1);
        dp[1].clear();
        dp[1][{0,0}] = p[1].fi;
        forn(i, 2, n){
            int i1 = (i - 1) & 1, i2 = (i & 1);
            dp[i2].clear();
            for(auto it : dp[i1]){
                int val = dp[i1][it.fi];
                add(i2, it.fi.fi, it.fi.se, val);
                int val1 = val;
                if(it.fi.fi == 0)
                    val1 += p[i].fi;
                add(i2, it.fi.fi + p[i].se, it.fi.se, val1);
                val1 = val;
                if(it.fi.se == 0)
                    val1 += p[i].fi;
                add(i2, it.fi.fi, it.fi.se + p[i].se, val1);
            }
        }
        int ans = inf;
        for(auto it : dp[(n & 1)]){
            if(it.fi.fi == 0 || it.fi.se == 0) continue;
            ans = min(ans, it.se * max(it.fi.fi, max(it.fi.se, tot - it.fi.fi - it.fi.se)));
        }
        printf("%d\n", ans);
    }
    return 0;
}
