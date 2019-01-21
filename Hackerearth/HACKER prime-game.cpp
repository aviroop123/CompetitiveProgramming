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

typedef long double float80;
typedef unsigned long long uint64;
typedef long long int64;
inline uint64 mul_mod(uint64 a, uint64 b, uint64 mod, float80 i = 0)
{
    if(!i) i = float80(1) / float80(mod);
    uint64 y = uint64(float80(a) * float80(b) * i + float80(1) / 2);
    uint64 r = a * b - y * mod;
    if(int64(r) < 0)
        r += mod;
    return r;
}
int pwr(int a,int b,int m)
{
    int ans = 1;
    while(b)
    {
        if(b & 1)
            ans = (ans * a) % m;
        a = (a * a) % m;
        b >>= 1;
    }
    return ans;
}

bool isprime(int n)
{
    if(n == 2 || n == 3) return 1;
    if(!(n & 1)) return 0;
    vector<int> v = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
    int r = 0;
    int x, d = n - 1;
    while(!(d & 1))
    {
        r++;
        d >>= 1;
    }
    float80 divi = float80(1) / float80(n);
    for(auto &a:v)
    {
        if(a >= n) break;
        x = pwr(a, d, n);
        if(x == 1 || x == (n - 1)) continue;
        bool flag = 1;
        for(int i = 1; i < r; i++)
        {
            x = mul_mod(x, x, n, divi);
            if(x == 1) return 0;
            if(x == (n - 1))
            {
               flag = 0;
               break;
            }
        }
        if(flag) return 0;
    }
    return 1;
}

const int N = 20;
int dp[N][N];
string s;
int go(int l,int r){
	if(l == r) return 1;
	if(dp[l][r] != -1) return dp[l][r];
	int val = 0;
	fr(i, l, r){
		val = val * 10 + s[i] - '0';
	}
	if(isprime(val)){
		return dp[l][r] = 1;
	}
	if(!go(l + 1, r) || !go(l, r - 1))
		return dp[l][r] = 1;
	return dp[l][r] = 0;
}
void solve(){
	cin >> s;
	fill(&dp[0][0], &dp[0][0] + N*N, -1);
	int n = s.size();
	cout << (go(0, n - 1) ? "Alice" : "Bob") << endl;
}
signed main(){
  	IO;
  	#ifdef LOCAL
		freopen("inp.txt","r", stdin);
		// freopen("out.txt", "w", stdout);
	#endif
	clock_t clk = clock();
  	int t = 1;
  	cin >> t;
  	fr(tt, 1, t){
    	solve();
  	}
  	cerr << endl << (double)(clock() - clk) / CLOCKS_PER_SEC;
  	return 0;
}
