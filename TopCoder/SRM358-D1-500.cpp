/* Solution : My solution uses the fact that after removing the multiples present in the vector, the number of elements in a set will be quite small. So, I created some random sets and added to the set while their gcd > 1.
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
class BalanceScale{
public:
	int takeWeights(vector<int> wt){
		int n = wt.size();
		vector<int> prob;
		sort(all(wt));
		int g = 0;
		for(int x : wt)
			g = __gcd(g, x);
		for(int &x : wt)
			x /= g;
		for(int x : wt){
			bool mul = 0;
			for(int y : prob){
				if(x % y == 0)
					mul = 1;
			}
			if(!mul) prob.pb(x);
		}
		n = prob.size();
		int ans = n;
		fr(i, 0, n - 1){
			fr(k, 1, 1000)
			{
				vector<int> lol = prob;
				lol.erase(lol.begin() + i);
				int val = prob[i], l = 1;
				while(val > 1){
					l++;
					int r = rand(0, sz(lol) - 1);
					val = __gcd(val, lol[r]);
					lol.erase(lol.begin() + r);
				}
				ans = min(ans, l);
			}
		}
		return ans;
	}
};
