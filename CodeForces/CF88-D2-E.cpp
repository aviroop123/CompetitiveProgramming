/* Solution : The only important observation that I came up was that the number of possible k's is a divisor of 2 * n. Say the piles were divided into k piles. So, the sizes of piles will be x, x + 1, ... x + k - 1. Summing this up, we get k*x+k(k-1)/2, which must be equal to n. So, k*(2*x+k-1)=2*n. Now, most of the k's will be redundant. So just brute forcing over all k's will be enough to pass t.l.
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
const int N = 2e5 + 5;
pii dp[N];
vector<int> divi[N];
vector<int> temp[N];
pii go(int n){
	if(!n) return {0, -1};
	if(dp[n].fi != -1) return dp[n];
	int g1 = -1;
	for(int k : divi[2 * n]){
		int x = (2 * n) / k + 1 - k;
		if(x <= 0) break;
		if(x & 1) continue;
		x >>= 1;
		int ans = 0;
		for(int j = x; j < x + k; j++)
			ans ^= go(j).fi;
		if(!ans && g1 == -1) g1 = k;
		temp[n].pb(ans);
	}
	return dp[n] = {mex(temp[n]), g1};
}
void solve(){
	fill(dp, dp + N, pii{-1, -1});
	int n;
	cin >> n;
	fr(i, 2, 2 * n){
		for(int j = i; j <= 2 * n; j += i){
			divi[j].pb(i);
		}
	}
	cout << go(n).se << endl;
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
