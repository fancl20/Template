#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#define pi (acos(-1.0))
#define eps (1e-6)
using namespace std;
struct point {
  point(double x = 0,double y = 0,double z = 0): x(x),y(y),z(z) {}
  void output() { printf("%.2f %.2f %.2f\n",x+eps,y+eps,z+eps); }
  double x,y,z;
};
struct trans {
  struct mat {
    mat() { clear(); }
    void output() {
      for(int i(0);i!=4;++i,cout<<endl)
        for(int j(0);j!=4;++j)
          printf("%.2f\t",ma[i][j]);
    }
    void clear() { memset(ma,0,sizeof(ma)); }
    void reg() { clear(); for(int i(0);i!=4;++i) ma[i][i] = 1; }
    double& g(int i,int j) { return ma[i][j]; }
    mat operator*(mat b) {
      mat res;
      for(int i(0);i!=4;++i)
        for(int j(0);j!=4;++j)
          for(int k(0);k!=4;++k)
            res.g(i,j)+=g(i,k)*b.g(k,j);
      return res;
    }
    mat pow(int n) {
      mat res; res.reg();
      for(mat t = *this;n;t = t*t, n>>=1)
        if(n&1) res = res*t;
      return res;
    }
    double ma[4][4];
  } op;
  trans() { op.reg(); }
  void move(double a,double b,double c) {
    mat t;
    t.g(0,0) = 1; t.g(0,3) = a;
    t.g(1,1) = 1; t.g(1,3) = b;
    t.g(2,2) = 1; t.g(2,3) = c;
    t.g(3,3) = 1;
    op = t*op;
  }
  void scale(double a,double b,double c) {
    mat t;
    t.g(0,0) = a;
    t.g(1,1) = b;
    t.g(2,2) = c;
    t.g(3,3) = 1;
    op = t*op;
  }
  //绕轴 (0,0,0)-(a,b,c) 逆时针旋转 d 度
  void rot(double a,double b,double c,double d) {
    mat t;
    double r = d/180*pi;
    double cr = cos(r), sr = sin(r);
    double l = sqrt(a*a+b*b+c*c);
    a/=l, b/=l, c/=l;
    t.g(0,0) = (1.0-cr)*a*a+cr;
    t.g(0,1) = (1.0-cr)*a*b-sr*c;
    t.g(0,2) = (1.0-cr)*a*c+sr*b;
    t.g(1,0) = (1.0-cr)*b*a+sr*c;
    t.g(1,1) = (1.0-cr)*b*b+cr;
    t.g(1,2) = (1.0-cr)*b*c-sr*a;
    t.g(2,0) = (1.0-cr)*c*a-sr*b;
    t.g(2,1) = (1.0-cr)*c*b+sr*a;
    t.g(2,2) = (1.0-cr)*c*c+cr;
    t.g(3,3) = 1;
    op = t*op;
  }
  trans rep(int n) {
    op = op.pow(n);
    return *this;
  }
  trans operator*(trans b) {
    trans res;
    res.op = op*b.op;
    return res;
  }
  point apply(point p) {
    mat t;
    t.g(0,0) = p.x;
    t.g(1,0) = p.y;
    t.g(2,0) = p.z;
    t.g(3,0) = 1.0;
    t = op*t;
    return point(t.g(0,0),t.g(1,0),t.g(2,0));
  }
};
trans run() {
  trans tr;
  int n;
  char op[20];
  double a,b,c,d;
  while(scanf("%s",op) && op[0]!='e') {
    if(op[0]=='t') {
      scanf("%lf%lf%lf",&a,&b,&c);
      tr.move(a,b,c);
    } else if(op[0]=='s') {
      scanf("%lf%lf%lf",&a,&b,&c);
      tr.scale(a,b,c);
    } else if(op[0]=='r' && op[1]=='o') {
      scanf("%lf%lf%lf%lf",&a,&b,&c,&d);
      tr.rot(a,b,c,d);
    } else if(op[0]=='r') {
      scanf("%d",&n);
      tr = run().rep(n)*tr;
    }
  }
  return tr;
}
//UVALIVE 5719
int main() {
  int N;
  double x,y,z;
  while(cin>>N && N) {
    trans tr = run();
    for(int i(0);i!=N;++i) {
      scanf("%lf%lf%lf",&x,&y,&z);
      tr.apply(point(x,y,z)).output();
    }
    cout<<endl;
  }
  return 0;
}
