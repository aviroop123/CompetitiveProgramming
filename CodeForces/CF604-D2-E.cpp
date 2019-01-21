/* Solution : When n is small just hardcode the solution, otherwise when n is odd, the person always loses except n = 1 and 3. Otherwise if k is odd, we always reach grundy = 0 so grundy(n) = mex(grundy(n - 1),0), else if k is odd, grundy(n) = mex(grundy(n/2), grundy(n - 1)).
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
const int N = 100005;
int g[N];
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
int go(int n){
	if(n < N) return g[n];
	if(n & 1) return 0;
	return mex({go(n / 2), 0});
}
int go1(int n){
	if(n < N) return g[n];
	if(n & 1) return 0;
	return mex({0, go(n - 1)});
}
void solve(){
	int n, k;
	cin >> n >> k;
	k &= 1;
	fr(i, 1, N - 1){
		if(i & 1)
		g[i] = mex({g[i - 1]});
		else if(k & 1)
		g[i] = mex({g[i - 1], g[i / 2]});
		else
		g[i] = mex({g[i - 1], 0});
	}
	int ans = 0;
	if(k == 1)
	{
		fr(i, 1, n){
			int x;
			cin >> x;
			ans ^= go(x);
		}
	}
	else{
		fr(i, 1, n){
			int x;
			cin >> x;
			ans ^= go1(x);
		}
	}
	cout << ((ans) ? "Kevin" : "Nicky");
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
