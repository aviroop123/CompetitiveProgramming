#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
//#define int long long int
#define pb push_back
#define fi first
#define se second
#define forn(i, x, y) for(int i = x; i <= y; i++)
#define all(x) x.begin(), x.end()
typedef vector<int> vi;

const int MAXN = 19;
const int maxn = 1 << MAXN;
const int mod = 998244353;
const int root = 3;
 
int A[maxn], B[maxn];
int W[maxn],iW[maxn], I[maxn];
int nn;
const int threshold = 10000;

int fact[maxn], ifact[maxn];

namespace modulo{
    const int MOD = 998244353;
    int add(const int &a,const int &b){
        int val = a + b;
        if(val >= MOD) val -= MOD;
        return val;
    }
    int sub(const int &a,const int &b){
        int val = a - b;
        if(val < 0) val += MOD;
        return val;
    }
    int mul(const int &a, const int &b){
        return 1ll * a * b % MOD;
    }
}
using namespace modulo;

void ensureINV(int n){
    if(n <= nn) return;
    if(!nn){
        I[1] = 1;
        nn = 1;
    }
    forn(i, nn + 1, n)
        I[i] = (mod - mul((mod / i), I[mod % i]));
    nn = n;
}
void print(vi &a, int n = 0){
    if(!n) n = a.size();
    a.resize(n);
    forn(i, 0, n - 1)
        cout << a[i] << " ";
    cout << endl;
}
int pwr(int a,int b){
    int ans = 1;
    while(b){
        if(b & 1)
            ans = mul(ans, a);
        a = mul(a, a);
        b >>= 1;
    }
    return ans;
}
void precompute(){
    W[0] = iW[0] = 1;
    int g = pwr(root,(mod - 1) / maxn), ig = pwr(g, mod - 2);
    forn(i, 1, maxn / 2 - 1){
        W[i] = mul(W[i - 1], g);
        iW[i] = mul(iW[i - 1], ig);
    }
}
int rev(int i, int n){
    int irev = 0;
    n >>= 1;
    while(n){
        n >>= 1;
        irev = (irev << 1) | (i & 1);
        i >>= 1;
    }
    return irev;
}
void go(int a[], int n){
    forn(i, 0, n - 1){
        int r = rev(i, n);
        if(i < r)
            swap(a[i], a[r]);
    }
}

void fft(int a[], int n, bool inv = 0){
    go(a, n);
    int len, i, j, *p, *q, u, v, ind, add;
    for(len = 2; len <= n; len <<= 1){
        for(i = 0; i < n; i += len){
            ind = 0, add = maxn / len;
            p = &a[i], q = &a[i + len / 2];
            forn(j, 0, len / 2 - 1){
                v = mul((*q), (inv ? iW[ind] : W[ind]));
                (*q) = sub((*p), v);
                (*p) = ::add((*p), v);
                ind += add;
                p++, q++;
            }
        }
    }
    if(inv) {
        int p = pwr(n, mod - 2);
        forn(i, 0, n - 1)
            a[i] = mul(a[i], p);
    }
}
vi brute(const vi &a, const vi &b){
    vi c(a.size() + b.size() - 1, 0);
    for(int i = 0; i < a.size(); i++){
        for(int j = 0; j < b.size(); j++){
            c[i + j] = add(c[i + j], mul(a[i], b[j]));
        }
    }
    return c;
}
vi mul(vi a, vi b,int n){ // n = total size
    if((ll)a.size() * b.size() <= threshold)
        return brute(a, b);
    a.resize(n);
    copy(all(a), A);
    fft(A, n);
    if(a == b)
        copy(A, A + n, B);
    else{
        b.resize(n);
        copy(all(b), B);
        fft(B, n);
    }
    forn(i, 0, n - 1)
        A[i] = mul(A[i], B[i]);
    fft(A, n, 1);
    vi c(A, A + n);
    return c;
}
vi inv(vi a, int m){ // get m terms
    assert(a[0] != 0);
    int tot = 1;
    while(tot < m)
        tot <<= 1;
    swap(tot, m);
    a.resize(m, 0);
    vi ia(m, 0);
    ia[0] = pwr(a[0], mod - 2);
    for(int sz = 2; sz <= m; sz <<= 1){
        copy(ia.begin(), ia.begin() + sz / 2, A);
        copy(a.begin(), a.begin() + sz, B);
        fill(A + sz / 2, A + (sz << 1), 0);
        fill(B + sz, B + (sz << 1), 0);
        fft(A, sz << 1);
        fft(B, sz << 1);
        forn(j, 0, (sz << 1) - 1)
            A[j] = add(A[j], sub(A[j], mul(mul(A[j], A[j]), B[j])));
        fft(A, sz << 1, 1);
        copy(A, A + sz, ia.begin());
    }
    ia.resize(tot);
    return ia;
}
vi sqrt(vi a, int m){ // get m terms
    int x = sqrt(a[0]);
    assert(x * x == a[0]);
    int tot = 1;
    while(tot < m)
        tot <<= 1;
    swap(tot, m);
    vi sa(m, 0);
    a.resize(m);
    sa[0] = x;
    int p = (mod + 1) / 2;
    for(int sz = 2; sz <= m; sz <<= 1){
        vi t1(a.begin(), a.begin() + sz);
        vi t2(sa.begin(), sa.begin() + sz / 2);
        t2 = inv(t2, sz);
        t1 = mul(t1, t2, sz << 1);
        for(int i = 0; i < sz; i++)
            sa[i] = mul(p, add(sa[i], t1[i]));
    }
    sa.resize(tot);
    return sa;
}
vi diff(vi a){
    if(a.size() == 1) return {0};
    int n = a.size() - 1;
    forn(i, 0, n - 1)
        a[i] = mul(i + 1, a[i + 1]);
    a.resize(n);
    return a;
}
vi integrate(vi a){
    int n = a.size();
    ensureINV(n);
    a.pb(0);
    for(int i = n - 1; i >= 0; i--)
        a[i + 1] = mul(a[i], I[i + 1]);
    a[0] = 0;
    return a;
}
vi log(vi a, int m){ // get m terms
    assert(a[0] == 1);
    int tot = 1;
    while(tot < m)
        tot <<= 1;
    swap(tot, m);
    a.resize(m);
    vi t1 = inv(a, m);
    vi t2 = diff(a);
    t2.resize(m);
    vi t = mul(t1, t2, m << 1);
    t = integrate(t);
    t.resize(tot);
    return t;
}
vi exp(vi a, int m){ // get m terms
    assert(!a[0]);
    int tot = 1;
    while(tot < m){
        tot <<= 1;
    }
    swap(tot, m);
    vi ea(m, 0);
    ea[0] = 1;
    a.resize(m);
    for(int sz = 2; sz <= m; sz <<= 1){
        vi t1 = log(ea, sz);
        vi t2(sz);
        forn(i, 0, sz - 1){
            t1[i] = sub(a[i], t1[i]);
            t2[i] = ea[i];
        }
        t1[0]++;
        vi t3 = mul(t1, t2, sz << 1);
        copy(t3.begin(), t3.begin() + sz, ea.begin());
    }
    ea.resize(tot);
    return ea;
}
vi pwr(vi a, int n,int m){ // get first m terms
    assert(n >= 0);
    vi ans = {1};
    while(n){
        if(n & 1)
        {
            int tot = 1;
            while(tot < ans.size() + a.size() - 1)
                tot <<= 1;
            ans = mul(ans, a, tot);
            ans.resize(min((int)ans.size(), m));
        }
        int tot = 1;
        while(tot < 2 * a.size() - 1) tot <<= 1;
        a = mul(a, a, tot);
        a.resize(min((int)a.size(), m));
        n >>= 1;
    }
    return ans;
}
int gf(int num,int den){
    return mul(num, pwr(den, mod - 2));
}
const int N = 100005;
int l[N], r[N], c[N];
void getFact(){
    fact[0] = 1;
    forn(i, 1, N - 1){
        fact[i] = mul(fact[i - 1], i);
    }
    ifact[N - 1] = pwr(fact[N - 1], mod - 2);
    for(int i = N - 2; i >= 0; i--)
        ifact[i] = mul(ifact[i + 1], (i + 1));
}
signed main(){
    //freopen("inp.txt", "r", stdin);
    getFact();
    precompute();
    ll n, k, m;
    scanf("%lld %lld %lld", &k, &m, &n);
    m %= mod;
    int sz = 1;
    while(sz < k + 1) sz <<= 1;
    sz <<= 1;
    vi ans(k + 1, 0);
    for(int i = 0; i <= k; i++)
        ans[i] = ifact[i + 1];
    ans = log(ans, k + 1);
    forn(i, 0, k) ans[i] = (ans[i] * (mod - m)) % mod;
    forn(i, 1, n){
        scanf("%d %d %d", &l[i], &r[i], &c[i]);
        vi p(k + 1, 0);
        int val1 = (r[i] + 1), val2 = l[i];
        int pp = pwr(r[i] + 1 - l[i], mod - 2);
        forn(j, 0, k){
            p[j] = sub(val1, val2);
            p[j] = mul(p[j], ifact[j + 1]);
            p[j] = mul(p[j], pp);
            val1 = mul(val1, r[i] + 1);
            val2 = mul(val2, l[i]);
        }
        p = log(p, k + 1);
        forn(j, 0, k)
            ans[j] = add(ans[j], mul(c[i], p[j]));
    }
    ans = exp(ans, k + 1);
    int val = mul(fact[k], ans[k]);
    printf("%d", val);
    return 0;
} 
