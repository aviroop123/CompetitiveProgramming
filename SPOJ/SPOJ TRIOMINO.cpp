// Solution : Whenever we place a triomino on the board, it gets divided into two boards whose endpoints may or may not be smooth.
// So dp[b1][b2][n] is the grundy value of the configuration of length n and b1, b2 represents the mask of the endpoints. Complexity: O(N^2)
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
const int N = 805;
int dp[3][3][N];
vector<int> g[3][3][N];
int go(bool b1,bool b2,int n){
	if(n < 2) return 0;
	if(n == 2){
		if(b1 && b2) return 0;
		return 1;
	}
	vector<int> &lol = g[b1][b2][n];
	if(dp[b1][b2][n] != -1) return dp[b1][b2][n];
	fr(i, 1, n - 1){
		if(i == 1){
			if(!b1)
			{
				lol.pb(go(1, b2, n - 1));
				lol.pb(go(2, b2, n - 1));
			}
		}
		else if(i == n - 1){
			lol.pb(go(b1, 0, n - 2));
		}
		else{
			lol.pb(go(b1, 0, i - 1) ^ go(1, b2, n - i));
			lol.pb(go(b1, 0, i - 1) ^ go(2, b2, n - i));
		}
	}
	swap(b1, b2);
	fr(i, 1, n - 1){
		if(i == 1){
			if(!b1)
			{
				lol.pb(go(1, b2, n - 1));
				lol.pb(go(2, b2, n - 1));
			}
		}
		else if(i == n - 1){
			lol.pb(go(b1, 0, n - 2));
		}
		else{
			lol.pb(go(b1, 0, i - 1) ^ go(1, b2, n - i));
			lol.pb(go(b1, 0, i - 1) ^ go(2, b2, n - i));
		}
	}
	swap(b1, b2);
	sort(all(lol));
	unique(all(lol));
	int val = 0;
	for(int x : lol){
		if(x == val) val++;
		else break;
	}
	return dp[b1][b2][n] = val;
}
void solve(){
	int n;
	cin >> n;
	cout << (go(0, 0, n) > 0 ? "X" : "Y") << endl;
}
signed main(){
  	IO;
  	#ifdef LOCAL
		freopen("inp.txt","r", stdin);
		// freopen("out.txt", "w", stdout);
	#endif
	// clock_t clk = clock();
	fill(&dp[0][0][0], &dp[0][0][0] + 9 * N, -1);
  	int t = 1;
  	cin >> t;
  	fr(tt, 1, t){
    	solve();
  	}
  	// cerr << endl << (double)(clock() - clk) / CLOCKS_PER_SEC;
  	return 0;
}
