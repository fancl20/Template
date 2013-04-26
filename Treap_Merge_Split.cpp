#include <iostream>
#include <cstdio>
#include <ctime>
#include <algorithm>
#include <cstdlib>
using namespace std;
struct treap {
  treap *l,*r;
  const int h;
  int k,size;
  treap(int k):l(NULL),r(NULL),h(rand()),k(k),size(0) { upd(); }
  static int psize(treap *p) { return p?p->size:0; }
  void upd() {
    size = psize(l)+psize(r)+1;
  }
  ~treap() { delete l; delete r; }
};
struct t_pair {
  treap *l,*r;
  t_pair(treap* l = NULL,treap* r = NULL):l(l),r(r) {}
};
//l 所有节点必须小于 r 所有节点
treap* merge(treap* l,treap* r) {
  if(!l || !r) return l?l:r;
  if(l->h > r->h) {
    l->r = merge(l->r,r);
    l->upd();
    return l;
  } else {
    r->l = merge(l,r->l);
    r->upd();
    return r;
  }
}
//小于等于 k 在左子树，大于 k 在右子树
t_pair split(treap* p,int k) {
  if(!p) return t_pair(NULL,NULL);
  if(p->k>k) {
    t_pair t = split(p->l,k);
    p->l = t.r;
    p->upd();
    t.r = p;
    return t;
  } else {
    t_pair t = split(p->r,k);
    p->r = t.l;
    p->upd();
    t.l = p;
    return t;
  }
}
treap* rem(treap* p,int k) {
  if(!p) return NULL;
  else if(p->k>k)
    p->l = rem(p->l,k), p->upd();
  else if(p->k<k)
    p->r = rem(p->r,k), p->upd();
  else {
    treap* t = p;
    p = merge(p->l,p->r);
    t->l = t->r = NULL;
    delete t;
  }
  return p;
}
treap* ins(treap* p,int k) {
  t_pair t = split(p,k);
  t.l = merge(t.l,new treap(k));
  return merge(t.l,t.r);
}
void print(treap* p) {
  if(!p) return;
  if(p->l) print(p->l);
  cout<<p->k<<" : "<<p->size<<'\n';
  if(p->r) print(p->r);
}
treap* root = NULL;
int main() {
  srand(time(NULL));
  for(int i(0);i!=10;++i)
    root = ins(root,i);
  print(root);
  return 0;
}
