#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <vector>
using namespace std;
const double eps = 1e-8;
const double inf = 1e20;
inline int sign(double d) {
  if(fabs(d)<eps) return 0;
  return (d>0?1:-1);
}
struct Point {
  double x,y;
  Point(double x = 0, double y = 0): x(x),y(y) {}
  bool operator<(const Point p) const { return sign(x-p.x)==0? sign(y-p.y)<0:x<p.x; }
  bool operator==(const Pint p) const { return sign(x-p.x)==0 && sign(y-p.y)==0; }
  double dis(Point p = Point()) { return hypot(x-p.x,y-p.y); }
  Point operator+(Point p) { return Point(x+p.x,y+p.y); }
  Point operator-(Point p) { return Point(x-p.x,y-p.y); }
  Point operator*(double m) { return Point(x*m,y*m); }
  Point operator/(double m) { return Point(x/m,y/m); }
  double operator^(Point p) { return x*p.y-y*p.x; }
};
struct Polygon {
  int n;
  vector<Point> p;
  void add(Point q) {
    p.push_back(q);
    n = p.size();
  }
  Polygon get_convex() {
    sort(p.begin(),p.end());
    Polygon cvx;
    cvx.p.resize(n*2);
    int &top = cvx.n;
    for(int i(0);i!=n;++i) {
      while(top>=2 && ((cvx.p[top]-p[i])^(cvx.p[top-1]-p[i]))<=0)
	--top;
      cvx.p[++top] = p[i];
    }
    for(int i(n-2),t(top+1);i>=0;--i) {
      while(top>=t && ((cvx.p[top]-p[i])^(cvx.p[top-1]-p[i]))<=0)
	--top;
      cvx.p[++top] = p[i];
    }
    cvx.p.resize(top>2?--top:top);
    return cvx;
  }
};
int main() {
  return 0;
}
