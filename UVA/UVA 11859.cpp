#include<bits/stdc++.h>
using namespace std;

#define pb emplace_back
#define fi first
#define se second
#define all(x) x.begin(), x.end()
#define vi vector
#define forn(i, l, r) for(int i = l; i <= r; i++)
#define pii pair<int,int>
#define f80 long double
#define LOCAL 0
#define endl '\n'

typedef long long int ll;
//#define int long long int

const int mod = 1e9 + 7;
const int N = 55;
const int inf = 2e9;

int a[N][N];
bool prime[10005];
int d[10005];

signed main(){
    if(LOCAL){
        freopen("inp.txt", "r", stdin);
    }
    forn(i, 2, 10000){
        if(!prime[i]){
            for(int j = i; j <= 10000; j += i){
                int v = j;
                while(v % i == 0){
                    d[j]++;
                    v /= i;
                }
                prime[j] = 1;
            }
        }
    }
    int t;
    cin >> t;
    forn(tt, 1, t){
        int n, m;
        cin >> n >> m;
        forn(i, 1, n)
        forn(j, 1, m)
        cin >> a[i][j];
        int g = 0;
        forn(i, 1, n){
            int val = 0;
            forn(j, 1, m)
                val += d[a[i][j]];
            g ^= val;
        }
        cout << "Case #" << tt << ": ";
        if(g)
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
    }
    return 0;
}
