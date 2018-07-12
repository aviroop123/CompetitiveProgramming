#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef long double f80;
//#define int long long int
#define fi first
#define se second
#define pb emplace_back
#define forn(i, x, y) for(int i = x; i <= y; i++)
#define vi vector
#define pii pair

signed main(){
    //freopen("inp.txt", "r", stdin);
    int t;
    scanf("%d", &t);
    while(t--){
        int x1, x2;
        scanf("%d.%d", &x1, &x2);
        int x = x1 * 100 + x2;
        int n, g = 0, v;
        scanf("%d", &n);
        while(n--){
            scanf("%d", &v);
            v *= 100;
            while(!(v & 1)) v >>= 1;
            g = __gcd(g, v);
        }
        if(x % g)
            puts("no");
        else
            puts("yes");
    }
    return 0;
}
