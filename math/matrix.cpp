#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
template <int M>
struct mat {
  mat() { clear(); }
  void clear() { memset(ma,0,sizeof(ma)); }
  void reg() { clear(); for(int i(0);i!=M;++i) ma[i][i] = 1; }
  double& get(int i,int j) { return ma[i][j]; }
  void input() {
    for(int i(0);i!=M;++i)
      for(int j(0);j!=M;++j)
        scanf("%lf",&ma[i][j]);
  }
  void output() {
    for(int i(0);i!=M;++i,cout<<'\n')
      for(int j(0);j!=M;++j)
        printf("%.2f\t",ma[i][j]);
  }
  mat<M> operator+(mat<M> b) {
    mat<M> res;
    for(int i(0);i!=M;++i)
      for(int j(0);j!=M;++j)
        res.get(i,j) = get(i,j)+b.get(i,j);
    return res;
  }
  mat<M> operator-(mat<M> b) {
    mat<M> res;
    for(int i(0);i!=M;++i)
      for(int j(0);j!=M;++j)
        res.get(i,j) = get(i,j)-b.get(i,j);
    return res;
  }
  mat<M> operator*(mat<M> b) {
    mat<M> res;
    for(int i(0);i!=M;++i)
      for(int j(0);j!=M;++j)
        for(int k(0);k!=M;++k)
          res.get(i,j)+=get(i,k)*b.get(k,j);
    return res;
  }
  mat<M> pow(int n) {
    mat<M> tmp,res;
    tmp = *this; res.reg();
    for(;n;tmp = tmp*tmp, n>>=1) if(n&1)
      res = res*tmp;
    return res;
  }
  double ma[M][M];
};
int main() {
  mat<2> ma;
  ma.input();
  ma.pow(2).output();
  return 0;
}
