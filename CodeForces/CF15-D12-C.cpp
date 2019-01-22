/* Solution : The problem boils down to calculating the prefix xor of 1 to x i.e 1^2^3..^x. This can be calculated by calculating the parity of each bit. There will be periodicity when the numbers are written in binary representation.
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
int mex(vector<int> v){
	int val = 0;
	sort(all(v));
	unique(all(v));
	for(int x : v){
		if(val == x) val++;
		else break;
	}
	return val;
}
int go(int x){ // 1^2^...^x
	x++;
	int c = 2, ans = 0;
	for(int i = 0; i < 57; i++){
		int val = (x / c) * (c / 2);
		int val1 = x % c;
		if(val1 > (c / 2))
			val += val1 - (c / 2);
		if(val & 1)
			ans ^= (1LL << i);
		c <<= 1;
	}
	return ans;
}
int brute(int x){
	int ans = 0;
	fr(i, 1, x){
		ans ^= i;
	}
	return ans;
}
void solve(){
	int n;
	cin >> n;
	int ans = 0;
	fr(i, 1, n){
		int x, m;
		cin >> x >> m;
		ans ^= go(x - 1) ^ go(x + m - 1);
	}
	cout << ((ans) ? "tolik" : "bolik");
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
