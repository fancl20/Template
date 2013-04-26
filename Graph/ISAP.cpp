#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#define FORE(e,u) for(Edge *e = vertex[u];e;e = e->next)
#define MS(x,v) memset(x,v,sizeof x)
const int MAXV = 1500;
const int MAXE = 160000;
using namespace std;
class flow {
  public:
    flow() { clear(); }
    void clear() {
      ptr = edge;
      MS(vertex,0);
    }
    void add(int u,int v,int c) {
      _add(u,v,c, 1);
      _add(v,u,0,-1);
    }
    int ISAP(int s,int t) {
      int ret(0);
      MS(h,0); MS(gap,0);
      gap[0] = MAXV;
      while(h[s]!=MAXV) ret+=dfs(s,s,t,~0u>>1);
      return ret;
    }
  private:
    int dfs(int u,int s,int t,int f) {
      if(u==t) return f;
      int r = f;
      FORE(e,u) if(e->c && h[e->v]+1==h[u]) {
        int d = dfs(e->v,s,t,min(r,e->c));
        e->c-=d; e->rev->c+=d; r-=d;
        if(h[s]==MAXV || !r) return f-r;
      }
      if(f==r) modlable(u,s,t);
      return f-r;
    }
    void modlable(int u,int s,int t) {
      int mh(MAXV);
      FORE(e,u) if(e->c) mh = min(mh,h[e->v]+1);
      if(!--gap[h[u]]) h[s] = MAXV; else ++gap[h[u] = mh];
    }
    void _add(int u,int v,int c,int r) {
      ptr->v = v;
      ptr->c = c;
      ptr->rev = ptr+r;
      ptr->next = vertex[u];
      vertex[u] = ptr++;
    }
    struct Edge {
      int v,c;
      Edge *next,*rev;
    } edge[MAXE],*ptr,*vertex[MAXV];
    int h[MAXV],gap[MAXV];
} g;
int main() {
  return 0;
}