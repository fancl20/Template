#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <stack>
#include <algorithm>
#include <utility>
#define MAX_VERTEX 100
#define MAX_EDGE 10000
using namespace std;
struct Edge {
  int v,next;
} edge[MAX_EDGE];
int last_p(0);
int vertex[MAX_VERTEX];
int DFN[MAX_VERTEX],col[MAX_VERTEX];
bool in_stack[MAX_VERTEX],choose[MAX_VERTEX];
int T(0),last_res(0);
stack<int> s;
int DFS(int u,int n) {
  in_stack[u] = true;
  s.push(u);
  int low = DFN[u] = ++T;
  for(int e(vertex[u]);e!=-1;e = edge[e].next) {
    int v(edge[e].v);
    if(!DFN[v])
      low = min(low,DFS(v));
    else if(in_stack[v])
      low = min(low,DFN[v]);
  }
  if(low==DFN[u]) {
    for(int v(-1);u!=v;s.pop()) {
      col[v = s.top()] = u;
      in_stack[v] = false;
      choose[u] |= choose[col[v]];
      for(int e(vertex[v]);!choose[v] && e!=-1;e = edge[e].next)
        choose[u] |= choose[col[edge[e].v]];
    }
  }
  return low;
}
void tarjan(int n) {
  fill_n(choose,MAX_VERTEX,false);
  fill_n(in_stack,MAX_VERTEX,false);
  fill_n(DFN,MAX_VERTEX,0);
  fill_n(col,MAX_VERTEX,-1);
  T = 0;
  for(int u(0);u!=n;++u)
    if(!DFN[u]) DFS(u,n);
}
int main() {
  return 0;
}
