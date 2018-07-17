#include<bits/stdc++.h>
using namespace std;

#define pb emplace_back
#define fi first
#define se second
#define all(x) x.begin(), x.end()
#define vi vector
#define forn(i, l, r) for(int i = l; i <= r; i++)
#define IO ios :: sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define pii pair<int,int>
#define f80 long double
#define LOCAL 0
#define endl '\n'

typedef long long int ll;
#define int long long int

const int mod = 1e9 + 7;
const int N = 200005;
const int inf = 1e9;

int phi(int n){
    int ans = n;
    if(n % 2 == 0)
        ans /= 2;
    if(n % 5 == 0)
        ans = (4 * ans) / 5;
    return ans;
}
int newmod(int a,int b){
    return (a <= b) ? a : a % b + b;
}
int pwr(int a,int b,int md){
    int ans = newmod(1, md);
    while(b){
        if(b & 1)
            ans = newmod((ans * a), md);
        a = newmod((a * a), md);
        b >>= 1;
    }
    return ans;
}
int solve(int b,int p,int md){
    if(p == 0) return newmod(1, md);
    int x = solve(b, p - 1, phi(md));
    return pwr(b, x, md);
}
signed main(){
    IO;
    if(LOCAL){
        freopen("inp.txt", "r", stdin);
    }
    int b, p, n;
    while(1){
        cin >> b;
        if(!b)
            break;
        cin >> p >> n;
        int md = pow(10, n);
        int ans = solve(b, p, md) % md;
        string s = to_string(ans);
        while(s.length() < n)
            s = '0' + s;
        cout << s << endl;
    }
    return 0;
}
