#pragma GCC optimize ("Ofast")
#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
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
typedef long double f80;
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
const int N = 2e5 + 5;
ordered_set<int> bit[N];
int a[N], b[N], lol[N], n, m;
void insert(int idx, int val){
  while(idx <= n){
    bit[idx].insert(val);
    idx += (idx) & (-idx);
  }
}
void erase(int idx, int val){
  while(idx <= n){
    bit[idx].erase(val);
    idx += (idx) & (-idx);
  }
}
int query(int idx,int x,int y){
  int s = 0;
  while(idx){
    s += bit[idx].order_of_key(y + 1) - bit[idx].order_of_key(x);
    idx -= (idx) & (-idx);
  }
  return s;
}
void solve(){
  cin >> n >> m;
  // n = 2e5, m = 2e5;
  // fr(i, 1, n){
  //   a[i] = i;
  //   b[i] = i;
  // }
  // random_shuffle(a + 1, a + n + 1);
  // random_shuffle(b + 1, b + n + 1);
  fr(i, 1, n){
    cin >> a[i];
    lol[a[i]] = i;
  }
  fr(i, 1, n){
    cin >> b[i];
    b[i] = lol[b[i]];
    insert(i, b[i]);
  }
  fr(i, 1, m){
    int t;
    cin >> t;
    // t = rand(1, 2);
    if(t == 2){
      int u, v;
      cin >> u >> v;
      // u = rand(1, n), v = rand(1, n);
      erase(u, b[u]);
      erase(v, b[v]);
      insert(u, b[v]);
      insert(v, b[u]);
      swap(b[u], b[v]);
    }
    else{
      int l1, r1, l2, r2;
      cin >> l1 >> r1 >> l2 >> r2;
      // l1 = rand(1, n), r1 = rand(l1, n), l2 = rand(1, n), r2 = rand(l2, n);
      cout << query(r2, l1, r1) - query(l2 - 1, l1, r1) << endl;
    }
  }
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
  while(t--){
    solve();
  }
  cerr << endl << (double)(clock() - clk) / CLOCKS_PER_SEC;
  return 0;
}
