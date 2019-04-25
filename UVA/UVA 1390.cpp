// Solution: Dp state represents the number of nodes in a component sorted by size. Transitions are quite easy.
#include "bits/stdc++.h"
// #include "ext/pb_ds/assoc_container.hpp"
// #include "ext/pb_ds/tree_policy.hpp"
// using namespace __gnu_pbds;
using namespace std;
typedef long long int ll;
#define int long long
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
#pragma GCC optimize ("O2")
#define endl '\n'
#endif

// template<typename T>
// using ordered_set = tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update>;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand(int l, int r){
    uniform_int_distribution<int> uid(l, r);
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

const int N = 35;
map<vector<int>,f80> dp;
vector<int> g[N];
bool vis[N];
int n, m;
void dfs(int u,int &c){
	vis[u] = 1;
	c++;
	for(int v : g[u]){
		if(!vis[v]){
			dfs(v, c);
		}
	}
}
int C2(int n){
	return (n * (n - 1)) / 2;
}
f80 go(vector<int> a){
	if(sz(a) == 1) return 0;
	if(dp.count(a)) return dp[a];
	f80 num = 0;
	int den = C2(n);
	fr(i, 0, sz(a) - 1){
		den -= C2(a[i]);
	}
	fr(i, 0, sz(a) - 1){
		fr(j, i + 1, sz(a) - 1){
			vector<int> lol = a;
			lol[j] += lol[i];
			swap(lol[sz(lol) - 1], lol[i]);
			lol.pop_back();
			sort(all(lol));
			num += (go(lol) + 1) * a[i] * a[j];
		}
	}
	num += C2(n) - den;
	num /= den;
	return dp[a] = num;
}
void solve(){
	cout << setprecision(10) << fixed;
	while(cin >> n)
	{
		dp.clear();
		cin >> m;
		fr(i, 1, n){
			g[i].clear();
			vis[i] = 0;
		}
		fr(i, 1, m){
			int u, v;
			cin >> u >> v;
			g[u].pb(v);
			g[v].pb(u);
		}
		vector<int> ini;
		fr(i, 1, n){
			if(!vis[i]){
				int c = 0;
				dfs(i, c);
				ini.pb(c);
			}
		}
		sort(all(ini));
		cout << go(ini) << endl;
	}
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
        solve();
    }
    return 0;
}
