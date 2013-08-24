#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#define INF (0x7f7f7f7f)
using namespace std;
int num[40010],D[40010];
int LIS(int n) {
  memset(D,0x7f,sizeof(D));
  for(int i(0);i!=n;++i)
    *lower_bound(D,D+i,num[i]) = num[i]; //最长不降子序列用 upper_bound
  for(int i(0);;++i) if(D[i]==INF) return i;
}
int main() {
  int n,_; cin>>_;
  while(_--) {
    cin>>n;
    for(int i(0);i!=n;++i)
      scanf("%d",&num[i]);
    cout<<LIS(n)<<'\n';
  }
  return 0;
}
