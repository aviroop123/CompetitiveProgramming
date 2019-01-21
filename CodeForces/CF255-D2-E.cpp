/* Solution : The main observation is that the grundy numbers upto 10^6 is quite small, so to calculate the mex of grundy numbers in a range, we can directly brute force to check whether there exist a particular value in the range. My solution was based on merging sets through a segtree and calculating mex after merging. The number of elements after merging would be quite small, so brute force would work.
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
const int N = 1e6;
int g[N];
set<int> tr[4 * N];
void update(int nd,int s,int e,int idx,int val){
	tr[nd].insert(val);
	if(s == e) return;
	int m = (s + e) >> 1;
	if(idx <= m) update(nd << 1, s, m, idx, val);
	else update(nd << 1 | 1, m + 1, e, idx, val);
}
vector<int> glob;
void mex(int nd,int s,int e,int l,int r){
	if(s > r || e < l || l > r) return;
	if(l <= s && e <= r){
		for(int x : tr[nd]) glob.pb(x);
		return;
	}
	int m = (s + e) >> 1;
	mex(nd << 1, s, m, l, r);
	mex(nd << 1 | 1, m + 1, e, l, r);
}
int getmex(){
	sort(all(glob));
	unique(all(glob));
	int val = 0;
	for(int x : glob){
		if(val == x) val++;
		else break;
	}
	return val;
}
void solve(){
	update(1, 1, N - 1, 1, 0);
	fr(i, 2, N - 1){
		int r = sqrtl(i);
		int l = ceil(sqrtl(sqrtl(i)));
		glob.clear();
		mex(1, 1, N - 1, l, r);
		g[i] = getmex();
		update(1, 1, N - 1, i, g[i]);
	}
	int n;
	cin >> n;
	int val = 0;
	fr(i, 1, n){
		int x;
		cin >> x;
		if(x < N) val ^= g[x];
		else
		{
			int r = sqrtl(x);
			int l = ceil(sqrtl(sqrtl(x)));
			glob.clear();
			mex(1, 1, N, l, r);
			val ^= getmex();
		}
	}
	cout << (val ? "Furlo" : "Rublo");
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
