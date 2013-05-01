#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
const int MAX = 10;
struct mat {
  mat() { clear(); }
  void clear() { memset(ma,0,sizeof(ma)); }
  void ONE() { clear(); for(int i(0);i!=MAX;++i) ma[i][i] = 1; }
  double& get(int i,int j) { return ma[i][j]; }
  mat operator+(mat b) {
    mat res;
    for(int i(0);i!=MAX;++i)
      for(int j(0);j!=MAX;++j)
        res.get(i,j) = get(i,j)+b.get(i,j);
    return res;
  }
  mat operator-(mat b) {
    mat res;
    for(int i(0);i!=MAX;++i)
      for(int j(0);j!=MAX;++j)
        res.get(i,j) = get(i,j)-b.get(i,j);
    return res;
  }
  mat operator*(mat b) {
    mat res;
    for(int i(0);i!=MAX;++i)
      for(int j(0);j!=MAX;++j)
        for(int k(0);k!=MAX;++k)
          res.get(i,j)+=get(i,k)*b.get(k,j);
    return res;
  }
  mat pow(int n) {
    mat tmp,res;
    tmp = *this; res.ONE();
    for(;n;tmp = tmp*tmp, n>>=1)
			if(n&1) res = res*tmp;
    return res;
  }
  double ma[MAX][MAX];
};
int main() {
  return 0;
}
