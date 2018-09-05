#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef long double f80;
#define int long long int
#define pb push_back
#define fi first
#define se second
#define all(x) x.begin(), x.end()
#define fr(i, a, b) for(int i = a; i <= b; i++)
#define IO ios :: sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define endl '\n'
#define vi vector

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

  void AddEdge(int from, int to, int cap) {
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

const int N = 405;
int a[N], b[N];
map<int,int> U, V;
vi<pair<int,int>> u, v;

signed main(){
    //freopen("inp.txt", "r", stdin);
    IO;
    int t;
    cin >> t;
    while(t--){
        U.clear(), V.clear();
        int n;
        cin >> n;
        fr(i, 1, n) cin >> a[i];
        fr(i, 1, n) cin >> b[i];
        fr(i, 1, n){
            fr(j, 1, n){
                int g = __gcd(a[i], b[j]);
                if(a[i] < b[j] && g > 1)
                    U[g]++;
                if(a[i] > b[j] && g > 1)
                    V[g]++;
            }
        }
        int n1 = U.size(), n2 = V.size();
        PushRelabel mf(n1 + n2 + 5);
        u.clear(), v.clear();
        for(auto it : U){
            u.pb(it);
        }
        for(auto it : V){
            v.pb(it);
        }
        fr(i, 1, n1){
            mf.AddEdge(0, i, u[i - 1].se);
            fr(j, 1, n2){
                int g = __gcd(u[i - 1].fi, v[j - 1].fi);
                if(g > 1)
                    mf.AddEdge(i, n1 + j, 1e9);
            }
        }
        fr(i, 1, n2){
            mf.AddEdge(n1 + i, n1 + n2 + 2, v[i - 1].se);
        }
        cout << mf.GetMaxFlow(0, n1 + n2 + 2) << endl;
    }
    return 0;
}
