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

const int N = 5005;
const int NN = 1e5 + 5;
int bit[N][N];
int lol[NN];
int X1[NN], X2[NN], Y1[NN], Y2[NN];
void upd(int x,int y,int val){
	for(int i = x; i < N; i += (i & (-i))){
		for(int j = y; j < N; j += j & (-j)){
			bit[i][j] += val;
		}
	}
}
int sum(int x,int y){
	int s = 0;
	for(int i = x; i > 0; i -= i & (-i)){
		for(int j = y; j > 0; j -= j & (-j)){
			s += bit[i][j];
		}
	}
	return s;
}
void solve(){
	int q;
	cin >> q;
	fr(i, 1, q){
		int t;
		cin >> t;
		if(t == 1){
			int x1, y1, x2, y2;
			cin >> x1 >> y1 >> x2 >> y2;
			lol[i] = rand(1, 1e13);
			if(x1 > x2) swap(x1, x2);
			if(y1 > y2) swap(y1, y2);
			X1[i] = x1, X2[i] = x2, Y1[i] = y1, Y2[i] = y2;
			upd(x1, y1, 1 * lol[i]);
			upd(x1, y2, -1 * lol[i]);
			upd(x2, y1, -1 * lol[i]);
			upd(x2, y2, 1 * lol[i]);
		}
		else if(t == 2){
			int j;
			cin >> j;
			upd(X1[j], Y1[j], -1 * lol[j]);
			upd(X1[j], Y2[j], 1 * lol[j]);
			upd(X2[j], Y1[j], 1 * lol[j]);
			upd(X2[j], Y2[j], -1 * lol[j]);
		}
		else{
			int x1, y1, x2, y2;
			cin >> x1 >> y1 >> x2 >> y2;
			if(sum(x1, y1) == sum(x2, y2)){
				cout << "Y";
			}
			else{
				cout << "N";
			}
		}
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
