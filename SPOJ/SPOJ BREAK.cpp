// Solution : Create a dag with all scc's compressed. Now the solution boils down to counting the number of reachable vertex for each node.
// This can be solved by maintaining bitsets for each node where bitset[i][j] = 1 denotes that j is reachable from i. Total complexity : O(N*M/32)

#pragma GCC optimize ("Ofast")
#include "bits/stdc++.h"
#include "ext/pb_ds/assoc_container.hpp"
#include "ext/pb_ds/tree_policy.hpp"
using namespace __gnu_pbds;
using namespace std;
typedef long long int ll;
// #define int long long int
#define pb push_back
#define fi first
#define se second
#define deb cerr << "Line no." << __LINE__
#define fr(i, a, b) for(int i = a; i <= b; i++)
#define all(x) x.begin(), x.end()
#define IO ios :: sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define pii pair<int,int>
#define sz(x) (int)x.size()
const int mod = 1e9 + 7;
const int mod1 = 998244353;
typedef double f80;
#ifndef LOCAL
#define endl '\n'
#endif

template<typename T>
using ordered_set = tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update>;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand(int l, int r){
	uniform_int_distribution<int> uid(l, r);
	return uid(rng);
}
int pwr(int a,int b){
	int ans = 1;
	while(b){
		if(b & 1) ans = (ans * a) % mod;
		a = (a * a) % mod;
		b >>= 1;
	}
	return ans;
}

class SCC
{
public:
  int n, cnt; // cnt -> number of scc's formed
  vector<vector<int>> g, rg, sg, comp; // sg -> dag with all nodes compressed.
  vector<int> scc, order;
  vector<bool> vis;
  void init(int _n)
  {
    g.resize(_n + 2);
    rg.resize(_n + 2);
    sg.resize(_n + 2);
    scc.resize(_n + 2, 0);
    vis.resize(_n + 2, 0);
    comp.resize(_n + 2);
    n = _n, cnt = 0;
  }
  void add(int u,int v)
  {
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
    fill(all(vis), 0);
    for(int i = n - 1; i >= 0; i--)
    {
      if(!vis[order[i]])
        dfs2(order[i], ++cnt);
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
    comp[c].pb(u);
    for(int v: rg[u])
    {
      if(!vis[v])
        dfs2(v,c);
      if(vis[v] && c!=scc[v])
        sg[scc[v]].push_back(c);
    }
  }
};

const int N = 10005;
SCC sc;
vector<int> ans, ans1;
int lol[N];
bitset<N> val[N];
set<pii> hol;
int getval(int u){
	if(lol[u] != -1) return lol[u];
	val[u].reset();
	for(int x : sc.comp[u]){
		val[u].set(x);
	}
	for(int v : sc.sg[u]){
		getval(v);
		val[u] |= val[v];
	}
	return lol[u] = val[u].count();
}
void solve() {
	hol.clear();
	sc = SCC();
	ans.clear();
	ans1.clear();
	int n, m;
	cin >> n >> m;
	sc.init(n);
	fr(i, 1, m){
		int u, v;
		cin >> v >> u;
		if(!hol.count({u, v}) && u != v) { hol.insert({u, v}); sc.add(u, v); }
	}
	sc.compute();
	fill(lol + 1, lol + sc.cnt + 1, -1);
	int tot = -1;
	fr(i, 1, sc.cnt){
		int g = getval(i);
		if(g > tot)
			{ ans = { i }; tot = g; }
		else if(g == tot)
			{ ans.pb(i); }
	}
	for(int x : ans){
		for(int u : sc.comp[x])
			ans1.pb(u);
	}
	sort(all(ans1));
	assert(!ans1.empty());
	fr(i, 0, sz(ans1) - 2){
		cout << ans1[i] << " ";
	}
	cout << ans1.back();
}
signed main(){
  	IO;
  	#ifdef LOCAL
		freopen("inp.txt","r", stdin);
		// freopen("out.txt", "w", stdout);
	#endif
	// clock_t clk = clock();
  	int t = 1;
  	cin >> t;
  	fr(tt, 1, t){
    	solve();
    	if(tt != t)
    		cout << endl;
  	}
  	// cerr << endl << (double)(clock() - clk) / CLOCKS_PER_SEC;
  	return 0;
}
