#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef long double f80;
#define pb push_back
#define fi first
#define se second
const int mod = 1e9 + 7;
#define int long long int

const int N = 100000000;
bitset<N> temp;
int pre[N];
vector<int> primes;
void sieve(){
    for(int i = 2; i < N; i++){
        if(!temp[i]){
            primes.pb(i);
            pre[i] = 1;
            for(int j = i * i; j < N; j += i)
                temp[j] = 1;
        }
        pre[i] += pre[i - 1];
    }
}
int power(int a,int b,int m){
    //cout << a << " " << b << endl; 
    b %= (m - 1);
    int ans = 1;
    while(b){
        if(b & 1)
            ans = (ans * a) % m;
        a = (a * a) % m;
        b >>= 1;
    }
    return ans;
}
signed main(){
    //freopen("inp.txt", "r", stdin);
    ios :: sync_with_stdio(0);
    sieve();
    int t;
    cin >> t;
    while(t--){
        int n, m;
        cin >> n >> m;
        if(n < 3){
            cout << 0 << endl;
            continue;
        }
        int ans = 1, pp;
        for(int p: primes){
            pp = p;
            if(p == 2) continue;
            if(p * p > n)
                break;
            int k = 0;
            int nn = n;
            while(nn){
                nn /= p;
                k += nn;
                k %= m;
            }
            ans *= (k + 1);
            ans %= m;
        }
        for(int i = 1; i * i <= n; i++){
            ans = (ans * power(i + 1, pre[n / i] - pre[max(n / (i + 1), pp - 1)], m)) % m;
        }
        ans = (ans + m - 1) % m;
        cout << ans << endl;
    }
    return 0;
}
