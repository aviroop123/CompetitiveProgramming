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
#define int long long int

const int mod = 1e9 + 7;
const int N = 2000005;
const int inf = 1e12;

int a[N], b[N], c[N];
int l1, r1, l2, r2;
bool extend_h(int x){
    for(int i = l2; i <= r2; i++){
        if(!a[abs(x) + abs(i)])
            return 0;
        a[abs(x) + abs(i)]--;
    }
    return 1;
}
bool extend_v(int x){
    for(int i = l1; i <= r1; i++){
        if(!a[abs(x) + abs(i)])
            return 0;
        a[abs(x) + abs(i)]--;
    }
    return 1;
}
main(){
    IO;
    if(LOCAL){
        freopen("inp.txt", "r", stdin);
        //freopen("out.txt", "w", stdout);
    }
    int n;
    cin >> n;
    forn(i, 1, n)
    {
        int x;
        cin >> x;
        a[x]++;
    }
    if(!a[0])
        return cout << -1, 0;
    a[0]--;
    l2 = 0, r2 = 0, l1 = 0, r1 = 0;
    int x = 1;
    while(a[x] == 4){ // correct
        l1--;
        if(!extend_h(l1))
            return cout << -1, 0;
        r1++;
        if(!extend_h(r1))
            return cout << -1, 0;
        l2--;
        if(!extend_v(l2))
            return cout << -1, 0;
        r2++;
        if(!extend_v(r2))
            return cout << -1, 0;
        x++;
    }
    while(a[x] == 3){ // correct
        l1--;
        if(!extend_h(l1))
            return cout << -1, 0;
        r1++;
        if(!extend_h(r1))
            return cout << -1, 0;
        l2--;
        if(!extend_v(l2))
            return cout << -1, 0;
        x++;
    }
    copy(a, a + n, b);
    bool yes = 1;
    int xx = x;
    int p1 = l1, p2 = l2, q1 = r1, q2 = r2;
    while(a[x] == 2){
        l1--;
        if(!extend_h(l1))
            yes = 0;
        l2--;
        if(!extend_v(l2))
            yes = 0;
        x++;
    }
    bool yes1 = yes;
    int xx2 = x;
    int a1 = l1, a2 = l2, b1 = r1, b2 = r2;
    copy(a, a + n, c);
    while(a[x] == 1){
        l1--;
        if(!extend_h(l1))
            yes = 0;
        x++;
    }
    for(int i = 0; i < n; i++){
        if(a[i]){
            yes = 0;
        }
    }
    if(!yes){
        yes = yes1;
        x = xx2;
        l1 = a1, l2 = a2, r1 = b1, r2 = b2;
        copy(c, c + n, a);
        while(a[x] == 1){
            l2--;
            if(!extend_v(l2))
                yes = 0;
            x++;
        }
        for(int i = 0; i < n; i++){
        if(a[i]){
            yes = 0;
        }
        }
    }
    if(!yes){
        yes = 1;
        copy(b, b + n, a);
        x = xx;
        l1 = p1, l2 = p2, r1 = q1, r2 = q2;
        while(a[x] == 2){
        l1--;
        if(!extend_h(l1))
            yes = 0;
        r1++;
        if(!extend_h(r1))
            yes = 0;
        x++;
        }
        while(a[x] == 1){
        l1--;
        if(!extend_h(l1))
            yes = 0;
        x++;
        }
        for(int i = 0; i < n; i++){
        if(a[i]){
            yes = 0;
        }
        }
    }
    if(!yes)
        return cout << -1, 0;
    assert((r2 - l2 + 1) * (r1 - l1 + 1) == n);
    cout << r2 - l2 + 1 << " " << r1 - l1 + 1 << endl;
    cout << -l2 + 1 << " " << -l1 + 1 << endl;
    return 0;
}
