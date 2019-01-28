/* Solution: Refer to https://docs.google.com/presentation/d/1uyDxDV90zdUeGLz22rwzuKyZ8q2Tb8DrLfR-T1NgG9w/edit#slide=id.g2042f11f10_0_192
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
inline void add(int &a,int b){
	a += b;
	a %= mod;
}
const int N = 2005;
int dp[N][N], s, e;
string x;
void solve(){
	int n;
	cin >> x;
	n = x.size();
	x = '0' + x;
	cin >> s >> e;
	if(x[1] == 'L' && e != 1)
		{ cout << 0; return; }
	dp[1][1] = 1;
	fr(i, 1, n - 1){
		fr(j, 1, i){
			if(!dp[i][j]) continue;
			if(i + 1 == s){
				// new
				if(x[i + 1] == 'R' || x[i + 1] == 'B')
					add(dp[i + 1][j + 1], dp[i][j]);
				// s = n + f
				if(x[i + 1] == 'L' || x[i + 1] == 'B'){
					add(dp[i + 1][j], (j - ((i + 1) > e)) * dp[i][j]);
					if(i + 1 == n && (j - ((i + 1) > e)) == 0)
						add(dp[i + 1][1], dp[i][1]);
				}
			}
			else if(i + 1 == e){
				// new
				add(dp[i + 1][j + 1], dp[i][j]);
				// e = f + n
				add(dp[i + 1][j], (j - ((i + 1) > s)) * dp[i][j]);
				// final step
				if(i + 1 == n && (j - ((i + 1) > s)) == 0){
					add(dp[i + 1][1], dp[i][1]);
				}
			}
			else{
				int f = j - ((i + 1) > s) - ((i + 1) > e);
				if(x[i + 1] == 'R' || x[i + 1] == 'B'){
					// new
					add(dp[i + 1][j + 1], dp[i][j]);
					// c + n
					add(dp[i + 1][j], (j - ((i + 1) > e)) * dp[i][j]);
				}
				if(x[i + 1] == 'L' || x[i + 1] == 'B'){
					// n + c
					add(dp[i + 1][j],(j - ((i + 1) > s)) * dp[i][j]);
					// s + n + f
					if(i + 1 > s && j > 1)
						add(dp[i + 1][j - 1], f * dp[i][j]);
					// f + n + e
					if(i + 1 > e && j > 1)
						add(dp[i + 1][j - 1], f * dp[i][j]);
					// f + n + f
					if(f > 1)
						add(dp[i + 1][j - 1], ((f * (f - 1)) % mod) * dp[i][j]);
					// final step
					if(i + 1 == n && j == 2){
						add(dp[i + 1][1], dp[i][2]);
					}
				}
			}
		}
	}
	cout << dp[n][1];
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
