/* Make 2^k masks which represents the sign of the ith dimension(-ve or +ve). Problem then reduces to finding the maximum and minimum value for each mask.
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
const int N = 2e5 + 5;
vector<int> b, c;
vector<int> tr[4 * N], tr2[4 * N];
int k, tot;
vector<int> max(vector<int> a, vector<int> b){
	a.resize(tot, -1e9);
	b.resize(tot, -1e9);
	fr(i, 0, tot - 1){
		a[i] = max(a[i], b[i]);
	}
	return a;
}
vector<int> min(vector<int> a, vector<int> b){
	a.resize(tot, 1e9);
	b.resize(tot, 1e9);
	fr(i, 0, tot - 1){
		a[i] = min(a[i], b[i]);
	}
	return a;
}
void upd(int nd,int s,int e,int idx){
	if(s == e){
		c.clear();
		fr(mask, 0, tot - 1){
			int val = 0;
			fr(j, 0, k - 1){
				if(mask & (1 << j))
					val += b[j];
				else
					val -= b[j];
			}
			c.pb(val);
		}
		tr[nd] = c;
		tr2[nd] = c;
		return;
	}
	int m = (s + e) >> 1;
	if(idx <= m)
		upd(nd << 1, s, m, idx);
	else
		upd(nd << 1 | 1, m + 1, e, idx);
	tr[nd] = max(tr[nd << 1], tr[nd << 1 | 1]);
	tr2[nd] = min(tr2[nd << 1], tr2[nd << 1 | 1]);
}
vector<int> query(int nd,int s,int e,int l,int r){
	if(s > r || e < l) return {};
	if(l <= s && e <= r) return tr[nd];
	int m = (s + e) >> 1;
	return max(query(nd << 1, s, m, l, r), query(nd << 1 | 1, m + 1, e, l, r));
}
vector<int> query1(int nd,int s,int e,int l,int r){
	if(s > r || e < l) return {};
	if(l <= s && e <= r) return tr2[nd];
	int m = (s + e) >> 1;
	return min(query1(nd << 1, s, m, l, r), query1(nd << 1 | 1, m + 1, e, l, r));
}
void solve(){
	int n;
	cin >> n >> k;
	tot = 1 << k;
	fr(i, 1, n){
		b.clear();
		fr(j, 0, k - 1){
			int x;
			cin >> x;
			b.pb(x);
		}
		upd(1, 1, n, i);
	}
	int q;
	cin >> q;
	fr(i, 1, q){
		int t;
		cin >> t;
		if(t == 1){
			int idx;
			cin >> idx;
			b.clear();
			fr(j, 1, k){
				int x;
				cin >> x;
				b.pb(x);
			}
			upd(1, 1, n, idx);
		}
		else{
			int l, r;
			cin >> l >> r;
			auto lol1 = query(1, 1, n, l, r);
			auto lol2 = query1(1, 1, n, l, r);
			int maxi = 0;
			fr(j, 0, tot - 1){
				maxi = max(maxi, lol1[j] - lol2[j]);
			}
			cout << maxi << endl;
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
