#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef double f80;
#define fi first
#define se second
#define pii pair<int,int>
#define pb push_back
const int mod = 1e9 + 7;
#define int long long int

const int N = 100005;
priority_queue<int,vector<int>> p;
pair<int,int> a[N];
signed main(){
    //freopen("inp.txt", "r", stdin);
    ios :: sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int n;
    cin >> n;
    for(int i = 1; i <= n; i++){
        cin >> a[i].fi;
    }
    for(int i = 1; i <= n; i++){
        cin >> a[i].se;
    }
    sort(a + 1,a + n + 1);
    int ans = 0;
    for(int i = 1; i <= n; i++){
        p.push(a[i].se);
        if(((n - i) & 1))
        {
            ans += p.top();
            p.pop();
        }
    }
    cout << ans;
    return 0;
}
