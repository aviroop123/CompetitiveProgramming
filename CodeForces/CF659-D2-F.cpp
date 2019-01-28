/* Solution : From highest value to lowest value, we connect cells and after each connection we check whether the number(say val) divides k and size of the component >= (k / val). If yes, then we can choose an arbitrary connected component of this component of size k / val and total sum = k.
*/
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
const int N = 1005;
int dsu[N * N], sz[N * N];
bool active[N][N];
int a[N][N], b[N][N];
vector<pair<int,pii>> v;
int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};
int n, m, k;
bool check(int x,int y){
	return x >= 1 && x <= n && y >= 1 && y <= m;
}
int idx(int x,int y){
	return (x - 1) * m + y;
}
int root(int u){
	return ((dsu[u] == u) ? u : dsu[u] = root(dsu[u]));
}
void uni(int u,int v){
	u = root(u), v = root(v);
	if(u == v) return;
	if(sz[u] < sz[v]) swap(u, v);
	dsu[v] = u;
	sz[u] += sz[v];
}
void dfs(int x,int y,int &rem,int val){
	b[x][y] = val;
	rem--;
	if(!rem) return;
	fr(k, 0, 3){
		int xx = x + dx[k], yy = y + dy[k];
		if(check(xx, yy) && a[xx][yy] >= val && !b[xx][yy])
			dfs(xx, yy, rem, val);
		if(!rem) return;
	}
}
void solve(){
	iota(dsu, dsu + N * N, 0);
	fill(sz, sz + N * N, 1);
	cin >> n >> m >> k;
	fr(i, 1, n){
		fr(j, 1, m){
			cin >> a[i][j];
			v.pb({a[i][j], {i, j}});
		}
	}
	sort(all(v));
	reverse(all(v));
	for(auto it : v){
		int x = it.se.fi, y = it.se.se;
		active[x][y] = 1;
		fr(k, 0, 3){
			int xx = x + dx[k], yy = y + dy[k];
			if(!check(xx, yy)) continue;
			if(active[xx][yy]) uni(idx(x, y), idx(xx, yy));
		}
		if(k % it.fi == 0 && sz[root(idx(x, y))] >= (k / it.fi))
		{
			int g = (k / it.fi);
			dfs(x, y, g, it.fi);
			cout << "YES" << endl;
			fr(i, 1, n){
				fr(j, 1, m){
					cout << b[i][j] << " ";
				}
				cout << endl;
			}
			return;
		}
	}
	cout << "NO" << endl;
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
