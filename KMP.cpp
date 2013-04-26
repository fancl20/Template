#include <iostream>
#include <cstdio>
#include <cctype>
#define MAX_LEN 10010
using namespace std;
int KMP(char a[],char b[]) {
  int ret(0),next[MAX_LEN] = {-1};
  for(int i(1),j(-1);b[i];++i) {
    while(j!=-1 && b[i]!=b[j+1]) j = next[j];
    if(b[i]==b[j+1]) ++j;
    next[i] = j;
  }
  for(int i(0),j(-1);a[i];++i) {
    while(j!=-1 && a[i]!=b[j+1]) j = next[j];
    if(a[i]==b[j+1]) ++j;
    if(!b[j+1]) ++ret, j = next[j];
  }
  return ret;
}
int main() {
  char W[MAX_LEN],T[1000010];
  int C,tmp;
  cin>>C;
  while(C--) {
    scanf("%s%s",W,T);
    printf("%d\n",KMP(T,W));
  }
  return 0;
}
