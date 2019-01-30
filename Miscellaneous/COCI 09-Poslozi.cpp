/* Solution : Used A* algorithm to find the shortest path initial to final permutation. This code gives partial score of 90pts. */
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
class cmp
{
public:
	inline bool operator () (const pair<int,vector<char>> &a, const pair<int,vector<char>> &b){
		return a.fi > b.fi;
	}
};
class cmp1
{
public:
	inline bool operator () (const pair<pii,vector<char>> &a, const pair<pii,vector<char>> &b){
		return a.fi.fi + a.fi.se > b.fi.fi + b.fi.se;
	}
};
priority_queue<pair<int,vector<char>>,vector<pair<int,vector<char>>>,cmp> q; 
priority_queue<pair<pii,vector<char>>,vector<pair<pii,vector<char>>>,cmp1> q1;
vector<pii> moves;
bool check(vector<char> &v){
	fr(i, 0, sz(v) - 1){
		if(v[i] != i + 1) return 0;
	}
	return 1;
}
int dp[15][15];
map<ll,int> dist2, dist;
ll hh(vector<char> &v){
	ll h = 0;
	for(char ch : v){
		h = (h * mod1 + ch) % mod;
	}
	return h;
}
int good_approx(vector<char> v){
	int n = sz(v);
	ll h1 = hh(v);
	q.push({0, v});
	dist2[h1] = 0;
	while(!q.empty()){
		auto y = q.top();
		q.pop();
		auto v = y.se;
		ll h1 = hh(v);
		int d = y.fi;
		if(y.fi > dist2[h1]) continue;
		if(check(v)) return d;
		fr(i, 0, n - 1){
			fr(j, 0, n - 1){
				if(i == j) continue;
				if(dp[i][j] == 1e9) continue;
				int dd = d + 2 * dp[i][j] - 1;
				if(v[i] == i + 1 && v[j] == j + 1) continue;
				if(v[i] == j + 1 || v[j] == i + 1){
					swap(v[i], v[j]);
					ll h1 = hh(v);
					if(!dist2.count(h1) || dist2[h1] > dd)
						dist2[h1] = dd, q.push({dd, v});
					swap(v[i], v[j]);
				}
			}
		}
	}
}
int h_value(vector<char> &v){ // minimum number of moves to make the permutation identity permutation
	int ret = 0;
	fr(i, 0, sz(v) - 1){
		ret += (v[i] != i + 1);
	}
	return (ret + 1) / 2;
}
vector<int> rev;
int solve(vector<char> v,int cutoff){
	dist2.clear();
	ll h1 = hh(v);
	q1.push({{0, dist[h1] = h_value(v)}, v});
	while(!q1.empty()){
		auto u = q1.top();
		q1.pop();
		auto v = u.se;
		ll h1 = hh(v);
		int d = u.fi.fi;
		if(dist[h1] < u.fi.fi + u.fi.se) continue;
		if(check(v)) return d;
		int c = 0;
		for(pii x : moves){
			c++;
			swap(v[x.fi], v[x.se]);
			ll h1 = hh(v);
			int h = h_value(v);
			int f = h + d + 1;
			if(f <= cutoff)
				if(!dist.count(h1) || dist[h1] > f){
					dist[h1] = f;
					q1.push({{d + 1, h}, v});
				}
			swap(v[x.fi], v[x.se]);
		}
	}
	assert(0);
}
void solve(){
	int n, m;
	cin >> n >> m;
	vector<char> v;
	fr(i, 1, n){
		int x;
		cin >> x;
		v.pb(x);
	}
	fr(i, 0, n - 1){
		fr(j, 0, n - 1){
			if(i == j) dp[i][j] = 0;
			else dp[i][j] = 1e9;
		}
	}
	fr(i, 1, m){
		int x, y;
		cin >> x >> y;
		x--, y--;
		if(x > y) swap(x, y);
		dp[x][y] = dp[y][x] = 1;
		moves.pb({x, y});
	}
	fr(k, 0, n - 1){
		fr(i, 0, n - 1){
			fr(j, 0, n - 1){
				if(dp[i][k] + dp[k][j] < dp[i][j])
					dp[i][j] = dp[i][k] + dp[k][j];
			}
		}
	}
	int d = good_approx(v);
	cout << solve(v, d);
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
