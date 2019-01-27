// Solution : As in the editorial.

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
const int N = 1e5 + 5;
int a[N];
string s;
bool hadwater = 0;
int g, w, st, t; // g -> represents the amount of grass that can be converted to fly.
// w -> represents the amount of water that can be converted to fly
// st -> stamina left
// t -> time
void solve(){
	int n;
	cin >> n;
	fr(i, 1, n){
		cin >> a[i];
		a[i] *= 2;
	}
	cin >> s;
	s = '0' + s;
	fr(i, 1, n){
		if(s[i] == 'L'){
			st -= a[i];
			t += a[i];
		}
		else if(s[i] == 'W'){
			hadwater = 1;
			st += a[i];
			w += a[i];
			t += 3 * a[i];
		}
		else{
			st += a[i];
			g += a[i];
			t += 5 * a[i];
		}
		if(st < 0){
			if(hadwater){
				t += 3 * (-st);
			}
			else{
				t += 5 * (-st);
			}
			st = 0;
		}
		g = min(g, st / 2);
		w = min(w, st / 2);
	}
	if(st > 0){
		t -= 4 * g;
		st -= 2 * g;
		w = min(w, st / 2);
		t -= 2 * w;
	}
	cout << t / 2;
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
