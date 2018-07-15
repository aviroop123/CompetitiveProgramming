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
#define int long long int

const int mod = 1e9 + 7;
const int N = 1000005;
const int inf = 2e9;

pii a[N];
map<int,int> m;
vector<int> ans;

signed main(){
    if(LOCAL){
        freopen("inp.txt", "r", stdin);
    }
    int t;
    cin >> t;
    while(t--){
        int n, x, s;
        cin >> n >> s;
        ans.clear();
        m.clear();
        int total = 0;
        forn(i, 1, n)
        {
            cin >> x;
            total += x;
            m[x]++;
        }
        if(total < s){
            cout << "Impossible" << endl;
            continue;
        }
        int tot = 1;
        for(auto it : m){
            a[tot++] = {it.se * it.fi, it.fi};
        }
        sort(a + 1, a + tot);
        int val = 0;
        for(int i = tot - 1; i >= 1; i--){
            val += a[i].fi;
            ans.pb(a[i].se);
            if(val >= s)
                break;
        }
        sort(all(ans));
        for(int x : ans)
            cout << x << " ";
        cout << endl;
    }
    return 0;
}
