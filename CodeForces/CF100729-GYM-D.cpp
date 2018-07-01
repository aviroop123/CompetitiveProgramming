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

typedef long long LL;

struct Edge {
  int from, to, cap, flow, index;
  Edge(int from, int to, int cap, int flow, int index) :
    from(from), to(to), cap(cap), flow(flow), index(index) {}
};

struct PushRelabel {
  int N;
  vector<vector<Edge> > G;
  vector<LL> excess;
  vector<int> dist, active, count;
  queue<int> Q;

  PushRelabel(int N) : N(N), G(N), excess(N), dist(N), active(N), count(2*N) {}

  void AddEdge(int from, int to, int cap = 1) {
    G[from].push_back(Edge(from, to, cap, 0, G[to].size()));
    if (from == to) G[from].back().index++;
    G[to].push_back(Edge(to, from, 0, 0, G[from].size() - 1)); // for bidirectional set cap.
  }

  void Enqueue(int v) { 
    if (!active[v] && excess[v] > 0) { active[v] = true; Q.push(v); } 
  }

  void Push(Edge &e) {
    int amt = min(excess[e.from], LL(e.cap - e.flow));
    if (dist[e.from] <= dist[e.to] || amt == 0) return;
    e.flow += amt;
    G[e.to][e.index].flow -= amt;
    excess[e.to] += amt;    
    excess[e.from] -= amt;
    Enqueue(e.to);
  }
  
  void Gap(int k) {
    for (int v = 0; v < N; v++) {
      if (dist[v] < k) continue;
      count[dist[v]]--;
      dist[v] = max(dist[v], N + 1);
      count[dist[v]]++;
      Enqueue(v);
    }
  }

  void Relabel(int v) {
    count[dist[v]]--;
    dist[v] = 2*N;
    for (int i = 0; i < G[v].size(); i++) 
      if (G[v][i].cap - G[v][i].flow > 0)
    dist[v] = min(dist[v], dist[G[v][i].to] + 1);
    count[dist[v]]++;
    Enqueue(v);
  }

  void Discharge(int v) {
    for (int i = 0; excess[v] > 0 && i < G[v].size(); i++) Push(G[v][i]);
    if (excess[v] > 0) {
      if (count[dist[v]] == 1) 
    Gap(dist[v]); 
      else
    Relabel(v);
    }
  }

  LL GetMaxFlow(int s, int t) {
    count[0] = N-1;
    count[N] = 1;
    dist[s] = N;
    active[s] = active[t] = true;
    for (int i = 0; i < G[s].size(); i++) {
      excess[s] += G[s][i].cap;
      Push(G[s][i]);
    }
    
    while (!Q.empty()) {
      int v = Q.front();
      Q.pop();
      active[v] = false;
      Discharge(v);
    }
    
    LL totflow = 0;
    for (int i = 0; i < G[s].size(); i++) totflow += G[s][i].flow;
    return totflow;
  }
};
vector<int> v[505][505];
int c[4] = {1, -1, 0, 0};
int d[4] = {0, 0, 1, -1};
string s[505];
int n, m;
bool check(int i,int j){
    return i >= 0 && i < n && j >= 0 && j < m;
}
signed main(){
    //freopen("inp.txt", "r", stdin);
    ios :: sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int t;
    cin >> t;
    while(t--){
        cin >> n >> m;
        int w = 0, b = 0;
        for(int i = 0; i < n; i++){
            cin >> s[i];
            for(int j = 0; j < m; j++){
                v[i][j].clear();
                if(s[i][j] == 'B')
                    b++;
                else if(s[i][j] == 'W')
                    w++;
            }
        }
        if(w != 2 * b)
        {
            cout << "NO" << endl;
            continue;
        }
        int p = 0;
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                if(s[i][j] == 'B'){
                    p++;
                    v[i][j].pb(p);
                    p++;
                    v[i][j].pb(p);
                }
                else if(s[i][j] == 'W'){
                    p++;
                    v[i][j].pb(p);
                }
            }
        }
        PushRelabel g(p + 5);
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                if(s[i][j] == 'B')
                {
                for(int k = 0; k < 2; k++)
                    g.AddEdge(0, v[i][j][k]);
                for(int k = 0; k < 4; k++){
                    int ii = i + c[k], jj = j + d[k];
                    if(check(ii, jj) && s[ii][jj] == 'W')
                        g.AddEdge(v[i][j][k / 2], v[ii][jj][0]);
                }
                }
                else if(s[i][j] == 'W'){
                    g.AddEdge(v[i][j][0], p + 1);
                }
            }
        }
        cout << ((g.GetMaxFlow(0, p + 1) == w) ? "YES" : "NO") << endl;
    }
    return 0;
}
