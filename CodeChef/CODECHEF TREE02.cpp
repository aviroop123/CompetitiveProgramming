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

const int N = 20005;
vi<int> g[N], temp;
int val[N], a[N], n, k, c;
void dfs(int u,int p,int x){
    for(int v : g[u]){
        if(v != p)
            dfs(v, u, x);
    }
    temp.clear();
    for(int v : g[u]){
        if(v != p)
            temp.pb(val[v]);
    }
    sort(all(temp));
    int vv = a[u];
    for(int i = 0; i < temp.size(); i++){
        if(vv + temp[i] > x){
            c += temp.size() - i;
            break;
        }
        else
            vv += temp[i];
    }
    val[u] = vv;
}

bool f(int x){
    c = 0;
    dfs(1, 0, x);
    return c <= k - 1;
}

signed main(){
   // freopen("inp.txt", "r", stdin);
    IO;
    cin >> n >> k;
    int maxi = 0, tot = 0;
    fr(i, 1, n){
        cin >> a[i];
        maxi = max(maxi, a[i]);
        tot += a[i];
    }
    fr(i, 1, n - 1){
        int u, v;
        cin >> u >> v;
        g[u].pb(v);
        g[v].pb(u);
    }
    int l = maxi - 1, r = tot;
    while(r - l > 1){
        int m = (l + r) >> 1;
        if(f(m)) r = m;
        else l = m;
    }
    cout << r;
    return 0;
}
