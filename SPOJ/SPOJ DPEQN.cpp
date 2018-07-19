// The equation boils down to finding a soln of a1 * x1 + a2 * x2 + ... + an * xn + m * x(n + 1) = b. This can be solved using extended gcd algorithm.
// We maintain two arrays, one for storing the coefficients after some modulo operation and the other for the soln. Soln is possible iff 
// gcd(a1, a2, .. an, m) divides b. Now we do some operations just like extended gcd, take the smallest of the coefficients greater than 0 and mod all other coefficients 
// with this value. After some operations, only 1 element will remain non-zero, this element is the gcd. After the operations, we can build the
// new soln from the original one just like extended gcd.
// Time complexity : O(N * N * log(N))

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
const int N = 105;
const int inf = 1e18;

int a[N], x[N];
bool valid;
void solve(int a[],int n,int b,int x[]){
    int cc = 0, mini = -1, idx = -1; // mini is the minimum non-zero element, idx is its position, cc is count of non-zero values.
    forn(i, 1, n){
        if(a[i]){
            if(idx == -1)
            {
                idx = i;
                mini = a[i];
            }
            mini = min(mini, a[i]);
            if(mini == a[i]) idx = i;
            cc++;
        }
    }
    if(cc == 1){ // only one non-zero element remains, this element is the gcd
        if(b % mini != 0){
            valid = 0; // if gcd doesn't divide b
        }
        else{
            x[idx] = b / mini; // soln for the base case
        }
        return;
    }
    int c[N]; // stores the new coefficients.
    copy(a + 1, a + n + 1, c + 1);
    forn(i, 1, n){
        if(i == idx) continue;
        c[i] %= mini;
    }
    solve(c, n, b, x); 
    if(!valid) return;
    forn(i, 1, n){ // getting the new soln from the previous one
        if(i == idx) continue;
        // We need x, y s.t. a[idx] * x + a[i] * y = a * x1 + (a[i] % a[idx]) * y1 -> x = x1 - (a[i] / a[idx]) * y1, y = y1.
        x[idx] -= (a[i] / mini) * x[i];
    }
    return;
}

signed main(){
    IO;
    if(LOCAL){
        freopen("inp.txt", "r", stdin);
    }
    int t;
    cin >> t;
    while(t--){
        int n, m, b;
        cin >> n;
        forn(i, 1, n)
            cin >> a[i];
        cin >> b >> m;
        a[++n] = m;
        fill(x + 1, x + n + 1, 0);
        valid = 1;
        solve(a, n, b, x);
        if(valid)
            {
                forn(i, 1, n - 1){
                    x[i] = (x[i] % m + m) % m;
                    cout << x[i] << " ";
                }
            }
        else
            cout << "NO";
        cout << endl;
    }
    return 0;
}
