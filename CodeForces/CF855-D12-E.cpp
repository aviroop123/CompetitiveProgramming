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
#define pii pair<int,int>
const int mod = 1e9 + 7;
const int mod1 = 998244353;
typedef long double f80;
#ifndef LOCAL
#define endl '\n'
#endif
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int dp[11][70][1 << 10];
vector<int> v;
int get(int b, int x){
    v.clear();
    // cout << b << " " << x << endl;
    while(x){
        v.pb(x % b);
        x /= b;
    }
    reverse(all(v));
    int ans = 0;
    for(int i = 1; i < v.size(); i++)
        ans += (dp[b][i][0] - dp[b][i - 1][1]);
    int l = v.size();
    int nmask = 0;
    for(int i = 0; i < l; i++){
        for(int j = 0; j < v[i]; j++){
            if(i == 0 && j == 0) continue;
            ans += dp[b][l - 1 - i][(nmask ^ (1 << j))];
        }
        nmask ^= (1 << v[i]);
    }
    // cout << ans << endl;
    return ans;
}
void solve(){
    int q;
    cin >> q;
    fr(i, 2, 10){
        dp[i][0][0] = 1;
        fr(l, 1, 60){
            fr(mask, 0, (1 << 10) - 1){
                fr(j, 0, i - 1){
                    dp[i][l][mask] += dp[i][l - 1][(mask ^ (1 << j))];
                }
            }
        }
    }
    while(q--){
        int b, l, r;
        cin >> b >> l >> r;
        int ans = get(b, r + 1) - get(b, l);
        cout << ans << endl;
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
