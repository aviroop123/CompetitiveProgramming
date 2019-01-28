/* Solution : Choose a random element between l to r. The probability that it is a majority element is > 50% if it exists. */

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
const int N = 3e5 + 5;
const int NN = 1e4 + 5;
vector<int> g[NN];
int a[N];
void solve(){
	int n, c;
	cin >> n >> c;
	fr(i, 1, n){
		cin >> a[i];
		g[a[i]].pb(i);
	}
	const int k = 100;
	int m;
	cin >> m;
	fr(i, 1, m){
		int l, r;
		cin >> l >> r;
		int ans = 0;
		fr(j, 1, k){
			int idx = rand(l, r);
			int f = upper_bound(all(g[a[idx]]), r) - lower_bound(all(g[a[idx]]), l);
			if(2 * f > r - l + 1)
				{ ans = a[idx]; break; }
		}
		if(!ans)
			cout << "no" << endl;
		else
			cout << "yes " << ans << endl;
	}
}
signed main(){
  	IO;
  	#ifdef LOCAL
		freopen("inp.txt","r", stdin);
		// freopen("out.txt", "w", stdout);
	#endif
	clock_t clk = clock();
  	int t = 1;
  	// cin >> t;
  	fr(tt, 1, t){
    	solve();
  	}
  	cerr << endl << (double)(clock() - clk) / CLOCKS_PER_SEC;
  	return 0;
}
