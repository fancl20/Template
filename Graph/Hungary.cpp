#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cctype>
using namespace std;
const int MAXE = 50000;
const int MAXV = 410;
struct Edge {
  int v;
  Edge *next;
} edge[MAXE],*ptr,*vertex[MAXV];
void add(int u,int v) {
  ptr->v = v;
  ptr->next = vertex[u];
  vertex[u] = ptr++;
}
void clear() {
  memset(vertex,0,sizeof vertex);
  ptr = edge;
}
bool vis[MAXV];
int l[MAXV];
bool DFS(int u) {
  for(Edge* e = vertex[u];e;e = e->next)
    if(!vis[e->v]) {
      vis[e->v] = true;
      if(l[e->v]==-1 || DFS(l[e->v])) {
        l[e->v] = u;
        return true;
      }
    }
  return false;
}
int calc(int n) {
  int res(0);
  memset(l,-1,sizeof l);
  do {
    memset(vis,0,sizeof vis);
    if(DFS(--n)) ++res;
  } while(n>0);
  return res;
}
//ZOJ 3646
int main() {
  int n,c;
  while(cin>>n) {
    clear();
    for(int i(0);i!=n;++i)
      for(int j(0);j!=n;++j) {
        while(isspace(c = getchar()));
        if(c=='U') add(i,j+n);
      }
    if(calc(n)==n) cout<<"YES"<<'\n';
    else cout<<"NO"<<'\n';
  }
  return 0;
}
