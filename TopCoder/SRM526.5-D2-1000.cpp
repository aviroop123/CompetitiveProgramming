#include<bits/stdc++.h>
using namespace std;

#define pb emplace_back
#define fi first
#define se second
#define all(x) x.begin(), x.end()
#define vi vector
#define IO ios :: sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define LOCAL 0
#define forn(i, l, r) for(int i = l; i <= r; i++)
#define pii pair<int,int>
#define f80 long double

typedef long long int ll;
//#define int long long int

const int mod = 1e9 + 7;
const int N = 55;
const int inf = 1e8;

typedef vector<int> VI;
typedef vector<VI> VVI;

const int INF = 1e9;

class MagicNaming{
public:
    int dp[N][N], n;
    bool go[N][N][N];
    int rec(int l,int p){
        if(l >= n)
            return 0;
        if(dp[l][p] != -1)
            return dp[l][p];
        int ans = -inf;
        for(int i = l; i < n; i++){
            if(go[p][l - 1][i])
                ans = max(ans, 1 + rec(i + 1, l));
        }
        return dp[l][p] = ans;
    }
    int maxReindeers(string s){
        n = s.size();
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
                dp[i][j] = -1;
        for(int i = 0; i < n; i++){
            for(int j = i; j < n; j++){
                for(int k = j + 1; k < n; k++){
                    string s1 = s.substr(i, j - i + 1) + s.substr(j + 1, k - j);
                    string s2 = s.substr(j + 1, k - j) + s.substr(i, j - i + 1);
                    if(s1 <= s2){
                        //cout << s.substr(i, j - i + 1) << " " << s.substr(j + 1, k - j) << endl;
                        go[i][j][k] = 1;
                    }
                }
            }
        }
        int ans = 0;
        for(int i = 0; i < n; i++){
            ans = max(ans, 1 + rec(i + 1, 0));
        }
        return ans;
    }
};
