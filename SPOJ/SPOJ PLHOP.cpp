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
const int inf = 2e18;

int sz;
const int NN = 55;
class matrix{
public:
    ll mat[NN][NN];
    matrix(){
        for(int i = 0; i < NN; i++)
            for(int j = 0; j < NN; j++)
                mat[i][j] = inf;
    }
    inline matrix operator * (const matrix &a){
        matrix temp;
        for(int i = 0; i < sz; i++)
            for(int j = 0; j < sz; j++){
                for(int k = 0; k < sz; k++)
                    temp.mat[i][j] = min(temp.mat[i][j], mat[i][k] + a.mat[k][j]);
        }
        return temp;
    }
    inline void operator = (const matrix &b){
        for(int i = 0; i < sz; i++)
            for(int j = 0; j < sz; j++)
                mat[i][j] = b.mat[i][j];
    }
    void print(){
    for(int i = 0; i < sz; i++){
        for(int j = 0; j < sz; j++)
            cout << mat[i][j] << " ";
        cout << endl;
    }
    }
};
matrix pow(matrix a,ll k){
    matrix ans = a;
    k--;
    while(k){
        if(k & 1)
            ans = ans * a;
        a = a * a;
        k >>= 1;
    }
    return ans;
}
matrix a, b, c;
matrix min(matrix a, matrix b){
    matrix c = a;
    for(int i = 0; i < sz; i++){
        for(int j = 0; j < sz; j++){
            if(c.mat[i][j] > b.mat[i][j])
                c.mat[i][j] = b.mat[i][j];
        }
    }
    return c;
}
signed main(){
    //freopen("inp.txt", "r", stdin);
    ios :: sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int t;
    cin >> t;
    for(int tt = 1; tt <= t; tt++){
        cout << "Region #" << tt << ":" << endl;
        int k, n;
        cin >> k >> n;
        sz = n;
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                cin >> a.mat[i][j];
            }
        }
        c = pow(a, k);
        b = c;
        for(int i = 1; i <= n; i++){
            b = min(b, c);
            c = c * a;
        }
        b.print();
    }
    return 0;
}
