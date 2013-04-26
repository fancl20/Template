#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <vector>
using namespace std;
const double eps = 1e-8;
const double pi = acos(-1);
const double inf = 1e20;
inline int sign(double d) {
  if(fabs(d)<eps) return 0;
  return (d>0?1:-1);
}
inline double sqr(double x) {
  return x*x;
}
struct Point {
  double x,y;
  Point(double x = 0, double y = 0): x(x),y(y){}
  void input() { scanf("%lf%lf",&x,&y); }
  void output() { printf("%.2f %.2f\n",x,y); }
  bool operator<(const Point p) const { return sign(x-p.x)==0? sign(y-p.y)<0:x<p.x; }
  bool operator==(const Point p) const { return sign(x-p.x)==0 && sign(y-p.y)==0; }
  double dis(Point p = Point()) { return hypot(x-p.x,y-p.y); }
  double dis2(Point p = Point()) { return sqr(x-p.x)+sqr(y-p.y); }
  Point operator+(Point p) { return Point(x+p.x,y+p.y); }
  Point operator-(Point p) { return Point(x-p.x,y-p.y); }
  Point operator*(double m) { return Point(x*m,y*m); }
  Point operator/(double m) { return Point(x/m,y/m); }
  double operator*(Point p) { return x*p.x+y*p.y; }
  double operator^(Point p) { return x*p.y-y*p.x; }
  double rad(Point a, Point b) {
    Point p = *this;
    return fabs(atan2(fabs((a-p)^(b-p)),(a-p)*(b-p)));
  }
  Point trunc(double r) {
    double l = dis();
    if(!sign(l)) return *this;
    return Point(x*r/l,y*r/l);
  }
  Point rotleft() { return Point(-y,x); }
  Point rotright() { return Point(y,-x); }
  Point rotate(double angle, Point o = Point()) {
    Point p = *this-o;
    double c = cos(angle),s = sin(angle);
    return Point(o.x+p.x*c-p.y*s,o.y+p.x*s+p.y*c);
  }
};
struct p_cmp {
  //极角比较函数
  p_cmp(Point _o = Point()): o(_o){}
  bool operator()(const Point &_a,const Point &_b) const {
    Point a(_a),b(_b);
    int det = sign((a-o)^(b-o));
    return det>0 || (det==0 && a.dis(o)<b.dis(o));
  }
  Point o;
};
struct Line {
  //a 指向 b
  Point a,b;
  Line(Point a = Point(), Point b = Point()): a(a),b(b){}
  //倾角
  Line(Point p, double angle) {
    a = p;
    if(sign(angle-pi/2)==0) b = a+Point(0.0,1.0);
    else b = a+Point(1,tan(angle));
  }
  //ax+by+c=0
  Line(double _a, double _b, double _c) {
    if(sign(_a)==0)
      a = Point(0,-_c/_b), b = Point(1,-_c/_b);
    else if(sign(_b)==0)
      a = Point(-_c/_a,0), b = Point(-_c/_a,1);
    else
      a = Point(0,-_c/_b), b = Point(1,(-_c-_a)/_b);
  }
  void input() { a.input(); b.input(); }
  void adjust() { if(b<a) swap(a,b); }
  double length() { return a.dis(b); }
  double angle() { return atan2(b.y-a.y,b.x-a.x); }
  //1 逆时针 2 顺时针 3 直线上
  int relation(Point p) {
    int c = sign((p-a)^(b-a));
    if(c<0) return 1;
    if(c>0) return 2;
    return 3;
  }
  bool on_seg(Point p) { return sign((p-a)^(b-a))==0 && sign((p-a)*(p-b))<=0; }
  bool parallel(Line v) { return sign((b-a)^(v.b-v.a))==0; }
  //0 不相交 1 非规范 2 规范
  int seg_cross_seg(Line v) {
    int d1 = sign((b-a)^(v.a-a)), d2 = sign((b-a)^(v.b-a));
    int d3 = sign((v.b-v.a)^(a-v.a)), d4 = sign((v.b-v.a)^(b-v.a));
    if((d1^d2)==-2 && (d3^d4)==-2) return 2;
    return (d1==0 && on_seg(v.a) || d2==0 && on_seg(v.b) ||
	    d3==0 && v.on_seg(a) || d4==0 && v.on_seg(b) );
  }
  //*this seg v Line
  //0 不相交 1 非规范 2 规范
  int seg_cross_line(Line v) {
    int d1 = sign((b-a)^(v.a-a)), d2 = sign((b-a)^(v.b-a));
    if((d1^d2)==-2) return 2;
    return (d1==0 || d2==0);
  }
  //0 平行 1 重合 2 相交
  int line_cross_line(Line v) {
    if(parallel(v)) return v.relation(a)==3;
    return 2;
  }
  Point cross_point(Line v) {
    double a1 = (v.b-v.a)^(a-v.a), a2 = (v.b-v.a)^(b-v.a);
    return Point((a.x*a2-b.x*a1)/(a2-a1),(a.y*a2-b.y*a1)/(a2-a1));
  }
  double dis_point_to_line(Point p) { return fabs((p-a)^(b-a))/length(); }
  double dis_point_to_seg(Point p) {
    if(sign((p-b)*(a-b))<0 || sign((p-a)*(b-a))<0)
      return min(p.dis(a),p.dis(b));
    return dis_point_to_line(p);
  }
  //投影点
  Point line_prog(Point p) { return a+(b-a)*((b-a)*(p-a))/(b-a).dis2(); }
  Point symmetry_point(Point p) { return line_prog(p)*2-p; }
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
  
  /*
inline double rotating_calipers(Point *ch,int n) {
  double ret(0);
  for(int p(0),q(1);p!=n;++p) {
    while(fabs(det(ch[p+1],ch[q],ch[p]))<fabs(det(ch[p+1],ch[q+1],ch[p])))
      q = (q+1)%n;
    ret = max(ret,max(dis(ch[q],ch[p]),dis(ch[(q+1)%n],ch[p+1])));
  }
  return ret;
}
  */
int main() {
  return 0;
}
