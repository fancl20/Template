#include <iostream>
#include <cmath>
#define MAX (10000)
using namespace std;
int SG[MAX],X(6);
int DFS(int u) {
  if(~SG[u]) return SG[u];
  bool mark[MAX];
  memset(mark,0,sizeof(mark));
  for(int i(0);(int)pow((double)X,i)<=u;++i)
    mark[DFS(u-(int)pow((double)X,i))] = true;
  for(int i(0);;++i)
    if(!mark[i]) return SG[u] = i;
}
int main() {
    memset(SG,-1,sizeof(SG));
    SG[0] = 0;
}
