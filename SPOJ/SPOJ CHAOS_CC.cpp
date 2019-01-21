/* Solution : The main idea is whenever you open a gate at position i, you cannot open a gate in the range [i - 2, i + 2]. So this reduces to two subgames of size i - 3 and n - i - 2. Corner cases should be taken care of. Compleity : O(N^2)

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
const int N = 3500;
int g[N];
vector<int> mex;
void solve(){
	g[1] = 1;
	g[2] = 1;
	g[3] = 1;
	fr(i, 4, N - 1){
		mex.clear();
		mex.pb(g[i - 3]);
		mex.pb(g[i - 4]);
		fr(j, 3, i - 2){
			int val = g[j - 3] ^ g[i - j - 2];
			mex.pb(val);
		}
		sort(all(mex));
		unique(all(mex));
		int val = 0;
		for(int x : mex){
			if(x == val) val++;
			else break;
		}
		g[i] = val;
	}
	int t;
	cin >> t;
	while(t--){
		int n;
		cin >> n;
		cout << ((g[n] > 0) ? "Joker" : "Bane") << endl;
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
