#include<bits/stdc++.h>
using namespace std;

#define pb emplace_back
#define fi first
#define se second
#define all(x) x.begin(), x.end()
#define vi vector
#define forn(i, l, r) for(int i = l; i <= r; i++)
#define IO ios :: sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define pii pair<int,int>
#define f80 double
#define LOCAL 0
#define endl '\n'

typedef long long int ll;
#define int long long int

const int mod = 1e9 + 7;
const int N = 200005;
const int inf = 2e9;

class SCC
{
public:
    int n,m,cnt; // cnt -> number of scc's formed
    #define N 200005
    vector<int> g[N],rg[N],sg[N]; // sg -> dag with all nodes compressed.
    int scc[N];
    bool vis[N];
    vector<int> order;
    SCC(int _n,int _m)
    {
        fill(scc,scc+N,0);
        fill(vis,vis+N,0);
        n = _n,m = _m,cnt = 0;
    }
    void add(int u,int v)
    {
        //cout << u << " " << v << endl;
        g[u].push_back(v);
        rg[v].push_back(u);
    }
    void compute()
    {
        for(int i=1;i<=n;i++)
        {
            if(!vis[i])
                dfs1(i);
        }
        fill(vis,vis+N,0);
        for(int i=n-1;i>=0;i--)
        {
            if(!vis[order[i]])
                dfs2(order[i],++cnt);
        }
    }
    void dfs1(int u)
    {
        vis[u] = 1;
        for(int v: g[u])
        {
            if(!vis[v])
                dfs1(v);
        }
        order.push_back(u);
    }
    void dfs2(int u,int c)
    {
        vis[u] = 1;
        scc[u] = c;
        for(int v: rg[u])
        {
            if(!vis[v])
                dfs2(v,c);
            if(vis[v] && c!=scc[v])
                sg[scc[v]].push_back(c);
        }
    }
    #undef N
} sc(0, 0);
int n, m;
int NOT(int a){
    return (a > m) ? a - m : a + m;
}
void XOR(int a,int b){
    sc.add(a, NOT(b));
    sc.add(b, NOT(a));
    sc.add(NOT(a), b);
    sc.add(NOT(b), a);
}
void NOT_XOR(int a,int b){
    sc.add(a, b);
    sc.add(b, a);
    sc.add(NOT(a), NOT(b));
    sc.add(NOT(b), NOT(a));
}
vi<int> b[N];
int a[N];
signed main(){
    IO;
    if(LOCAL){
        freopen("inp.txt", "r", stdin);
    }
    cin >> n >> m;
    sc.n = 2 * m;
    forn(i, 1, n)
        cin >> a[i];
    forn(i, 1, m){
        int sz;
        cin >> sz;
        forn(j, 1, sz)
        {
            int x;
            cin >> x;
            b[x].pb(i);
        }
    }
    forn(i, 1, n){
        if(!a[i]){
            XOR(b[i][0], b[i][1]);
        }
        else{
            NOT_XOR(b[i][0], b[i][1]);
        }
    }
    sc.compute();
    bool yes = 1;
    forn(i, 1, m){
        if(sc.scc[i] == sc.scc[NOT(i)])
            {yes = 0;break;}
    }
    if(yes)
        cout << "YES";
    else
        cout << "NO";
    return 0;
}
