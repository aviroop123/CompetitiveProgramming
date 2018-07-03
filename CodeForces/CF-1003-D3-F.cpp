#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef long double f80;
#define pb push_back
#define fi first
#define se second
const int mod = 1e9 + 7;
const int mod1 = 101;
#define int long long int

string w[305];
string tot;
vector<int> s, e;
int h[100005], inv[100005];
int power(int a,int b,int m){
    int ans = 1;
    while(b){
        if(b & 1)
            ans = (ans * a) % mod;
        a = (a * a) % mod;
        b >>= 1;
    }
    return ans;
}
int get_len(int i,int j){
    return e[j - 1] - s[i - 1] + 1;
}
int get_hash(int i,int j){
    int val = h[e[j - 1]] - ((i == 1) ? 0 : h[s[i - 1] - 1]);
    val = (val * inv[s[i - 1]]) % mod;
    val = (val + mod) % mod;
    return val;
}
signed main(){
    //freopen("inp.txt", "r", stdin);
    ios :: sync_with_stdio(0);
    int n;
    cin >> n;
    for(int i = 1; i <= n; i++){
        cin >> w[i];
        s.pb(tot.size());
        tot += w[i];
        e.pb(tot.size() - 1);
        if(i != n)
            tot += "A";
    }
    int c = mod1;
    h[0] = (tot[0] - 'A');
    inv[0] = 1;
    for(int i = 1; i < tot.size(); i++){
        h[i] = (h[i - 1] + (tot[i] - 'A') * c) % mod;
        inv[i] = power(c, mod - 2, mod);
        c = (c * mod1) % mod;
    }
    int ans = tot.size();
    for(int i = 1; i <= n; i++){
        for(int j = i; j <= n; j++){
            int val = tot.size();
            int hh = get_hash(i, j);
            int l = j - i;
            int len = get_len(i, j);
            int cc = 0;
            for(int k = 1; k + l <= n; k++){
                if(get_hash(k, k + l) == hh)
                {
                    cc++;
                    val -= len;
                    val += j - i + 1;
                    k += l;
                }
            }
            if(cc > 1)
            ans = min(ans, val);
        }
    }
    cout << ans;
    return 0;
}
