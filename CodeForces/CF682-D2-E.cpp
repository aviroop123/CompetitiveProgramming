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
#define f80 double
#define LOCAL 0

typedef long long int ll;
#define int long long int

#define double long double

const int mod = 1e9 + 7;
const int N = 55;
const int inf = 1e9;

#define REMOVE_REDUNDANT

typedef double T;
const T EPS = 1e-7;
struct PT { 
  T x, y; 
  PT() {} 
  PT(T x, T y) : x(x), y(y) {}
  bool operator<(const PT &rhs) const { return make_pair(y,x) < make_pair(rhs.y,rhs.x); }
  bool operator==(const PT &rhs) const { return make_pair(y,x) == make_pair(rhs.y,rhs.x); }
};

T cross(PT p, PT q) { return p.x*q.y-p.y*q.x; }
T area2(PT a, PT b, PT c) { return cross(a,b) + cross(b,c) + cross(c,a); }
T area(PT a, PT b, PT c) {return abs(area2(a, b, c));}

#ifdef REMOVE_REDUNDANT
bool between(const PT &a, const PT &b, const PT &c) {
  return (fabs(area2(a,b,c)) < EPS && (a.x-b.x)*(c.x-b.x) <= 0 && (a.y-b.y)*(c.y-b.y) <= 0);
}
#endif

void ConvexHull(vector<PT> &pts) {
  sort(pts.begin(), pts.end());
  pts.erase(unique(pts.begin(), pts.end()), pts.end());
  vector<PT> up, dn;
  for (int i = 0; i < pts.size(); i++) {
    while (up.size() > 1 && area2(up[up.size()-2], up.back(), pts[i]) >= 0) up.pop_back();
    while (dn.size() > 1 && area2(dn[dn.size()-2], dn.back(), pts[i]) <= 0) dn.pop_back();
    up.push_back(pts[i]);
    dn.push_back(pts[i]);
  }
  pts = dn;
  for (int i = (int) up.size() - 2; i >= 1; i--) pts.push_back(up[i]);
  
#ifdef REMOVE_REDUNDANT
  if (pts.size() <= 2) return;
  dn.clear();
  dn.push_back(pts[0]);
  dn.push_back(pts[1]);
  for (int i = 2; i < pts.size(); i++) {
    if (between(dn[dn.size()-2], dn[dn.size()-1], pts[i])) dn.pop_back();
    dn.push_back(pts[i]);
  }
  if (dn.size() >= 3 && between(dn.back(), dn[0], dn[1])) {
    dn[0] = dn.back();
    dn.pop_back();
  }
  pts = dn;
#endif
}

vector<PT> v;
vector<PT> pt;

main(){
    if(LOCAL){
        freopen("inp.txt", "r", stdin);
        //freopen("out.txt", "w", stdout);
    }
    int n, s;
    cin >> n >> s;
    forn(i, 1, n){
        PT p;
        cin >> p.x >> p.y;
        v.pb(p);
    }
    ConvexHull(v);
    pt.resize(v.size());
    copy(all(v), pt.begin());
    n = v.size();
    f80 max_area = -1, a = -1, b = -1, c = -1;
    forn(i, 0, n - 1){
        int pt1 = i, pt2 = (i + 2) % n;
        f80 ar = 0;
        while(area(v[i], v[(pt1 + 1) % n], v[pt2]) >= ar){
            pt1 = (pt1 + 1) % n;
            ar = area(v[i], v[pt1], v[pt2]);
            while(area(v[i], v[pt1], v[(pt2 + 1) % n]) >= ar){
                pt2++;
                ar = area(v[i], v[pt1], v[pt2]);
            }
        }
        if(max_area < ar){
            max_area = ar;
            a = i, b =  pt1, c = pt2;
        }
    }
    //cout << a << " " << b << " " << c << endl;
    cout << setprecision(0) << fixed;
    cout << pt[a].x + pt[b].x - pt[c].x << " " << pt[a].y + pt[b].y - pt[c].y << endl;
    cout << pt[b].x + pt[c].x - pt[a].x << " " << pt[b].y + pt[c].y - pt[a].y << endl;
    cout << pt[c].x + pt[a].x - pt[b].x << " " << pt[c].y + pt[a].y - pt[b].y << endl;
    return 0;
}
