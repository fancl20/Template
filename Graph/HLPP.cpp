#include <iostream>
#include <cstdio>
#include <algorithm>
#include <utility>
#include <queue>
#define INF (0x3f3f3f)
#define MAXV (6000)
#define MAXE (70000)
using namespace std;
class network_flow {
  public:
    network_flow() {clear();}
    void add(int u,int v,int cap) {
      _add(u,v,cap);
      _add(v,u,0);
    }
    void add2(int u,int v,int cap) {
      _add(u,v,cap);
      _add(v,u,cap);
    }
    void clear() {
      memset(vertex,-1,sizeof(vertex));
      memset(h,0,sizeof(h));
      memset(exc,0,sizeof(exc));
      memset(gap,0,sizeof(gap));
      memset(added,0,sizeof(added));
      last_p = 0;
    }
    int HLPP(int _n) {
      n = _n;
      init();
      return push_relable();
    }
  private:
    void push(int u,int i) {
      Edge &e = edge[i],&rev = edge[i^1];
      int d = min(e.c,exc[u]);
      e.c -= d; rev.c += d;
      exc[u] -= d; exc[e.v] += d;
      if(!added[e.v]) h[e.v]>=h[Q.size()? Q.front():0]?
        Q.push_front(e.v): Q.push_back(e.v);
      added[e.v] = true;
    }
    void relable(int u,int min_h) {
      int tmp;
      if(h[u]<n && --gap[tmp = h[u]]==0)
        for(int i(0);i!=n;++i) if(h[i]>tmp && h[i]<n)
          --gap[h[i]], h[i] = n;
      if((h[u] = min_h+1) <n+1) ++gap[h[u]];
    }
    void BFS() {
      bool v[MAXV];
      fill_n(v,MAXV,false);
      queue<int> q; v[n-1] = v[0] = true; q.push(n-1);
      while(q.size()) {
        int u = q.front(); q.pop();
        for(int i(vertex[u]);i!=-1;i = edge[i].next) {
          Edge &e = edge[i],&rev = edge[i^1];
          if(!v[e.v] && rev.c)
            v[e.v] = true, ++gap[h[e.v] = h[u]+1], --gap[0], q.push(e.v);
        }
      }
    }
    void init() {
      h[0] = gap[0] = n;
      added[0] = added[n-1] = true;
      BFS();
      for(int i(vertex[0]);i!=-1;i = edge[i].next) {
        exc[0] = INF;
        if(edge[i].c) push(0,i);
      }
    }
    long long push_relable() {
      while(Q.size()) {
        while(Q.size() && Q.front()>n) Q.pop_front();
        if(Q.empty()) break;
        int u(Q.front()); Q.pop_front(); added[u] = false;
        while(exc[u]>0) {
          int min_h(INF);
          for(int i(vertex[u]);i!=-1 && exc[u]>0;i = edge[i].next) {
            Edge &e = edge[i];
            if(e.c && h[u]==h[e.v]+1) push(u,i);
            else if(e.c && min_h>h[e.v])  min_h = h[e.v];
          }
          if(exc[u]>0) relable(u,min_h);
        }
      }
      return exc[n-1];
    }
    void _add(int u,int v,int c) {
      edge[last_p].v = v;
      edge[last_p].c = c;
      edge[last_p].next = vertex[u];
      vertex[u] = last_p++;
    }
    deque<int> Q;
    int vertex[MAXV],h[MAXV],exc[MAXV],gap[MAXV];
    bool added[MAXV];
    struct Edge {
      int v,c,next;
    } edge[MAXE];
    int last_p,n;
};
network_flow G;
int main() {
  int N,M,u,v,c1,c2;
  while(cin>>N>>M) {
    G.clear();
    for(int i(0);i!=N;++i) {
      scanf("%d%d",&c1,&c2);
      G.add(0,i+1,c1);
      G.add(i+1,N+1,c2);
    }
    for(int i(0);i!=M;++i) {
      scanf("%d%d%d",&u,&v,&c1);
      G.add2(u,v,c1);
    }
    cout<<G.HLPP(N+2)<<'\n';
  }
  return 0;
}
