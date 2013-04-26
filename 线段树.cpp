#include <iostream>
#include <cstdio>
#include <algorithm>
#define lson l,m,rt->ls
#define rson m+1,r,rt->rs
using namespace std;
struct Node {
  int wl,wr,w,col,st,ed;
  Node *ls,*rs;
  Node():ls(0),rs(0),col(0){}
} *root;
Node* build(int l,int r,int len) {
  Node* ret = new Node;
  ret->wl = ret->wr = ret->w = len;
  ret->st = l, ret->ed = r;
  return ret;
}
void push_up(Node* rt,int len,int l,int r) {
  int ll = (len+1)/2, rl = len/2, m = l+r>>1;
  Node *ls = rt->ls, *rs = rt->rs;
  rt->wl = ls->wl;
  rt->wr = rs->wr;
  if(rt->wl==ll) rt->wl+=rs->wl;
  if(rt->wr==rl) rt->wr+=ls->wr;
  rt->w = ls->wr+rs->wl;
  rt->st = m-ls->wr+1;
  rt->ed = m+rs->wl;
  if(rt->w<=ls->w) {
    rt->w = ls->w;
    rt->st = ls->st;
    rt->ed = ls->ed;
  }
  if(rt->w<rs->w) {
    rt->w = rs->w;
    rt->st = rs->st;
    rt->ed = rs->ed;
  }
}
void push_down(Node* rt,int len,int l,int r) {
  int ll = (len+1)/2, rl = len/2, m = l+1>>1;
  if(!rt->ls) rt->ls = build(l,m,ll);
  if(!rt->rs) rt->rs = build(m+1,r,rl);
  Node *ls = rt->ls, *rs = rt->rs;
  if(!rt->col) return;
  if(rt->col==1) {
    ls->st = l, ls->ed = m;
    rs->st = m+1, rs->ed = r;
  }
  ls->wl = ls->wr = ls->w = rt->col==1?ll:0;
  rs->wl = rs->wr = rs->w = rt->col==1?rl:0;
  ls->col = rs->col = rt->col;
  rt->col = 0;
}
void update(int L,int R,int c,int l,int r,Node *rt) {
  int len = r-l+1;
  if(L<=l && r<=R) {
    rt->wl = rt->wr = rt->w = c==1?len:0;
    rt->col = c;
    return;
  }
  push_down(rt,len,l,r);
  int m = l+r>>1;
  if(L<=m) update(L,R,c,lson);
  if(R>m) update(L,R,c,rson);
  push_up(rt,len,l,r);
}
int main() {
  int m,l,r; cin>>m;
  char c[10];
  root = build(0,999999999,1000000000);
  for(int i(0);i!=m;++i) {
    scanf("%d%d%s",&l,&r,c);
    update(l,r-1,c[0]=='w'?1:2,0,999999999,root);
  }
  cout<<root->st<<' '<<root->ed+1<<'\n';
  return 0;
}
