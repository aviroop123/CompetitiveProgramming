#pragma GCC optimize ("Ofast")
#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
// #define int long long int
#define pb push_back
#define fi first
#define se second
#define fr(i, a, b) for(int i = a; i <= b; i++)
#define all(x) x.begin(), x.end()
#define IO ios :: sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define pii pair<int,ll>
const int mod = 1e9 + 7;
const int mod1 = 998244353;
typedef long double f80;
#ifndef LOCAL
#define endl '\n'
#endif
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

const int N = 1005;
int t[N][N], a[N][N];
ll pre[N][N];
deque<pii> d;
struct node{
    int i, j;
    ll val;
};
inline bool cmp(const node &a, const node &b){
    if(a.val != b.val) return a.val < b.val;
    else if(a.i != b.i) return a.i < b.i;
    else return a.j < b.j;
}
int bit[N][N], n, m, p, q;
void update(int i,int j){
    while(i <= n){
        int jj = j;
        while(jj <= m){
            bit[i][jj]++;
            jj += (jj & (-jj));
        }
        i += i & (-i);
    }
}
int query(int i,int j){
    int ans = 0;
    while(i){
        int jj = j;
        while(jj){
            ans += bit[i][jj];
            jj -= jj & (-jj);
        }
        i -= i & (-i);
    }
    return ans;
}
vector<node> ql;
vector<node> lol;
void solve(){
    cin >> n >> m >> p >> q;
    fr(i, 1, n){
        fr(j, 1, m){
            cin >> a[i][j];
            pre[i][j] = pre[i - 1][j] + pre[i][j - 1] - pre[i - 1][j - 1] + a[i][j];
        }
    }
    fr(i, 1, n){
        while(!d.empty()) d.pop_back();
        fr(j, 1, m){
            while(!d.empty() && d.back().se > a[i][j]) d.pop_back();
            d.push_back({j, a[i][j]});
            while(d.front().fi <= j - q) d.pop_front();
            t[i][j] = d.front().se;
        }
    }
    fr(j, 1, m){
        while(!d.empty()) d.pop_back();
        fr(i, 1, n){
            while(!d.empty() && d.back().se > t[i][j]) d.pop_back();
            d.push_back({i, t[i][j]});
            while(d.front().fi <= i - p) d.pop_front();
            if(i >= p && j >= q)
                ql.pb({i, j, pre[i][j] - pre[i - p][j] - pre[i][j - q] + pre[i - p][j - q] - p * q * d.front().se});
        }
    }
    sort(all(ql), cmp);
    for(auto u : ql){
        int val = query(u.i, u.j) - query(u.i - p, u.j) - query(u.i, u.j - q) + query(u.i - p, u.j - q);
        if(val) continue;
        lol.pb(u);
        update(u.i, u.j);
        update(u.i - p + 1, u.j);
        update(u.i - p + 1, u.j - q + 1);
        update(u.i, u.j - q + 1);
    }
    cout << lol.size() << endl;
    for(auto it : lol){
        cout << it.i - p + 1 << " " << it.j - q + 1 << " " << it.val << endl;
    }
}
signed main()
{
    IO;
    #ifdef LOCAL
     freopen("inp.txt", "r", stdin);
     // freopen("out.txt", "w", stdout);
    #endif
    clock_t clk = clock();
    int t;
    // cin >> t;
    t = 1;
    fr(i, 1, t){
        solve();
    }
    cerr << endl << setprecision(10) << fixed << (double)(clock() - clk) / CLOCKS_PER_SEC;
    return 0;
}
