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
const int N = 10001;
const int inf = 2e9;

f80 a[N];

signed main(){
    if(LOCAL){
        freopen("inp.txt", "r", stdin);
    }
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        forn(i, 1, n)
            cin >> a[i];
        sort(a + 1, a + n + 1);
        f80 ans = 0;
        forn(i, 3, n){
            if(a[i] >= a[i - 1] + a[i - 2]) continue;
            f80 s = (a[i] + a[i - 1] + a[i - 2]) / 2;
            f80 area = s * (s - a[i]) * (s - a[i - 1]) * (s - a[i - 2]);
            ans = max(ans, area);
        }
        ans = sqrt(ans);
        ans = round(100 * ans);
        cout << setprecision(2) << fixed << ans / 100 << endl;
    }
    return 0;
}
