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

const int mod = 1e9 + 7;
const int N = 200005;
const int inf = 1e9;

int newmod(ll a, int m){
    return (a <= m) ? a : a % m + m;
}
int pwr(int a,int b,int m){
    int ans = newmod(1, m);
    while(b){
        if(b & 1)
            ans = newmod((ll)ans * a, m);
        a = newmod((ll)a * a, m);
        b >>= 1;
    }
    return ans;
}
class FactorialTower{
    public :
    vi<int> b;
    int fact[40005], m;
    int phi[40005];
    bitset<40005> prime;    
    int getfact(int n,int m){
        int f = newmod(1, m);
        forn(i, 1, n){
            if(f % m == 0)
                break;
            f = newmod((ll)f * i, m);
        }
        return f;
    }
    int solve(int idx,int m){
        if(idx == b.size()) return newmod(1, m);
        int x = solve(idx + 1, phi[m]);
        int val = getfact(b[idx], m);
        return pwr(val, x, m);
    }
    int exprValue(vi<int> a, int _m){
        m = _m;
        b = a;
        fact[0] = newmod(1, m);
        forn(i, 1, 40000){
            fact[i] = newmod((ll)fact[i - 1] * i, m);
            phi[i] = i;
        }
        forn(i, 2, 40000){
        if(!prime[i]){
            for(int j = i; j <= 40000; j += i){
                phi[j] -= phi[j] / i;
                prime[j] = 1;
            }
        }
        }
        int ans = solve(0, m) % m;
        return ans;
    }
};
