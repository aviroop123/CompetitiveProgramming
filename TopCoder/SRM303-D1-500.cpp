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
typedef long double f80;
#ifndef LOCAL
#define endl '\n'
#endif
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

const int inf = 1e9;

typedef vector<int> VI;
typedef vector<VI> VVI;

struct BipartiteMatcher {
    vector<vector<int>> G;
    vector<int> L, R, Viz;

    void init(int n, int m){
        G.clear(), L.clear(), R.clear(), Viz.clear();
        G.resize(n), L.resize(n, -1), R.resize(m, -1), Viz.resize(n, 0);
    }

    void AddEdge(int a, int b) {
        G[a].push_back(b);
    }

    bool Match(int node) {
        if(Viz[node]) 
            return false;
        Viz[node] = true;
    
        for(auto vec : G[node]) {
            if(R[vec] == -1 || Match(R[vec])) {
                L[node] = vec;
                R[vec] = node;
                return true;
            }
        }

        return false;
    }
    int Solve() {
        bool ok = true;
        while(ok) {
            ok = false;
            fill(Viz.begin(), Viz.end(), 0);
            for(int i = 0; i < L.size(); ++i)
                if(L[i] == -1)
                    ok |= Match(i);
        }
        
        int ret = 0;
        for(int i = 0; i < L.size(); ++i)
            ret += (L[i] != -1);
        return ret;
    }
} bm;
int x[8] = {1, 2, 2, 1, -1, -2, -2, -1};
int y[8] = {2, 1, -1, -2, -2, -1, 1, 2};
class Knights{
public:
    int a[27][27], b[27][27], n;
    int get(int i,int j){
        return (i - 1) * n + j;
    }
    bool check(int i,int j){
        return i >= 1 && i <= n && j >= 1 && j <= n;
    }
    int makeFriendly(int nn, vector<string> v){
        n = nn;
        int c1 = 0, c2 = 0;
        fr(i, 1, n){
            fr(j, 1, n){
                a[i][j] = 0;
                if((i + j) & 1)
                    b[i][j] = ++c1;
                else
                    b[i][j] = ++c2;
            }
        }
        BipartiteMatcher bm;
        bm.init(c1 + 1, c2 + 1);
        for(string s : v){
            for(int i = 0; i < s.size(); i += 3){
                a[s[i + 1] - '0'][s[i] - 'A' + 1] = 1;
            }
        }
        fr(i, 1, n){
            fr(j, 1, n){
                if(a[i][j])
                fr(k, 0, 7){
                    int xx = i + x[k], yy = j + y[k];
                    if(check(xx, yy) && a[xx][yy]){
                        if((i + j) & 1)
                            bm.AddEdge(b[i][j], b[xx][yy]);
                        else
                            bm.AddEdge(b[xx][yy], b[i][j]);
                    }
                }
            }
        }
        return bm.Solve();
    }
};
