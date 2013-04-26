#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#define MAXV (55)
using namespace std;
int prim(int g[][],int n) {
  int dis[MAXV],id[MAXV],res(0);
  memset(dis,0x3f,sizeof(dis));
  for(int i(0);i!=n;++i) id[i] = i;
  for(int i(0);i!=n-1;++i) {
    int p = i+1;
    //如果 g[i][j]==0 表示不联通需要判断
    for(int j(i+1);j!=n;++j) {
      dis[id[j]] = min(dis[id[j]],g[id[i]][id[j]]);
      if(dis[id[p]]>dis[id[j]]) p = j;
    }
    res+=dis[id[p]];
    swap(id[i+1],id[p]);
  }
  return res;
}
int main() {
  return 0;
}
