#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef long double f80;
#define int long long int
#define pb push_back
#define fi first
#define se second
#define all(x) x.begin(), x.end()
#define fr(i, a, b) for(int i = a; i <= b; i++)
#define IO ios :: sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define endl '\n'
#define vi vector

const int inf = 1e9;
const int N = 500005;
int val[N], lol[N], ans[N], depth[N], sz[N];
int s[1 << 22];
int euler[N], st[N], e[N];
vi<pair<int,int>> g[N];
int h[23];
int tt;
void dfs(int u,int p, int c){
    st[u] = ++tt;
    euler[tt] = u;
    val[u] = c;
    sz[u] = 1;
    for(auto v : g[u]){
        if(v.fi != p){
            depth[v.fi] = depth[u] + 1;
            dfs(v.fi, u, (v.se ^ val[u]));
            sz[u] += sz[v.fi];
        }
    }
    e[u] = tt;
}
void dfs1(int u,int p, bool ret){
    int h_child = -1, S = 0;
    for(auto v : g[u]){
        if(v.fi != p){
            if(sz[v.fi] > S){
                S = sz[v.fi], h_child = v.fi;
            }
        }
    }
    if(h_child == -1){
        if(ret)
            s[val[u]] = max(s[val[u]], depth[u]);
        return;
    }
    for(auto v : g[u]){
        if(v.fi != p && v.fi != h_child){
            dfs1(v.fi, u, 0);
            ans[u] = max(ans[u], ans[v.fi]);
        }
    }
    dfs1(h_child, u, 1);
    ans[u] = max(ans[u], ans[h_child]);
    for(auto v : g[u]){
        if(v.fi != p && v.fi != h_child){
            for(int i = st[v.fi]; i <= e[v.fi]; i++){
                for(int j = 0; j < 23; j++){
                    int hh = (h[j] ^ val[euler[i]]);
                    ans[u] = max(ans[u], depth[euler[i]] + s[hh] - 2 * depth[u]);
                }
            }
            for(int i = st[v.fi]; i <= e[v.fi]; i++){
                s[val[euler[i]]] = max(s[val[euler[i]]], depth[euler[i]]);
            }
        }
    }
    s[val[u]] = max(s[val[u]], depth[u]);
    for(int j = 0; j < 23; j++){
        int hh = (h[j] ^ val[u]);
        ans[u] = max(ans[u], s[hh] - depth[u]);
    }
    if(!ret){
        for(int i = st[u]; i <= e[u]; i++){
            s[val[euler[i]]] = -inf;
        }
    }
}

signed main(){
    //freopen("inp.txt", "r", stdin);
    IO;
    fr(i, 1, 22){
        h[i] = 1 << (i - 1);
    }
    fr(i, 0, (1 << 22) - 1)
        s[i] = - inf;
    int n;
    cin >> n;
    fr(i, 2, n){
        int p;
        char ch;
        cin >> p >> ch;
        g[p].pb({i, 1 << (ch - 'a')});
        g[i].pb({p, 1 << (ch - 'a')});
    }
    dfs(1, 0, 0);
    dfs1(1, 0, 1);
    fr(i, 1, n){
        cout << ans[i] << " ";
    }
    return 0;
}
