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

string s[5];
int c[6] = {1, 1, 0, -1, -1, 0}, d[6] = {-1, 1, 2, 1, -1, -2};
string e = "##.#.#.###.#.#.#.#.#.#.#.#.#.#.#.#.###.#.#.##";
bool check(int i,int j){
    return i >= 0 && i < 5 && j >= 0 && j < 9;
}
string get(string s[]){
    string ss = "";
    for(int i = 0; i < 5; i++)
        ss += s[i];
    return ss;
}
void put(string ss, string s[]){
    for(int i = 0; i < 5; i++){
        s[i] = ss.substr(9 * i, 9);
    }
}
int pos(int i,int j){
    return i * 9 + j;
}
int dp[1 << 19];
vi<int> positions;
int hh(string s){
    int tot = 0;
    for(int i = 0; i < 19; i++){
        if(s[positions[i]] == 'O')
            tot += (1 << i);
    }
    return tot;
}
int sz = 0;
bool go(string ss){
    if(ss == e)
        return 0;
    int h1 = hh(ss);
    if(dp[h1] != -1)
        return dp[h1];
    string s[5];
    put(ss, s);
    bool yes = 0;
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 9; j++){
            if(s[i][j] == 'O'){
                for(int k = 0; k < 6; k++){
                    string s1 = ss;
                    int ii = i, jj = j;
                    while(check(ii, jj) && s[ii][jj] == 'O')
                    {
                        s1[pos(ii, jj)] = '.';
                        if(go(s1) == 0){
                            yes = 1;
                            goto g;
                        }
                        ii += c[k], jj += d[k];
                    }
                }
            }
        }
    }
    g:;
    return dp[h1] = yes;
}
main(){
    IO;
    if(LOCAL){
        freopen("inp.txt", "r", stdin);
        //freopen("out.txt", "w", stdout);
    }
    fill(dp, dp + (1 << 19), -1);
    string s[5];
    for(int i = 0; i < 5; i++){
        getline(cin, s[i]);
        for(int j = 0; j < s[i].size(); j++)
            if(s[i][j] == ' ')
                s[i][j] = '#';
        while(s[i].size() < 9)
            s[i] += '#';
    }
    string ss = get(s);
    for(int i = 0; i < ss.size(); i++){
        if(ss[i] != '#')
            positions.pb(i);
    }
    cout << ((go(ss)) ? "Karlsson" : "Lillebror");
    return 0;
}
