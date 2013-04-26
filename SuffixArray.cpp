#include <iostream>
#include <cstring>
#include <iterator>
#include <cstdio>
#include <algorithm>
#include <numeric>
#define M_val (256)
#define MAXN (2010)
#define CMP(r,a,b,l) (r[a]==r[b] && r[a+l]==r[b+l])
using namespace std;
void da(char ori[],int sa[],int n) {
  int cnt[M_val],tmp[2][MAXN],*x(tmp[0]),*y(tmp[1]),sorted[MAXN];
  ori[++n] = 0; fill_n(cnt,M_val,0);
  for(int i(0);i!=n;++i) ++cnt[x[i]=ori[i]];
  partial_sum(cnt,cnt+M_val,cnt);
  for(int i(n-1);i>=0;--i) sa[--cnt[ori[i]]] = i;
  for(int len(1),p(1),i(0),m(M_val);p!=n;len<<=1,m = p) {
    for(p = 0,i = n-len;i!=n;++i) y[p++] = i;
    for(i = 0;i!=n;++i) if(sa[i]>=len) y[p++]=sa[i]-len;
    for(i = 0;i!=n;++i) sorted[i] = x[y[i]];
    fill_n(cnt,m,0);
    for(i = 0;i!=n;++i) ++cnt[sorted[i]];
    partial_sum(cnt,cnt+m,cnt);
    for(i = n-1;i>=0;--i) sa[--cnt[sorted[i]]] = y[i];
    swap(x,y);
    for(p = 1,i = 1,x[sa[0]] = 0;i!=n;++i)
      x[sa[i]] = CMP(y,sa[i-1],sa[i],len)?p-1:p++;
  }
}
void get_rank(int sa[],int rank[],int n) {
  for(int i(1);i!=n+1;++i)
    rank[sa[i]] = i;
}
void get_height(char ori[],int sa[],int rank[],int height[],int n) {
  for(int i(0),j(0),k(0);i!=n;height[rank[i++]] = k)
    for(k?k--:0,j=sa[rank[i]-1];ori[i+k]==ori[j+k];++k);
  return;
}
int main() {
  char a[MAXN]; //ori
  int sa[MAXN],rank[MAXN],height[MAXN]; //sa from 1 to n;  height from 2 to n; rank from 0 to n-1;
  cin>>a;
  da(a,sa,strlen(a));
  get_rank(sa,rank,strlen(a));
  get_height(a,sa,rank,height,strlen(a));
  for(int i(1);i!=strlen(a)+1;++i)
    cout<<a+sa[i]<<endl;
  for(int i(2);i!=strlen(a)+1;++i) //the height between sa[i-1] && sa[i];
    cout<<height[i]<<endl;
  return 0;
}
