// Solution Idea : First I make pairs (a, b) and sort them according to a first, then b. Then the first player will always take the rightmost element in the worst case.
// Let 1 denote that item is taken by 2nd player and 0 denote the opposite. So you would get a sequence of 01010101...0 . Now,
// my solution uses the fact that you can only shift 1's to the left. So I take greedily from the first. I maintain a priority queue
// which gives me the maximum value of b that I can take. 

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

const int N = 100005;
priority_queue<int,vector<int>> p;
pair<int,int> a[N];
signed main(){
    //freopen("inp.txt", "r", stdin);
    ios :: sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int n;
    cin >> n;
    for(int i = 1; i <= n; i++){
        cin >> a[i].fi;
    }
    for(int i = 1; i <= n; i++){
        cin >> a[i].se;
    }
    sort(a + 1,a + n + 1);
    int ans = 0;
    for(int i = 1; i <= n; i++){
        p.push(a[i].se);
        if(((n - i) & 1))
        {
            ans += p.top();
            p.pop();
        }
    }
    cout << ans;
    return 0;
}
