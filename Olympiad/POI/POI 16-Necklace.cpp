// I got 96 pts with this implementation. It's the same as the solution of kors5.cpp but some minute changes made it faster when n is large and slow when n is small. 
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

const int N = 1e6 + 5;
pii a[N];
int n, k;
struct necklace{
	vector<int> s; // will store the updated indexes
	ll val;
	int max_bit;
	necklace() {}
	necklace(int b){
		val = a[b].fi;
		max_bit = b;
		s.pb(b);
	}
	void remove(int b){
		val -= a[b].fi;
		s.pop_back();
	}
	void add(int b){
		s.pb(b);
		max_bit = b;
		val += a[b].fi;
	}
};
necklace lol[2 * N];
vector<int> v1, v2;
class cmp{
public:
	bool operator () (const necklace* b, const necklace* c){
		if(b -> val != c -> val) return b -> val > c -> val;
		v1.clear(), v2.clear();
		for(int x : b -> s)
			v1.pb(a[x].se);
		for(int x : c -> s)
			v2.pb(a[x].se);
		sort(all(v1));
		sort(all(v2));
		return v1 > v2;
	}
};
int S = 1;
necklace* solve1(necklace * &a){
	lol[++S] = (*a);
	int b = a -> max_bit;
	lol[S].add(b + 1);
	return &lol[S];
}
necklace* solve2(necklace * &a){
	lol[++S] = (*a);
	int b = a -> max_bit;
	lol[S].remove(b);
	lol[S].add(b + 1);
	return &lol[S];
}
priority_queue<necklace*, vector<necklace*>, cmp> q;
void solve(){
	cin >> n >> k;
	fr(i, 1, n){
		cin >> a[i].fi;
		a[i].se = i;
	}
	if(k == 1){
		cout << 0 << endl;
		return;
	}
	sort(a + 1, a + n + 1);
	lol[1] = necklace(1);
	q.push(&lol[1]);
	while(!q.empty()){
		necklace* u = q.top();
		q.pop();
		k--;
		if(k == 1){
			v1.clear();
			for(int x : u -> s){
				v1.pb(a[x].se);
			}
			sort(all(v1));
			cout << u -> val << endl;
			for(int x : v1)
				cout << x << " ";
			return;
		}
		if(u -> max_bit == n) continue;
		auto A = solve1(u);
		auto B = solve2(u);
		q.push(A);
		q.push(B);
	}
	assert(0);
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
