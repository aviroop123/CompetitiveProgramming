/* Solution : It's obvious that some losing states are those in which there are no coins on odd depth, because now, if some player chooses a node and moves some coins up, then the opponent would move the same coins further up, which by induction becomes another losing state. Now, we can imagine the number of coins on odd depth as separate nim games. The first person to finish all the coins on odd depth wins. The querying part is quite simple.
*/

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
const int N = 5e4 + 5;
int dp[N][2], s[N], e[N], depth[N], par[N], tt;
vector<int> g[N];
void dfs(int u,int p){
	par[u] = p;
	s[u] = ++tt;
	for(int v : g[u]){
		if(v != p){
			depth[v] = depth[u] + 1;
			dfs(v, u);
			dp[u][0] ^= dp[v][1];
			dp[u][1] ^= dp[v][0];
		}
	}
	e[u] = tt;
}
void solve(){
	int n, q;
	cin >> n;
	fr(i, 1, n){
		cin >> dp[i][0];
	}
	fr(i, 1, n - 1){
		int u, v;
		cin >> u >> v;
		g[u].pb(v);
		g[v].pb(u);
	}
	cin >> q;
	dfs(1, 0);
	while(q--){
		int u, v;
		cin >> u >> v;
		if(s[v] >= s[u] && e[v] <= e[u])
			cout << "INVALID" << endl;
		else{
			int ans = dp[1][1];
			if(depth[u] & 1)
				ans ^= dp[u][0];
			else
				ans ^= dp[u][1];
			if(depth[v] & 1)
				ans ^= dp[u][1];
			else
				ans ^= dp[u][0];
			if(ans)
				cout << "YES" << endl;
			else
				cout << "NO" << endl;
		}
	}
}
signed main(){
  	IO;
  	#ifdef LOCAL
		freopen("inp.txt","r", stdin);
		// freopen("out.txt", "w", stdout);
	#endif
	// clock_t clk = clock();
  	int t = 1;
  	// cin >> t;
  	fr(tt, 1, t){
    	solve();
  	}
  	// cerr << endl << (double)(clock() - clk) / CLOCKS_PER_SEC;
  	return 0;
}
