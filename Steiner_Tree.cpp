#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
#define MS(x,v) memset(x,v,sizeof x)
const int MAXV = 5000;
const int MAXE = 100000;
const int MAX = 1<<8;
const int INF = 0x3f3f3f3f;
using namespace std;
int dp[MAXV][MAX],g[MAXV];
struct Edge {
  int v,w;
  Edge *next;
} edge[MAXE],*cur;
Edge *vertex[MAXV];
void _add(int u,int v,int w) {
  cur->v = v;
  cur->w = w;
  cur->next = vertex[u];
  vertex[u] = cur++;
}
void add(int u,int v,int w) {
  _add(u,v,w);
  _add(v,u,w);
}
void clear() {
  MS(g,0); MS(vertex,0);
  cur = edge;
}
namespace steiner_tree {
  inline bool update(int u,int s,int w) {
	if(w>=dp[u][s]) return false;
	return dp[u][s] = w, true;
  }
  queue<int> q;
  bool in[MAXV][MAX];
  void spfa() {
    while(q.size()) {
      int u = q.front()/MAX,s = q.front()%MAX; q.pop();
      in[u][s] = false;
      for(Edge *e = vertex[u];e;e = e->next)
        if( update(e->v,s|g[e->v],dp[u][s]+e->w) &&
            s==(s|g[e->v]) && !in[e->v][s])
          q.push(e->v*MAX+s), in[e->v][s] = true;
    }
  }
  void run(int n,int k) {
    MS(dp,0x3f); MS(in,0);
    while(!q.empty()) q.pop();
    for(int i(0);i!=n;++i)  dp[i][g[i]] = 0;
    for(int s(0);s!=(1<<k);++s,spfa())
      for(int u(0);u!=n;++u) {
        for(int x(s);x;x = s&(x-1))
          dp[u][s] = min(dp[u][s],dp[u][x|g[u]]+dp[u][s-x|g[u]]);
        if(dp[u][s]<INF) q.push(u*MAX+s), in[u][s] = true;
      }
  }
}
//hdu 3311
int main() {
  int n,m,p,w,u,v;
  while(cin>>n>>m>>p) {
    clear();
    for(int i(0);i!=n+m;++i) {
      scanf("%d",&w);
      add(i,n+m,w);
    }
    for(int i(0);i!=p;++i) {
      scanf("%d%d%d",&u,&v,&w);
      add(u-1,v-1,w);
    }
    g[n+m] = 1<<n;
    for(int i(0);i!=n;++i)
      g[i] = 1<<i;
    steiner_tree::run(n+m+1,n+1);
    cout<<dp[0][(1<<n+1)-1]<<'\n';
  }
  return 0;
}