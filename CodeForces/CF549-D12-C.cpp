/* Solution : The most important observation is that in the end if the person has both 0 and 1, then he/she can willingly change the parity. Then the problem only reduces to case handling. */

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
void S(){
	cout << "Stannis";
	exit(0);
}
void D(){
	cout << "Daenerys";
	exit(0);
}
int n, k, mv1 = 0, mv2 = 0, o = 0, z = 0;
bool win(){ // returns 1 if stannis wins
	if(o <= mv2) return 0;
	if(k & 1 && z <= mv1) return 1;
	if(!(k & 1) && z <= mv2) return 0;
	if((o & 1) && !(z & 1)) return 1;
	if(z <= mv2 && !(k & 1)) return 0;
	return 1;
}
void solve(){
	cin >> n >> k;
	fr(i, 1, n){
		int x;
		cin >> x;
		if(x & 1)
			o++;
		else
			z++;
	}
	mv1 = (n - k + 1) / 2, mv2 = (n - k) / 2;
	if(mv1 == 0){
		if(o & 1) S();
		else D();
	}
	if(o <= mv2){
		D();
	}
	if(k & 1 && z <= mv1){
		S();
	}
	if(!(k & 1) && z <= mv2){
		D();
	}
	if(mv1 == mv2){
		D();
	}
	mv1--;
	if(o){
		o--;
		if(win())
			S();
		o++;
	}
	if(z){
		z--;
		if(win())
			S();
		z++;
	}
	D();
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
