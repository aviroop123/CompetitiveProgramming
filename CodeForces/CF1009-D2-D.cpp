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
//#define int long long int

const int mod = 1e9 + 7;
const int N = 100005;
const int inf = 1e9;

vector<pii> v;
signed main(){
    IO;
    if(LOCAL){
        freopen("inp.txt", "r", stdin);
    }
    int n, m;
    cin >> n >> m;
    if(m < (n - 1))
        return puts("Impossible"), 0;
    forn(i, 1, n){
        int z = min(2 * i, n);
        forn(j, i + 1, z){
            if(__gcd(i, j) == 1){
                for(int k = j; k <= n; k += i){
                    v.pb(i, k);
                    if(v.size() == m)
                    {
                    puts("Possible");
                    for(pii x : v)
                        printf("%d %d\n", x.fi, x.se);
                    return 0;
                    }
                }
            }
        }
    }
    puts("Impossible");
    return 0;
}
