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

int md[500];
signed main(){
    //freopen("inp.txt", "r", stdin);
    ios :: sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int n;
    cin >> n;
    for(int i = 0; i < 500; i++)
        md[i] = -1;
    for(int i = 0; i <= 8; i++){
        for(int j = 0; j <= 48; j++){
            int val = 4 * i + 9 * j;
            val %= 49;
            if(i + j > n) continue;
            md[val] = max(md[val], n - i - j);
        }
    }
    int ans = 0;
    for(int i = 0; i < 500; i++){
        ans += md[i] + 1;
    }
    cout << ans;
    return 0;
}
