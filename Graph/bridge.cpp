#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
const int MAXV = 110;
const int MAXE = 10010;
struct Edge {
	int v,l;
	Edge *next;
} edge[MAXE],*vertex[MAXV],*cur;
int DFN[MAXV],LOW[MAXV],f[MAXV],T;
bool added[MAXV];
void _add(int u,int v,int l) {
	cur->v = v;
	cur->l = l;
	cur->next = vertex[u];
	vertex[u] = cur++;
}
void add(int u,int v) {
	_add(u,v,cur-edge);
	_add(v,u,cur-edge-1);
}
void tarjan(int u) {
	LOW[u] = DFN[u] = ++T;
	for(Edge *e = vertex[u];e;e = e->next) {
		if(!DFN[e->v]) {
			f[e->v] = e->l;
			tarjan(e->v);
			LOW[u] = min(LOW[u],LOW[e->v]);
		} else if(e->l!=f[u])
			LOW[u] = min(LOW[u],DFN[e->v]);
	}
}
void clear() {
	memset(vertex,0,sizeof vertex);
	memset(DFN,0,sizeof DFN);
	memset(added,0,sizeof added);
	memset(f,-1,sizeof f);
	cur = edge;
	T = 0;
}
void bridge(int n) {
	int cnt(0);
	pair<int,int> ans[110];
	for(int i(0);i!=n;++i)
		for(Edge *e = vertex[i];e;e = e->next)
			if(DFN[i]<LOW[e->v])
				ans[cnt++] = make_pair(min(i,e->v),max(i,e->v));
	sort(ans,ans+cnt);
	printf("%d critical links\n",cnt);
	for(int i(0);i!=cnt;++i)
		printf("%d - %d\n",ans[i].first,ans[i].second);
	puts("");
}
int main() {
	int n,m,u,v;
	while(cin>>n) {
		clear();
		for(int i(0);i!=n;++i) {
			scanf("%d (%d)",&u,&m);
			added[u] = true;
			for(int j(0);j!=m;++j) {
				scanf("%d",&v);
				if(!added[v]) add(u,v);
			}
		}
		for(int i(0);i!=n;++i)
			if(!DFN[i]) tarjan(i);
		bridge(n);
	}
	return 0;
}
