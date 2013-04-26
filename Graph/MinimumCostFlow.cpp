#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <cstring>
using namespace std;
const int INF = 0x3f3f3f3f;
const int MAXV = 1000;
const int MAXE = 1000000;
class cost_flow {
  public:
    void add(int u,int v,int c,int w) {
      _add(u,v,c, w, 1);
      _add(v,u,0,-w,-1);
    }
    void clear() {
      memset(vertex,0,sizeof vertex);
      cur = edge;
    }
    pair<int,int> SSP(int n,int s,int t) {
      flow = cost = dis = 0;
      while(modlabel(s,t,n))
        do memset(vis,0,sizeof vis);
        while(dfs(s,t,INF));
      return make_pair(flow,cost);
    }
  private:
    int dfs(int u,int t,int f) {
      if(u==t) return cost+=dis*f, flow+=f, f;
      int r = f; vis[u] = true;
      for(Edge *e = vertex[u];e;e = e->next)
        if(e->c && !e->w && !vis[e->v]) {
          int d = dfs(e->v,t,min(e->c,f));
          e->c-=d, e->rev->c+=d, r-=d;
          if(!r) return f;
        }
      return f-r;
    }
    bool modlabel(int s,int t,int n) {
      memset(d,0x3f,sizeof d); d[t] = 0;
      static queue<int> q; q.push(t);
      while(q.size()) {
        int dv,u = q.front(); q.pop();
        for(Edge *e = vertex[u];e;e = e->next)
          if(e->rev->c && (dv = d[u]-e->w)<d[e->v])
            d[e->v] = dv, q.push(e->v);
      }
      for(int i(0);i!=n;++i)
        for(Edge *e = vertex[i];e;e = e->next)
          e->w+=d[e->v]-d[i];
      dis+=d[s];
      return d[s]<INF;
    }
    void _add(int u,int v,int c,int w,int r) {
      cur->v = v;
      cur->c = c;
      cur->w = w;
      cur->rev = cur+r;
      cur->next = vertex[u];
      vertex[u] = cur++;
    }
    struct Edge {
      int v,c,w;
      Edge *rev,*next;
    } edge[MAXE],*cur,*vertex[MAXV];
    int flow,cost,dis,d[MAXV];
    bool vis[MAXV];
} G;
//ural 1076
int main() {
  int N,tmp,in[160][160],sum[160];
  cin>>N;
  G.clear();
  memset(sum,0,sizeof(sum));
  for(int i(0);i!=N;++i)
    for(int j(0);j!=N;++j)
      cin>>in[i][j], sum[j]+=in[i][j];
  for(int i(0);i!=N;++i)
    for(int j(0);j!=N;++j)
      G.add(i+1,j+1+N,1,sum[i]-in[j][i]);
  for(int i(0);i!=N;++i)
    G.add(0,i+1,1,0), G.add(i+1+N,2*N+1,1,0);
  cout<<G.SSP(2*N+2,0,2*N+1).second<<endl;
  return 0;
}
