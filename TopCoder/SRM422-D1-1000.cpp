#include<bits/stdc++.h>
using namespace std;

#define pb emplace_back
#define fi first
#define se second
#define all(x) x.begin(), x.end()
#define vi vector
#define IO ios :: sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define LOCAL 1
#define forn(i, l, r) for(int i = l; i <= r; i++)
#define pii pair<int,int>
#define f80 long double

typedef long long int ll;
//#define int long long int

const int mod = 1e9 + 7;
const int N = 35;
const int inf = 1e8;

typedef vector<int> VI;
typedef vector<VI> VVI;

const int INF = 1e9;

struct maxflow {
  int N;
  VVI cap, flow;
  VI dad, Q;

  maxflow(int N) :
    N(N), cap(N, VI(N)), flow(N, VI(N)), dad(N), Q(N) {}

  void addEdge(int from, int to, int cap) {
    //cout << from << " " << to << " " << cap << endl;
    this->cap[from][to] += cap;
  }

  int BlockingFlow(int s, int t) {
    fill(dad.begin(), dad.end(), -1);
    dad[s] = -2;

    int head = 0, tail = 0;
    Q[tail++] = s;
    while (head < tail) {
      int x = Q[head++];
      for (int i = 0; i < N; i++) {
        if (dad[i] == -1 && cap[x][i] - flow[x][i] > 0) {
          dad[i] = x;
          Q[tail++] = i;
        }
      }
    }

    if (dad[t] == -1) return 0;

    int totflow = 0;
    for (int i = 0; i < N; i++) {
      if (dad[i] == -1) continue;
      int amt = cap[i][t] - flow[i][t];
      for (int j = i; amt && j != s; j = dad[j])
        amt = min(amt, cap[dad[j]][j] - flow[dad[j]][j]);
      if (amt == 0) continue;
      flow[i][t] += amt;
      flow[t][i] -= amt;
      for (int j = i; j != s; j = dad[j]) {
        flow[dad[j]][j] += amt;
        flow[j][dad[j]] -= amt;
      }
      totflow += amt;
    }

    return totflow;
  }

  int getflow(int source, int sink) {
    int totflow = 0;
    while (int flow = BlockingFlow(source, sink))
      totflow += flow;
    return totflow;
  }
};
int c[4] = {1, -1, 0, 0}, d[4] = {0, 0, -1, 1};
class WorkersOnPlane{
public:
    vi<string> f;
    int dist[N][N], n, m, k;
    queue<pii> q;
    bool vis[N][N];
    bool check(int i,int j){
        return i >= 0 && i < n && j >= 0 && j < m;
    }
    int h(int i,int j){
        return i * m + j;
    }
    void bfs(int x,int y, maxflow &mf){
        q.emplace(x, y);
        for(int i = 0; i < n; i++){
            fill(dist[i], dist[i] + m, inf);
            fill(vis[i], vis[i] + m, 0);
        }
        vis[x][y] = 1;
        dist[x][y] = 0;
        while(!q.empty()){
            pii u = q.front();
            q.pop();
            for(int k = 0; k < 4; k++){
                int ii = u.fi + c[k], jj = u.se + d[k];
                if(check(ii, jj) && !vis[ii][jj]){
                    vis[ii][jj] = 1;
                    dist[ii][jj] = dist[u.fi][u.se] + 1;
                    if(f[ii][jj] == '.')
                        q.emplace(ii, jj);
                }
            }
        }
        /*for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++)
                cout << dist[i][j] << " ";
            cout << endl;
        }*/
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                if(dist[i][j] <= k){
                    if(f[i][j] == 'G')
                        mf.addEdge(h(i, j), h(x, y), 1);
                    else if(f[i][j] == 'S')
                        mf.addEdge(h(x, y) + n * m, h(i, j), 1);
                }
            }
        }
        mf.addEdge(h(x, y), h(x, y) + n * m, 1);
    }
    int howMany(vi<string> _m, int _k){
        f = _m, k = _k;
        n = f.size(), m = f[0].size();
        maxflow mf(2 * n * m + 5);
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                if(f[i][j] == 'W'){
                    bfs(i, j, mf);
                }
                else if(f[i][j] == 'G')
                    mf.addEdge(2 * n * m + 1, h(i, j), 1);
                else if(f[i][j] == 'S')
                    mf.addEdge(h(i, j), 2 * n * m + 2, 1);
            }
        }
        return mf.getflow(2 * n * m + 1,2 * n * m + 2);
    }
};
