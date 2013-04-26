#include <iostream>
#include <algorithm>
#define MAXEDGE 1000
#define MAXVERTEX 1000
using namespace std;
struct Edge {
  int p;
  int next;
};
class Foward_Star {
  public:
    Foward_Star() {clear();}
    int add(int from,int to) {
      edge[last_p].p = to;
      edge[last_p].next = vertex[from];
      return vertex[from] = last_p++;
    }
    int next_edge(int cur) {return edge[cur].next;}
    int get_edge(int p) {return vertex[p];}
    void clear() {
      for(int i(0);i!=MAXVERTEX;++i) vertex[i] = -1;
      last_p = 0;
    }
    Edge edge[MAXEDGE+10];
  private:
    int vertex[MAXVERTEX+10];
    int last_p;
};

Foward_Star map;
int in_degree[MAXVERTEX];
int result[MAXVERTEX]; //0 degree points
int p;
bool topsort(int m) {
  p = 0;
  fill_n(result,m,-1);
  for(int i(0);i!=m;++i)
    if(in_degree[i]==0) result[p++] = i;
  for(int q(0);q!=m && result[q]!=-1;++q) {
    for(int i(map.get_edge(result[q]));i!=-1;i = map.edge[i].next) {
      int cur(map.edge[i].p);
      if(--in_degree[cur]==0)
        result[p++] = cur;
    }
  }
  if(p!=m) return false;
  else return true;
}
main() {
  int m,temp;
  cin>>m;
  for(int i(0);i!=m;++i) {
    while (cin>>temp) {
      if(temp==0) break;
      map.add(i,temp-1);
      /**/
      ++in_degree[temp-1];
    }
  }
  topsort(m);
  for(int i(0);i!=m;++i) cout<<result[i]+1<<" ";
  cout<<endl;
  return 0;
}
