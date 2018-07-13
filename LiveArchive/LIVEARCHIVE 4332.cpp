#include<bits/stdc++.h>
using namespace std;

#define pb emplace_back
#define fi first
#define se second
#define all(x) x.begin(), x.end()
#define vi vector
#define IO ios :: sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define forn(i, l, r) for(int i = l; i <= r; i++)
#define pii pair<int,int>
#define f80 long double
#define LOCAL 0

typedef long long int ll;
//#define int long long int

const int mod = 1e9 + 7;
const int N = 100005;
const int inf = 1e9;

int sz = 4, m = 10007;
const int NN = 4;
class matrix{
public:
    ll mat[NN][NN];
    matrix(){
        for(int i = 0; i < NN; i++)
            for(int j = 0; j < NN; j++)
                mat[i][j] = 0;
    }
    inline matrix operator * (const matrix &a){
        matrix temp;
        for(int i = 0; i < sz; i++)
            for(int j = 0; j < sz; j++){
                for(int k = 0; k < sz; k++){
                temp.mat[i][j] += (mat[i][k] * a.mat[k][j]) % m;
                if(temp.mat[i][j] >= m)
                    temp.mat[i][j] -= m;
                }
            }
        return temp;
    }
    inline matrix operator + (const matrix &a){
        matrix temp;
        for(int i = 0; i < sz; i++)
            for(int j = 0; j < sz; j++){
                temp.mat[i][j] = mat[i][j] + a.mat[i][j] ;
                if(temp.mat[i][j] >= m)
                    temp.mat[i][j] -= m;
            }
        return temp;
    }
    inline matrix operator - (const matrix &a){
        matrix temp;
        for(int i = 0; i < sz; i++)
            for(int j = 0; j < sz; j++){
                temp.mat[i][j] = mat[i][j] - a.mat[i][j] ;
                if(temp.mat[i][j] < m)
                    temp.mat[i][j] += m;
            }
        return temp;
    }
    inline void operator = (const matrix &b){
        for(int i = 0; i < sz; i++)
            for(int j = 0; j < sz; j++)
                mat[i][j] = b.mat[i][j];
    }
};
matrix pow(matrix a,ll k){
    matrix ans;
    for(int i = 0; i < sz; i++)
        ans.mat[i][i] = 1;
    while(k){
        if(k & 1)
            ans = ans * a;
        a = a * a;
        k >>= 1;
    }
    return ans;
}

signed main(){
    IO;
    if(LOCAL){
        freopen("inp.txt", "r", stdin);
    }
    while(1){
        int n;
        scanf("%d", &n);
        if(n == -1)
            break;
        matrix a;
        a.mat[1][0] = a.mat[2][1] = a.mat[3][2] = 1;
        a.mat[0][3] = -4, a.mat[1][3] = -8, a.mat[3][3] = 4;
        a = pow(a, n);
        ll ans = ((ll)a.mat[0][0] * 1 + (ll)a.mat[1][0] * 4 + (ll)a.mat[2][0] * 16 + (ll)a.mat[3][0] * 56) % m;
        ans = (ans + m) % m;
        printf("%lld\n", ans);
    }
    return 0;
}
