#include <iostream>
#include <algorithm>
#include <queue>
#define MAXEDGE 1000
#define MAXVERTEX 1000
using namespace std;
const int MAXV = 1000;
const int MAXE = 1000000;
struct Edge {
	int v;
	Edge *next;
} *vertex[MAXV],edge[MAXE],*cur;
int res[MAXV],deg[MAXV];
void clear() {
	memset(deg,0,sizeof deg);
	memset(vertex,0,sizeof vertex);
	cur = edge;
}
void add(int u,int v) {
	++deg[v];
	cur->v = v;
	cur->next = vertex[u];
	vertex[u] = cur++;
}
bool topsort(int n) {
  int ptr(0);
  for(int i(0);i!=n;++i)
		if(deg[i]==0)
			res[ptr++] = i;
	for(int i(0);i!=ptr;++i) {
		int u = res[i];
		for(Edge *e = vertex[u];e;e = e->next) {
			if(--deg[e->v]==0)
				res[ptr++] = e->v;
		}
	}
	return ptr==n;
}
main() {
	return 0;
}
