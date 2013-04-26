#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#define INF (0x7f7f7f)
#define MAXV (10010)
#define MAXE (20010)
#define M (1<<14)
#define MAX (1<<15)
using namespace std;
int vertex[MAXV];
struct Edge {
  int v,next;
} edge[MAXE];
struct _Edge {
  int u,v,w;
} e[MAXV];
int last_p;
int f[MAXV],size[MAXV],heavy[MAXV],dep[MAXV],head[MAXV],pos[MAXV];
int tree[MAX];
void _add(int u,int v) {
  edge[last_p].v = v;
  edge[last_p].next = vertex[u];
  vertex[u] = last_p++;
}
void add(int u,int v) {
  _add(u,v);
  _add(v,u);
}
int query(int s,int t) {
  int res(-INF);
  for(s = s+M-1,t = t+M+1;s^t^1;s>>=1,t>>=1) {
    if(~s&1) res = max(res,tree[s^1]);
    if( t&1) res = max(res,tree[t^1]);
  }
  return res;
}
void mod(int s,int val) {
  tree[s+=M] = val;
  for(s>>=1;s;s>>=1)
    tree[s] = max(tree[s<<1],tree[s<<1^1]);
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
  for(int i(0),p(0);i!=N;++i)
    if(f[i]==-1 || heavy[f[i]]!=i)
      for(int j = i;j!=-1;j = heavy[j])
        pos[j] = ++p, head[j] = i;
}
int qtree(int u,int v) {
  int res = (-INF);
  if(u==v) return 0;
  while(head[u]!=head[v]) {
    if(dep[head[u]]>dep[head[v]]) swap(u,v);
    res = max(res,query(pos[head[v]],pos[v]));
    v = f[head[v]];
  }
  if(dep[u]>dep[v]) swap(u,v);
  if(u!=v) res = max(res,query(pos[u]+1,pos[v]));
  return res;
}
void mtree(int i,int val) {
  mod(pos[e[i].v],val);
}
void init(int N) {
  last_p = 0;
  memset(vertex,-1,sizeof(vertex));
  memset(tree,0,sizeof(tree));
  for(int i(1);i!=N;++i) {
    scanf("%d%d%d",&e[i].u,&e[i].v,&e[i].w);
    --e[i].u,--e[i].v;
    add(e[i].u,e[i].v);
  }
  heavy_light(N);
  for(int i(1);i!=N;++i) {
    if(dep[e[i].u]>dep[e[i].v]) swap(e[i].u,e[i].v);
    mod(pos[e[i].v],e[i].w);
  }
}
//spoj 375
int main() {
  int _,N; cin>>_;
  char op[20];
  while(_-- && cin>>N) {
    init(N);
    while(scanf("%s",op) && op[0]!='D') {
      int x,y; scanf("%d%d",&x,&y);
      if(op[0]=='Q') printf("%d\n",qtree(x-1,y-1));
      else mtree(x,y);
    }
  }
  return 0;
}
