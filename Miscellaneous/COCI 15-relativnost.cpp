/* Solution : Let polynomial f(x) = (b1+a1*x)(b2+a2*x)...(bn+an*x). We need sum of coefficients of x^i s.t. i >= c. So it it equal to total sum of coefficients - sum(x^i) (0 <= i < c). Total sum of coefficients = f(1). Segment tree is used for update and querying.
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
const int mod = 10007;
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
const int N = 1e5 + 5;
vector<int> tr[4 * N];
int a[N], b[N], n, m;
vector<int> mul(vector<int> a,vector<int> b){
	vector<int> c(sz(a) + sz(b), 0);
	fr(i, 0, sz(a) - 1){
		fr(j, 0, sz(b) - 1){
			c[i + j] += (a[i] * b[j]) % mod;
			if(c[i + j] >= mod) c[i + j] -= mod;
		}
	}
	c.resize(m, 0);
	return c;
}
void upd(int nd,int s,int e,int idx,int a,int b){
	if(s == e){
		tr[nd] = {b, a};
		return;
	}
	int m = (s + e) >> 1;
	if(idx <= m)
		upd(nd << 1, s, m, idx, a, b);
	else
		upd(nd << 1 | 1, m + 1, e, idx, a, b);
	tr[nd] = mul(tr[nd << 1], tr[nd << 1 | 1]);
}
vector<int> query(int nd,int s,int e,int l,int r){
	if(s > r || e < l) return {0};
	if(l <= s && e <= r) return tr[nd];
	int m = (s + e) >> 1;
	return mul(query(nd << 1, s, m, l, r), query(nd << 1 | 1, m + 1, e, l, r));
}
void solve(){
	cin >> n >> m;
	fr(i, 1, n){
		cin >> a[i];
		a[i] %= mod;
	}
	int tot = 1;
	fr(i, 1, n){
		cin >> b[i];
		b[i] %= mod;
		tot = (tot * (a[i] + b[i])) % mod;
		upd(1, 1, n, i, a[i], b[i]);
	}
	int q;
	cin >> q;
	fr(i, 1, q){
		int idx, aa, bb;
		cin >> idx >> aa >> bb;
		aa %= mod, bb %= mod;
		tot = (tot * pwr(a[idx] + b[idx], mod - 2)) % mod;
		a[idx] = aa, b[idx] = bb;
		tot = (tot * (a[idx] + b[idx])) % mod;
		upd(1, 1, n, idx, aa, bb);
		int ans = tot;
		vector<int> lol = query(1, 1, n, 1, n);
		fr(i, 0, m - 1){
			ans -= lol[i];
			if(ans < 0) ans += mod;
		}
		cout << ans << endl;
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
  	//cerr << endl << (double)(clock() - clk) / CLOCKS_PER_SEC;
  	return 0;
}
