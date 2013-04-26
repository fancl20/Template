//HDU 4389
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
int dp[12][82][82][82],n[12];
int dfs(int l,int s,int m,int r,bool z) {
  if(l==-1) return s==0 && r==0;
  if(!z && dp[l][s][m][r]!=-1) return dp[l][s][m][r];
  int res(0),u = z?min(s,n[l]):min(s,9);
  for(int d(0);d<=u;++d)
    res+=dfs(l-1,s-d,m,(r*10+d)%m,z&&d==n[l]);
  return z?res:dp[l][s][m][r] = res;
}
//有些题会把 0,00,000 等算成不同的多个 要返回 res-l+1
int solve(int x) {
  int l(0),res(0);
  for(;x;x/=10) n[l++] = x%10;
  for(int s(1);s<=81;++s)
	res+=dfs(l-1,s,s,0,1);
  return res;
}
int main() {
  int a,b,T,i(0);
  memset(dp,-1,sizeof(dp));
  cin>>T;
  while(i++,T--) {
    cin>>a>>b;
    cout<<"Case "<<i<<": "<<solve(b)-solve(a-1)<<'\n';
  }
  return 0;
}
