#include <iostream>
#include <cstdio>
#include <stack>
#include <algorithm>
#include <cstring>
using namespace std;
const int MAXV = 40000;
const int MAXE = 400000;
struct Edge {
  int v;
	Edge *next;
} edge[MAXE],*vertex[MAXV],*cur;
int DFN[MAXV],col[MAXV],T;
bool ins[MAXV];
stack<int> s;
int dfs(int u) {
  ins[u] = true;
  s.push(u);
  int low = DFN[u] = ++T;
  for(Edge *e = vertex[u];e;e = e->next) {
    if(!DFN[e->v])
      low = min(low,dfs(e->v));
    else if(ins[e->v])
      low = min(low,DFN[e->v]);
  }
  if(low==DFN[u])
    for(int v(-1);u!=v;s.pop()) {
			v = s.top();
      col[v] = u;
      ins[v] = false;
    }
  return low;
}
void init() {
	memset(vertex,0,sizeof vertex);
	cur = edge;
}
void tarjan(int n) {
	memset(ins,0,sizeof ins);
	memset(DFN,0,sizeof DFN);
	memset(col,0,sizeof col);
	T = 0;
  for(int u(0);u!=n;++u)
    if(!DFN[u]) dfs(u);
}
void add(int u,int v) {
	cur->v = v;
	cur->next = vertex[u];
	vertex[u] = cur++;
}
bool vis[MAXV];
int val[MAXV],nval[MAXV],dp[MAXV];
void dfs2(int u) {
	vis[u] = true;
	int ma(0);
	for(Edge *e = vertex[u];e;e = e->next) {
		if(!vis[col[e->v]]) dfs2(col[e->v]);
		ma = max(ma,dp[col[e->v]]);
	}
	dp[u] = ma+nval[u];
}
void topsort(int n) {
	memset(vis,0,sizeof vis);
	for(int i(0);i!=n;++i)
		if(!vis[col[i]]) dfs2(col[i]);
}
int main() {
	int n,m;
	while(cin>>n>>m) {
		init();
		for(int i(0);i!=n;++i)
			scanf("%d",&val[i]);
		for(int i(0);i!=m;++i) {
			int u,v;
			scanf("%d%d",&u,&v);
			add(u,v);
		}
		tarjan(n);
		memset(nval,0,sizeof nval);
		for(int i(0);i!=n;++i) {
			if(val[i]>0) nval[col[i]]+=val[i];
			if(col[i]!=i)
				for(Edge *e = vertex[i];e;e = e->next)
					add(col[i],e->v);
		}
		memset(dp,0,sizeof dp);
		topsort(n);
		cout<<*max_element(dp,dp+n)<<'\n';
	}
  return 0;
}
