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
#define f80 double
#define LOCAL 0
#define endl '\n'

typedef long long int ll;
//#define int long long int

const int mod = 1e9 + 7;
const int N = 5005;
const int inf = 2e9;

priority_queue<pii,vi<pii>,greater<pii>> q;
int a[N], x[N * 10];
bool vis[N * 10]; 
void preprocess(int n){
    forn(i, 0, a[1] - 1)
        x[i] = inf;
    x[0] = 0;
    q.push({0, 0});
    while(!q.empty()){
        pii t = q.top();
        q.pop();
        if(vis[t.se]) continue;
        vis[t.se] = 1;
        forn(i, 1, n){
            int k = (t.se + a[i]) % a[1];
            if(x[k] > t.fi + a[i]){
                x[k] = t.fi + a[i];
                q.push({x[k], k});
            }
        }
    }
}
signed main(){
    IO;
    if(LOCAL){
        freopen("inp.txt", "r", stdin);
    }
    int n;
    cin >> n;
    forn(i, 1, n)
    cin >> a[i];
    preprocess(n);
    int k;
    cin >> k;
    while(k--){
        int val;
        cin >> val;
        if(x[val % a[1]] <= val)
            cout << "TAK" << endl;
        else
            cout << "NIE" << endl;
    }
    return 0;
}
