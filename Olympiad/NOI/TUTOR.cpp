/* Solution : dp[i][j][k] -> maximum amount of money you can get when processed till time i and knowledge j and k represents the mask of which books have already been bought.
*/
#include "bits/stdc++.h"
// #include "ext/pb_ds/assoc_container.hpp"
// #include "ext/pb_ds/tree_policy.hpp"
// using namespace __gnu_pbds;
using namespace std;
typedef long long int ll;
// #define int long long
#define pb push_back
#define fi first
#define se second
#define fr(i, a, b) for(int i = a; i <= b; i++)
#define all(x) x.begin(), x.end()
#define IO ios :: sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define pii pair<int,int>
#define sz(x) (int)x.size()
const int mod = 1e9 + 7;
const int mod1 = 998244353;
typedef long double f80;

#ifndef LOCAL
#pragma GCC optimize ("O3")
#define endl '\n'
#endif

// template<typename T>
// using ordered_set = tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update>;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
ll rand(ll l, ll r){
    uniform_int_distribution<ll> uid(l, r);
    return uid(rng);
}

ll pwr(ll a,ll b, ll mod){
	a %= mod;
    int ans = 1;
    while(b){
        if(b & 1) ans = (ans * a) % mod;
        a = (a * a) % mod;
        b >>= 1;
    }
    return ans;
}

string to_string(string s) {
  return '"' + s + '"';
}

string to_string(const char* s) {
  return to_string((string) s);
}

string to_string(bool b) {
  return (b ? "true" : "false");
}

template <typename A, typename B>
string to_string(pair<A, B> p) {
  return "(" + to_string(p.first) + ", " + to_string(p.second) + ")";
}

template <typename A>
string to_string(A v) {
  bool first = true;
  string res = "{";
  for (const auto &x : v) {
    if (!first) {
      res += ", ";
    }
    first = false;
    res += to_string(x);
  }
  res += "}";
  return res;
}

void debug_out() { cerr << endl; }

template <typename Head, typename... Tail>
void debug_out(Head H, Tail... T) {
  cerr << " " << to_string(H);
  debug_out(T...);
}

#ifdef LOCAL
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#else
#define debug(...) 42
#endif

const int N = 1005;
int dp[N][N][16]; // dp[time][knowledge][mask]
int bookcost[4];
void solve(){
	fill(&dp[0][0][0], &dp[0][0][0] + N * N * 16, -1e9);
	dp[0][0][0] = 0;
	int t, lr, pr;
	cin >> t >> lr >> pr;
	fr(i, 0, 3){
		cin >> bookcost[i];
	}
	int ans = 0;
	fr(i, 0, t){
		fr(j, 0, i){
			fr(k, 0, 15){
				if(dp[i][j][k] == -1e9) continue;
				ans = max(ans, dp[i][j][k]);
				int book = __builtin_popcount(k);
				int inc = 10 + min(20, j) * pr;
				int tt = max(1, 8 / max(1, book * lr));
				// TEACH
				if(i + 2 <= t){
					dp[i + 2][j][k] = max(dp[i + 2][j][k], dp[i][j][k] + inc);
				}
				// TRAIN
				if(i + tt <= t && dp[i][j][k] >= 20){
					dp[i + tt][j + 1][k] = max(dp[i + tt][j + 1][k], dp[i][j][k] - 20);
				}
				// BUY
				fr(l, 0, 3){
					if(!(k & (1 << l)) && dp[i][j][k] >= bookcost[l]){
						dp[i + l][j][k ^ (1 << l)] = max(dp[i + l][j][k ^ (1 << l)], dp[i][j][k] - bookcost[l]);
					}
				}
			}
		}
	}
	cout << ans << endl;
}
signed main(){
    IO;
    #ifdef LOCAL
        freopen("inp.txt","r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    int t = 1;
    // cin >> t;
    fr(tt, 1, t){
    	// cout << "Case #" << tt << ": ";
        solve();
    }
    return 0;
}
