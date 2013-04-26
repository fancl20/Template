#include <iostream>
#include <queue>
#include <algorithm>
#include <cstdio>
#define MAXEDGE (4010)
#define MAXVERTEX (1010)
#define INF (1u<<31-1)
using namespace std;
class shortest_path {
  public:
    shortest_path() {clear();}
    void add(int from,int to,int weight) {
      edge[last_p].v = to;
      edge[last_p].w = weight;
      edge[last_p].next = vertex[from];
      vertex[from] = last_p++;
    }
    int clear() {
      last_p = 0;
      fill_n(vertex,MAXVERTEX,-1);
    }
    int SPFA(int nv) {
      n = nv;
      bool added[MAXVERTEX];
      queue<int> q;
      fill_n(result,MAXVERTEX,INF);
      fill_n(added,MAXVERTEX,false);
      q.push(0);
      result[0] = 0;
      while(q.size()) {
        int cur(q.front());
        q.pop();
        added[cur] = false;
        for(int e(vertex[cur]);e!=-1;e = edge[e].next) {
          int v(edge[e].v);
          if((edge[e].w+result[cur])<result[v]) {
            result[v] = result[cur]+edge[e].w;
            if(!added[v]) {
              q.push(v);
              added[v] = true;
            }
          }
        }
      }
      return result[n-1];
    }
  private:
    struct Edge {
      int v,w,next;
    } edge[MAXEDGE];
    int last_p,n;
    int vertex[MAXVERTEX];
    int result[MAXVERTEX];
};
int main() {
  int T,N;
  shortest_path map;
  cin>>T>>N;
  for(int i(0);i!=T;++i) {
    int a,b,l;
    scanf("%d%d%d",&a,&b,&l);
    map.add(a-1,b-1,l);
    map.add(b-1,a-1,l);
  }
  cout<<map.SPFA(N)<<endl;
  return 0;
}
