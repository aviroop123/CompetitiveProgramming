// Let dp[i][j] be the maximum value you can achieve with the first i elements of a and first j elements of b. It can be easily
// proved that to get maximum value of dp[i][j], either a[i] or b[j] will be included in the product. So, the dp recurrence is as follows:
// dp[i][j] = max(dp[i - 1][k - 1] + a[i] * b[k] - sumb(k + 1, j)^2, dp[k - 1][j - 1] + a[k] * b[j] - suma(k + 1, i)^2) for all possible k. This can be calculated efficiently
// by considering rows and columns separately and forming cht for each row and column and updating accordingly.
// Here suma(i, j) = a[i] + a[i + 1] + ... + a[j]
//      sumb(i, j) = b[i] + b[i + 1] + ... + b[j]

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
#define f80 long double
#define LOCAL 0
#define endl '\n'
 
typedef long long int ll;
#define int long long int
 
const int mod = 1e9 + 7;
const int N = 1005;
const int inf = 1e17;
 
struct line {
    int a;
    long long b;
    
    line(int a = 0, long long b = 0) : a(a), b(b) { }
    
    long long evaluate(int x) const {
        return (long long)a * x + b;
    }
};
 
bool bad(const line& L1, const line& L2, const line& L3) {
    return (L2.b - L1.b) * (L1.a - L3.a) > (L3.b - L1.b) * (L1.a - L2.a);
}
 
struct convex_hull {
    int ind, sz;
    line lines[N];
    
    void clear() {
        sz = ind = 0;
    }
    
    void add(const line& L) {        
        while (sz > 0 && lines[sz - 1].a == L.a && lines[sz - 1].b < L.b) {
            --sz;
        }
        if (sz == 0 || lines[sz - 1].a < L.a) {
            while (sz > 1 && bad(lines[sz - 2], lines[sz - 1], L)) {
                --sz;
            }
            lines[sz++] = L;
        }
    }
    
    long long query(int x) {
        if (ind >= sz) {
            ind = sz - 1;
        }
        while (ind + 1 < sz && lines[ind + 1].b - lines[ind].b >= (long long)(lines[ind].a - lines[ind + 1].a) * x) {
            ++ind;
        }
        return lines[ind].evaluate(x);
    }
} rows, cols[N];
 
int a[N], b[N], sa[N], sb[N];
int dp[N][N];
signed main(){
    IO;
    if(LOCAL){
        freopen("inp.txt", "r", stdin);
        //freopen("out.txt", "w", stdout);
    }
    int n;
    cin >> n;
    forn(i, 1, n){
        cin >> a[i];
        sa[i] = sa[i - 1] + a[i];
    }
    forn(i, 1, n){
        cin >> b[i];
        sb[i] = sb[i - 1] + b[i];
    }
    forn(i, 1, n){ // Base cases
        dp[i][0] = -sa[i] * sa[i];
        dp[0][i] = -sb[i] * sb[i];
    }
    forn(i, 1, n){
        rows.clear();
        forn(j, 1, n){
            dp[i][j] = -inf;
            rows.add(line(2 * sb[j], dp[i - 1][j - 1] + a[i] * b[j] - sb[j] * sb[j]));
            cols[j].add(line(2 * sa[i], dp[i - 1][j - 1] + a[i] * b[j] - sa[i] * sa[i]));
            dp[i][j] = max(dp[i][j], rows.query(sb[j]) - sb[j] * sb[j]);
            dp[i][j] = max(dp[i][j], cols[j].query(sa[i]) - sa[i] * sa[i]);
        }
    }
    cout << dp[n][n];
    return 0;
} 
