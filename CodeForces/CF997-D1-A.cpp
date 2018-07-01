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

string s, t = "";
signed main(){
    //freopen("inp.txt", "r", stdin);
    //ios :: sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int n, x, y;
    cin >> n >> x >> y;
    cin >> s;
    t += s[0];
    int j = 0;
    for(int i = 1; i < s.length(); i++){
        if(t[j] == s[i]) continue;
        t += s[i];
        j++;
    }
    int z = 0;
    for(int i = 0; i < t.length(); i++){
        if(t[i] == '0')
            z++;
    }
    int ans;
    if(z == 0)
        ans = 0;
    else
        ans = min((z - 1) * x + y, z * y);
    cout << ans;
    return 0;
}
