#pragma GCC optimize ("Ofast")
#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
#define int long long int
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

// dp[i][p][q][p1][q1] -> covered till ith, current depth d
// p -> 1 deg nodes in prev layer, q -> 2 deg nodes in prev layer
// p1 -> 1 deg nodes in cur layer, q -> 2 deg nodes in cur layer
// ans = dp[n][0][0][0][0]
const int N = 52;
int dp[2][N][N][N][N];
int a[N];
int C(int n,int p){
    if(n < p) return 0;
    int ans = 1;
    fr(i, n - p + 1, n)
        ans *= i;
    fr(i, 1, p)
        ans /= i;
    return ans;
}
void solve(){
    int n;
    cin >> n;
    fr(i, 1, n)
        cin >> a[i];
    dp[0][(a[1] == 2)][(a[1] == 3)][(a[2] == 2)][(a[2] == 3)] = 1;
    fr(i, 2, n - 1){
        int l1 = (i & 1);
        int l2 = (l1 ^ 1);
        fr(p, 0, n)
            fr(q, 0, n)
                fr(p1, 0, n)
                    fr(q1, 0, n)
                        dp[l2][p][q][p1][q1] = 0;
        fr(p, 0, n){
            fr(q, 0, n){
                fr(p1, 0, n){
                    fr(q1, 0, n){
                        int cur = dp[l1][p][q][p1][q1];
                        if(!cur) continue;
                        fr(x1, 0, 3){
                            fr(x2, 0, 3){
                                if(x1 + x2 != 1) continue;
                                if(x1 + x2 > a[i + 1]) continue;
                                fr(x3, 0, 2){
                                    if(x1 + x2 + x3 > a[i + 1]) continue;
                                    fr(x4, 0, 2){
                                        int x5 = a[i + 1] - x1 - x2 - x3 - x4;
                                        if(x5 < 0) continue;
                                        if(x1 > p || x2 > q || x3 > p1 || x4 > q1) continue;
                                        int lol = (C(p, x1) * C(q, x2)) % mod;
                                        lol = (lol * C(p1, x3)) % mod;
                                        lol = (lol * C(q1, x4)) % mod;
                                        dp[l2][p - x1 + x2][q - x2][p1 - x3 + x4 + (x5 == 1)][q1 - x4 + (x5 == 2)] += (lol * cur) % mod;
                                        dp[l2][p - x1 + x2][q - x2][p1 - x3 + x4 + (x5 == 1)][q1 - x4 + (x5 == 2)] %= mod;
                                    }
                                }
                            }
                        }
                        if(p == 0 && q == 0){
                            fr(x1, 0, 3){
                                fr(x2, 0, 3){
                                    if(x1 + x2 != 1) continue;
                                    int x3 = a[i + 1] - x1 - x2;
                                    if(x3 < 0) continue;
                                    if(x1 > p1 || x2 > q1) continue;
                                    int lol = (C(p1, x1) * C(q1, x2)) % mod;
                                    dp[l2][p1 - x1 + x2][q1 - x2][x3 == 1][x3 == 2] += (lol * cur) % mod;
                                    dp[l2][p1 - x1 + x2][q1 - x2][x3 == 1][x3 == 2] %= mod;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    cout << dp[(n & 1)][0][0][0][0];
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
