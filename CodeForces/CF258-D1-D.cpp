#include<bits/stdc++.h>
using namespace std;

#define pb emplace_back
#define fi first
#define se second
#define all(x) x.begin(), x.end()
#define vi vector
#define IO ios :: sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define forn(i, l, r) for(int i = l; i <= r; i++)
#define pii pair<int,int>
#define f80 long double
#define LOCAL 0

typedef long long int ll;
#define int long long int

const int mod = 1e9 + 7;
const int N = 1005;
const int inf = 1e12;

f80 d[N][N];
int p[N];

main(){
    IO;
    if(LOCAL){
        freopen("inp.txt", "r", stdin);
        //freopen("out.txt", "w", stdout);
    }
    int n, m;
    cin >> n >> m;
    forn(i, 1, n)
    cin >> p[i];
    forn(i, 1, n)
    forn(j, i + 1, n)
    if(p[i] > p[j])
        d[i][j] = 1;
    forn(j, 1, m){
        int a, b;
        cin >> a >> b;
        if(a > b) swap(a, b);
        forn(i, 1, a - 1)
            d[i][a] = d[i][b] = 0.5 * (d[i][a] + d[i][b]);
        forn(i, a + 1, b - 1){
            f80 t1 = d[a][i], t2 = d[i][b];
            d[a][i] = 0.5 * t1 + 0.5 * (1 - t2);
            d[i][b] = 0.5 * t2 + 0.5 * (1 - t1);
        }
        forn(i, b + 1, n)
            d[a][i] = d[b][i] = 0.5 * d[a][i] + 0.5 * d[b][i];
        d[a][b] = 0.5;
    }
    f80 ans = 0;
    forn(i, 1, n)
    forn(j, i + 1, n)
    ans += d[i][j];
    cout << setprecision(10) << fixed << ans;
    return 0;
}
