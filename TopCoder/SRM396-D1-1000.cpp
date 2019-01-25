/* Solution: The problem involves finding basis vectors of a set of numbers under xor operation. The problem reduces to finding a subset of numbers s.t. any of its subset has non-zero xor value and their sum is maximum. So, just sort the numbers in reverse order and add to the gaussian set.
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
class MoreNim{
public:
	ll basis[61], basis1[61];
	vector<ll> lol;
	void add(ll x){
	ll xx = x;
	for(int i = 60; i >= 0; i--){
		if(x & (1LL << i)){
			if(!basis[i])
				{ basis[i] = x; basis1[i] = xx; return; }
			else{
				x ^= basis[i];
			}
		}
	}
	}
	ll bestSet(vector<string> a){
		fill(basis, basis + 61, 0);
		fill(basis1, basis1 + 61, 0);
		lol.clear();
		ll tot = 0;
		for(string s : a){
			ll x = 0;
			for(char ch : s){
				x = x * 10 + ch - '0';
			}
			tot += x;
			lol.pb(x);
		}
		sort(all(lol));
		reverse(all(lol));#
		for(ll x : lol) add(x);
		fr(i, 0, 60){
			tot -= basis1[i];
		}
		return tot;
	}
};
