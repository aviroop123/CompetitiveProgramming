/* Solution : First, let's solve the problem for k = 0. Also, let n be odd. The second player can always make a[mid] since the opponent can remove in the opposite end. Or, the first player can choose any of a[mid-1] and a[mid+1] by doing the move on same end as first player. So, if the first player tries to maximize, then the optimal value would be max(a[mid],min(a[mid-1],a[mid+1])). If n is even, choose the endpoint for which optimal value of first player is better. If we consider k, then it boils down to range queries.
*/
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
int tr[4 * N], tr2[4 * N], tr3[4 * N];
int a[N], b[N], c[N], d[N];
void build(int nd,int s,int e, int tr[], int a[]){
	if(s == e){
		tr[nd] = a[s];
		return;
	}
	int m = (s + e) >> 1;
	build(nd << 1, s, m, tr, a);
	build(nd << 1 | 1, m + 1, e, tr, a);
	tr[nd] = max(tr[nd << 1], tr[nd << 1 | 1]);
}
int query(int nd,int s,int e,int l,int r,int tr[]){
	if(s > r || e < l) return 0;
	if(l <= s && e <= r) return tr[nd];
	int m = (s + e) >> 1;
	return max(query(nd << 1, s, m, l, r, tr), query(nd << 1 | 1, m + 1, e, l, r, tr));
}
void solve(){
	int n;
	cin >> n;
	int maxi = 0;
	fr(i, 1, n){
		cin >> a[i];
		maxi = max(maxi, a[i]);
	}
	fr(i, 2, n - 1){
		b[i] = min(a[i], max(a[i - 1], a[i + 1]));
	}
	fr(i, 2, n - 1){
		d[i] = max(a[i], min(a[i - 1], a[i + 1]));
	}
	fr(i, 2, n - 2){
		c[i] = max(d[i], d[i + 1]);
	}
	build(1, 1, n, tr, b);
	build(1, 1, n, tr2, c);
	fr(k, 0, n - 1){
		if(k == n - 1 || k == n - 2){
			cout << maxi << " ";
			continue;
		}
		int l = n - k;
		if(l & 1){
			l = (l + 1) / 2;
			cout << query(1, 1, n, l, n - l + 1, tr) << " ";
		}
		else{
			l /= 2;
			cout << query(1, 1, n, l, n - l, tr2) << " ";
		}
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
