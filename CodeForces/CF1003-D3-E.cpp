#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef long double f80;
#define pb emplace_back
#define fi first
#define se second
const int mod = 1e9 + 7;
const int mod1 = 101;
#define int long long int

const int N = 400005;
int depth[N], deg[N];
set<int> s;
vector<pair<int,int>> ans;
vector<int> g[N];
int n, k, d;
void dfs(vector<int> g[], int u,int p,int d,int &x,int &dd){
    if(dd < d)
        x = u, dd = d;
    for(int v: g[u])
        if(v != p)
            dfs(g, v, u, d + 1, x, dd);
}
int diameter(vector<int> g[]){
    int x = -1, d = -1, y = -1;
    dfs(g, 1, 0, 0, x, d);
    d = -1;
    dfs(g, x, 0, 0, y, d);
    return d;
}
bool check(){
    for(int i = 1; i <= n; i++)
        if(deg[i] > k)
            return 0;
    for(auto e: ans){
        g[e.fi].pb(e.se);
        g[e.se].pb(e.fi);
    }
    return diameter(g) == d;
}
signed main(){
    //freopen("inp.txt", "r", stdin);
    ios :: sync_with_stdio(0);
    cin >> n >> d >> k;
    if(d == 1){
        if(n == 2){
            cout << "YES" << endl;
            cout << 1 << " " << 2 << endl;
        }
        else{
            cout << "NO";
        }
    }
    else{
        if(k == 1 || n <= d){
            cout << "NO";
            return 0;
        }
        for(int i = 1; i <= d; i++){
            ans.pb(i, i + 1);
            depth[i] = max(i - 1, d + 1 - i);
        }
        depth[d + 1] = d;
        for(int i = 1; i <= d + 1; i++){
            if(depth[i] + 1 <= d)
            {
                s.insert(i);
            }
            deg[i] = 2;
        }
        deg[1] = deg[d + 1] = 1;
        int nn = d + 2;
        bool yes = 1;
        while(nn <= n){
            if(s.empty()){
                yes = 0;
                break;
            }
            int v = *s.begin();
            ans.pb(v, nn);
            deg[v]++;
            deg[nn]++;
            depth[nn] = depth[v] + 1;
            if(depth[nn] + 1 <= d)
                s.insert(nn);
            if(deg[v] == k)
                s.erase(v);
            nn++;
        }
        if(yes){
            if(!check())
            {
                cout << "NO";
                return 0;
            }
            cout << "YES" << endl;
            for(auto e: ans)
                cout << e.fi << " " << e.se << endl;
        }
        else
            cout << "NO" << endl;
    }
    return 0;
}
