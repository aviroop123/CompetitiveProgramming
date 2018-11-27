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
#define pii pair<int,int>
const int mod = 1e9 + 7;
const int mod1 = 998244353;
typedef long double f80;
#ifndef LOCAL
#define endl '\n'
#endif
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

const int N = 16500;
int comp[N], comp1[N], dsu[N], lol[N];
bitset<N> b;
int n, m;
int root(int u){
    return (dsu[u] == u) ? u : (dsu[u] = root(dsu[u]));
}
bool uni(int u,int v){
    u = root(u), v = root(v);
    if(u == v) return 0;
    dsu[root(u)] = root(v);
    return 1;
}
vector<int> cp;
void solve(){
    cin >> n >> m;
    m /= 4;
    int ans = 0;
    fr(i, 1, n){
        b.reset();
        fr(j, 1, m){ // good
            int c = 4 * j, x;
            char ch;
            cin >> ch;
            if(ch >= '0' && ch <= '9') x = ch - '0';
            else x = 10 + ch - 'A';
            while(x){
                b[c--] = (x & 1);
                x >>= 1;
            }
        }
        if(i == 1){ // good
            fr(j, 1, 4 * m){
                if(b[j]){
                    int r = j;
                    while(b[r]) r++;
                    r--;
                    ans++;
                    fr(k, j, r) comp[k] = ans;
                    j = r;
                }
            }
        }
        else{
            int maxi = 0;
            fr(j, 1, 4 * m){
                comp1[j] = 0;
                dsu[j] = j;
                if(comp[j]) maxi = max(maxi, comp[j]);
            }
            fr(j, 1, 4 * m){
                if(b[j]){
                    int r = j, p = -1;
                    while(b[r]){
                        if(comp[r]){
                            if(p != -1)
                                ans -= uni(p, comp[r]);
                            p = comp[r];
                        }
                        r++;
                    }
                    if(p == -1)
                        comp1[j] = ++maxi, ans++;
                    j = r;
                }
            }
            fr(j, 1, 4 * m){
                if(comp[j] && b[j]) comp1[j] = root(comp[j]);
            }
            fr(j, 1, 4 * m){
                if(comp1[j]){
                    int r = j;
                    while(b[r]){
                        comp1[r] = comp1[j];
                        r--;
                    }
                    r = j;
                    while(b[r]){
                        comp1[r] = comp1[j];
                        r++;
                    }
                    cp.pb(comp1[j]);
                    j = r;
                }
            }
            sort(all(cp));
            unique(all(cp));
            int cc = 0;
            for(int x : cp){
                lol[x] = ++cc;
            }
            fr(j, 1, 4 * m){
                if(comp1[j])
                    comp1[j] = lol[comp1[j]];
                comp[j] = comp1[j];
            }
            cp.clear();
        }
    }
    cout << ans;
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
