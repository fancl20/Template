#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <set>
#define MAXV (100010)
#define MAXE (200010)
using namespace std;
typedef set<pair<int,int> > sp;
sp va[MAXV];
int vertex[MAXV];
struct Edge {
  int v,next;
} edge[MAXE];
int last_p;
int f[MAXV],size[MAXV],heavy[MAXV],dep[MAXV],head[MAXV],pos[MAXV],val[MAXV];
void _add(int u,int v) {
  edge[last_p].v = v;
  edge[last_p].next = vertex[u];
  vertex[u] = last_p++;
}
void add(int u,int v) {
  _add(u,v);
  _add(v,u);
}
void dfs(int u) {
  size[u] = 1;
  for(int i(vertex[u]);i!=-1;i = edge[i].next) {
    int v = edge[i].v;
    if(v==f[u]) continue;
    f[v] = u;
    dep[v] = dep[u]+1;
    dfs(v);
    size[u]+=size[v];
    if(heavy[u]==-1 || size[v]>size[heavy[u]])
      heavy[u] = v;
  }
}
void heavy_light(int N) {
  memset(heavy,-1,sizeof(heavy));
  f[0] = -1;
  dep[0] = 0;
  dfs(0);
  for(int i(0),p(1);i!=N;++i)
    if(f[i]==-1 || heavy[f[i]]!=i) {
      for(int j = i;j!=-1;j = heavy[j])
        pos[j] = p, head[j] = i;
      ++p;
    }
}
bool qtree(int u,int v,int val) {
  sp::iterator iter;
  while(head[u]!=head[v]) {
    if(dep[head[u]]>dep[head[v]]) swap(u,v);
    iter = va[pos[v]].upper_bound(make_pair(val,dep[v]));
    if(iter!=va[pos[v]].begin() && (--iter)->first==val) return true;
    v = f[head[v]];
  }
  if(dep[u]>dep[v]) swap(u,v);
  iter = va[pos[v]].upper_bound(make_pair(val,dep[v]));
  if(iter!=va[pos[v]].begin() && (--iter)->first==val && iter->second>=dep[u])
    return true;
  return false;
}
void init(int N) {
  last_p = 0;
  memset(vertex,-1,sizeof(vertex));
  for(int i(0);i!=N;++i) va[i].clear();
  for(int i(0);i!=N;++i) scanf("%d",&val[i]);
  for(int i(1);i!=N;++i) {
    int u,v;
    scanf("%d%d",&u,&v);
    add(u-1,v-1);
  }
  heavy_light(N);
  for(int i(0);i!=N;++i)
    va[pos[i]].insert(make_pair(val[i],dep[i]));
}
void mod(int u,int _val) {
  va[pos[u]].erase(make_pair(val[u],dep[u]));
  va[pos[u]].insert(make_pair(_val,dep[u]));
  val[u] = _val;
}
//BOJ 649
int main() {
  int _,N,M; cin>>_;
  char op[20];
  while(_-- && cin>>N>>M) {
    init(N);
    while(M-- && scanf("%s",op)) {
      int u,v,val;
      if(op[0]=='Q') {
        scanf("%d%d%d",&u,&v,&val);
        puts((qtree(u-1,v-1,val))?"Find":"NotFind");
      } else {
        scanf("%d%d",&u,&val);
        mod(u-1,val);
      }
    }
    puts("");
  }
  return 0;
}
