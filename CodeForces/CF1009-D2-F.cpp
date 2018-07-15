#include<bits/stdc++.h>
using namespace std;

#define pb emplace_back
#define fi first
#define se second
#define all(x) x.begin(), x.end()
#define vi vector
#define IO ios :: sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define forn(i, l, r) for(int i = l; i <= r; i++)
#define pii pair<int,int>
#define f80 long double
#define LOCAL 0

typedef long long int ll;
//#define int long long int

const int mod = 1e9 + 7;
const int N = 1000005;
const int inf = 1e9;

vi<int> g[N];
int dom[N], lol[N], depth[N], f[N], sz[N], tt;
vi<int> cnt[N];
void dfs(int u,int p,int d){
    depth[u] = d;
    sz[u] = depth[u];
    for(int v : g[u]){
        if(v != p){
            dfs(v, u, d + 1);
            sz[u] = max(sz[u], sz[v]);
        }
    }
}
void dfs1(int u,int p){
    int h_child = -1, tot = -1;
    for(int v : g[u]){
        if(v != p && tot < sz[v]){
            tot = sz[v];
            h_child = v;
        }
    }
    int ans, mf;
    if(h_child == -1){
        lol[u] = u;
        cnt[u].pb(1);
        f[u] = 1;
        dom[u] = 0;
        return;
    }
    else{
        dfs1(h_child, u);
        ans = dom[h_child] + 1;
        mf = f[h_child];
        lol[u] = lol[h_child];
    }
    for(int v : g[u]){
        if(v != p && v != h_child)
        {
            dfs1(v, u);
            int c = 1;
            int j = cnt[lol[u]].size() - 1;
            for(int i = cnt[lol[v]].size() - 1; i >= 0; i--){
                cnt[lol[u]][j] += cnt[lol[v]][i];
                if(cnt[lol[u]][j] > mf){
                    mf = cnt[lol[u]][j];
                    ans = c;
                }
                else if(cnt[lol[u]][j] == mf)
                    ans = min(ans, c);
                c++;
                j--;
            }
        }
    }
    cnt[lol[u]].pb(1);
    if(mf == 1)
        ans = 0;
    dom[u] = ans;
    f[u] = mf;
}
signed main(){
    IO;
    if(LOCAL){
        freopen("inp.txt", "r", stdin);
    }
    int n;
    scanf("%d", &n);
    forn(i, 1, n - 1){
        int u, v;
        scanf("%d %d", &u, &v);
        g[u].pb(v);
        g[v].pb(u);
    }
    dfs(1, -1, 0);
    dfs1(1, -1);
    forn(i, 1, n)
        printf("%d ", dom[i]);
    return 0;
}
