// Basically we are given some trees and we have to arrange them like a toposort. So first connect the trees with a single vertex, say (n + 1). Then run a dp, dp[u] stores the number of ways to arrange the subtree of u. Now the reccurence is as follows: First fix u on the first position. Then you are left with sz[u] - 1 positions. For a child v, we choose out of these sz[u] - 1 positions, sz[v] positions and arrange the subtree of v. Complexity: O(n) + some preprocessing for calculating ncr.
#pragma GCC optimize ("Ofast")
#include "bits/stdc++.h"
#include "ext/pb_ds/assoc_container.hpp"
#include "ext/pb_ds/tree_policy.hpp"
using namespace __gnu_pbds;
using namespace std;
typedef long long int ll;
#define int long long int
#define pb push_back
#define fi first
#define se second
#define deb cerr << "Line no." << __LINE__
#define fr(i, a, b) for(int i = a; i <= b; i++)
#define aint(x) x.begin(), x.end()
#define IO ios :: sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define pii pair<int,int>
#define sz(x) (int)x.size()
const int mod = 1e9 + 7;
const int mod1 = 998244353;
typedef long double f80;
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
const int N = 1e5 + 5;
int dp[N];
vector<int> g[N];
bool root[N];
int fact[N], ifact[N], sz[N];
void dfs(int u,int p){
	sz[u] = 1;
	for(int v : g[u]){
		dfs(v, u);
		sz[u] += sz[v];
	}
}
int ncr(int n, int k){
	if(n < k || k < 0) return 0;
	int ans = (fact[n] * ifact[k]) % mod;
	return (ans * ifact[n - k]) % mod;
}
int go(int u){
	if(dp[u] != -1) return dp[u];
	int tot = sz[u] - 1;
	int ans = 1;
	for(int v : g[u]){
		ans = (ans * ((ncr(tot, sz[v]) * go(v)) % mod)) % mod;
		tot -= sz[v];
	}
	ans %= mod;
	return dp[u] = ans;
}
void solve(){
	int n, m;
	cin >> n >> m;
	fr(i, 1, n + 1) g[i].clear();
	fill(root + 1, root + n + 1, 1);
	fr(i, 1, m){
		int v, u;
		cin >> v >> u;
		g[u].pb(v);
		root[v] = 0;
	}
	fill(dp + 1, dp + n + 2, -1);
	fr(i, 1, n){
		if(root[i]){
			g[n + 1].pb(i);
		}
	}
	dfs(n + 1, 0);
	cout << go(n + 1) << endl;
}
signed main(){
  	IO;
  	#ifdef LOCAL
		freopen("inp.txt","r", stdin);
		// freopen("out.txt", "w", stdout);
	#endif
	fact[0] = 1;
	fr(i, 1, N - 1){
		fact[i] = (i * fact[i - 1]) % mod;
	}
	ifact[N - 1] = pwr(fact[N - 1], mod - 2);
	for(int i = N - 2; i >= 0; i--){
		ifact[i] = (ifact[i + 1] * (i + 1)) % mod;
	}
 	clock_t clk = clock();
  	int t = 1;
  	cin >> t;
  	fr(tt, 1, t){
    	solve();
  	}
  	cerr << endl << (double)(clock() - clk) / CLOCKS_PER_SEC;
  	return 0;
}
