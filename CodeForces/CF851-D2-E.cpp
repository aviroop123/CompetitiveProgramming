/* Solution : Same as the editorial
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
map<int,int> masks, dp;
int mex(vector<int> v){
	int val = 0;
	sort(all(v));
	unique(all(v));
	for(int x : v){
		if(x == val) val++;
		else break;
	}
	return val;
}
int grundy(int mask){
	if(mask == 1) return 0;
	if(dp.count(mask)) return dp[mask];
	int b = 0;
	int x = mask;
	while(x){
		x >>= 1, b++;
	}
	vector<int> temp;
	fr(i, 0, b - 2){
		int mask1 = mask - ((mask >> (i + 1)) << (i + 1));
		mask1 |= (mask >> (i + 1));
		temp.pb(grundy(mask1));
	}
	return dp[mask] = mex(temp);
}
int a[105];
void solve(){
	int n;
	cin >> n;
	fr(i, 1, n){
		cin >> a[i];
		for(int p = 2; p * p <= a[i]; p++){
			if(a[i] % p == 0){
				int c = 0;
				while(a[i] % p == 0)
					a[i] /= p, c++;
				masks[p] |= (1 << c);
			}
		}
		if(a[i] > 1){
			masks[a[i]] |= 2;
		}
	}
	int ans = 0;
	for(auto it : masks){
		ans ^= grundy(it.se);
	}
	cout << ((ans > 0) ? "Mojtaba" : "Arpa");
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
