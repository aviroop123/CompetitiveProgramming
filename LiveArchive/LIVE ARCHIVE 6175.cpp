// Solution uses 3D dp. Let dp[i][j][k] denote the expected value of the rightmost position with i operations left,
// j is the current position, k is the rightmost position which occured till now. Therefore, dp[n][p][r] = (1 - pl - pr) * dp[n - 1][p][r](if he stays at the same position)
//+ pl * dp[n - 1][p - 1][r](if he moves left) + pr * dp[n - 1][p + 1][max(r, p + 1)](if he moves right).
// To reduce memory consumption, the first dimension can be reduced to 2 since we need only the last value.

#include<bits/stdc++.h>
using namespace std;

#define pb emplace_back
#define fi first
#define se second
#define all(x) x.begin(), x.end()
#define vi vector
#define forn(i, l, r) for(int i = l; i <= r; i++)
#define IO ios :: sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define pii pair<int,int>
#define f80 double
#define LOCAL 0
#define endl '\n'

typedef long long int ll;
#define int long long int

const int mod = 1e9 + 7;
const int N = 2005;
const int inf = 1e18;

f80 dp[2][2 * N][2 * N];
f80 pl, pr;

signed main(){
    IO;
    if(LOCAL){
        freopen("inp.txt", "r", stdin);
    }
    int t;
    cin >> t;
    while(t--){
        int n, k;
        cin >> k >> n;
        cout << k << " ";
        cin >> pl >> pr;
        forn(i, 0, 2 * N - 1)
        forn(j, i, 2 * N - 1)
        dp[0][i][j] = j;
        forn(i, 1, n){
            forn(j, 1, 2 * N - 2){
                forn(k, j, 2 * N - 1){
                    int i1 = (i - 1) & 1, i2 = i & 1;
                    dp[i2][j][k] = (1 - pl - pr) * dp[i1][j][k] + pl * dp[i1][j - 1][k] + pr * dp[i1][j + 1][max(k, j + 1)];
                }
            }
        }
        f80 ans = dp[(n & 1)][N][N] - N;
        cout << setprecision(4) << fixed << ans << endl;
    }
    return 0;
}
