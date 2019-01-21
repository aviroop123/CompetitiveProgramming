/* Solution : The most crucial observation is to see the frequency of the largest value present in the array. If the freq of max element is even, then first player loses, otherwise the first player wins. this can be proved by induction. Say that the freq of max element be fm. Then, if fm is odd, we can reduce it to set the parity of the second largest element to even. f fm is even, whatever the first player does, the second player can again set the parity of second max element to even. Eventually, the 2nd max element becomes the max element.
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
const int N = 3e5 + 5;
int a[N];
map<int,int> m;
vector<pii> lol;
void solve(){
	lol.clear();
	m.clear();
	int n;
	cin >> n;
	int mx = 0;
	fr(i, 1, n){
		cin >> a[i];
		mx = max(mx, a[i]);
		if(!a[i]) continue;
		m[a[i]]++;
	}
	if(!mx){
		cout << 0 << endl;
		return;
	}
	for(auto it : m){
		lol.pb(it);
	}
	if(!(lol.back().se & 1))
	{
		cout << 0 << endl;
		return;
	}
	if(sz(lol) == 1){
		if(lol[0].se == 1)
			cout << 1 << endl;
		else
			cout << lol[0].fi * lol[0].se << endl;
		return;
	}
	if(lol.back().se > 1){
		cout << lol.back().se * lol.back().fi << endl;
		return;
	}
	if(lol.back().se == 1){
		if(lol[sz(lol) - 2].se & 1){
			cout << 1 << endl;
		}
		else{
			cout << lol[sz(lol) - 2].fi << endl;
		}
	}
}
signed main(){
  	IO;
  	#ifdef LOCAL
		freopen("inp.txt","r", stdin);
		// freopen("out.txt", "w", stdout);
	#endif
	// clock_t clk = clock();
  	int t = 1;
  	cin >> t;
  	fr(tt, 1, t){
    	solve();
  	}
  	// cerr << endl << (double)(clock() - clk) / CLOCKS_PER_SEC;
  	return 0;
}
