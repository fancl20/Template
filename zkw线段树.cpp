#include <iostream>
#include <cstdio>
#include <algorithm>
#define MAX (1<<18)
#define M (1<<17)
using namespace std;
struct Node {
  int l[2],r[2],m[2],sum[2];
  int op;
} Tree[MAX];
void push_up(int s) {
  for(int i(0);i!=2;++i) {
    Tree[s].sum[i] = Tree[s<<1].sum[i]+Tree[s<<1^1].sum[i];
    if(Tree[s<<1].sum[i^1]==0) Tree[s].l[i] = Tree[s<<1].l[i]+Tree[s<<1^1].l[i];
    else Tree[s].l[i] = Tree[s<<1].l[i];
    if(Tree[s<<1^1].sum[i^1]==0) Tree[s].r[i] = Tree[s<<1^1].r[i]+Tree[s<<1].r[i];
    else Tree[s].r[i] = Tree[s<<1^1].r[i];
    Tree[s].m[i] = max(max(Tree[s<<1].m[i],Tree[s<<1^1].m[i]),Tree[s<<1].r[i]+Tree[s<<1^1].l[i]);
  }
}
void add(int s,bool val) {
  s+=M;
  Tree[s].l[0] = Tree[s].r[0] = Tree[s].sum[0] = val^1;
  Tree[s].l[1] = Tree[s].r[1] = Tree[s].sum[1] = val;
  for(s>>=1;s;s>>=1)
    push_up(s);
}
void _change(int s,bool val) {
  int good = Tree[s].sum[0]+Tree[s].sum[1],bad(0);
  if(val) swap(good,bad);
  Tree[s].l[0] = Tree[s].r[0] = Tree[s].m[0] = Tree[s].sum[0] = good;
  Tree[s].l[1] = Tree[s].r[1] = Tree[s].m[1] = Tree[s].sum[1] = bad;
}
void _rev(int s) { //3^3==0 1^3==2 2^3==1 0^3==3
  Tree[s].op^=3;
  if(Tree[s].op==1 || Tree[s].op==2) {
    _change(s,Tree[s].op-1);
    return;
  }
  swap(Tree[s].sum[0],Tree[s].sum[1]);
  swap(Tree[s].l[0],Tree[s].l[1]);
  swap(Tree[s].r[0],Tree[s].r[1]);
  swap(Tree[s].m[0],Tree[s].m[1]);
}
void push_down(int s) {
  int op = Tree[s].op;
  Tree[s].op = 0;
  if(s>=M) return;
  if(op==1 || op==2)
    Tree[s<<1].op = Tree[s<<1^1].op = op, _change(s<<1,op-1), _change(s<<1^1,op-1);
  if(op==3)
    _rev(s<<1), _rev(s<<1^1);
}
void force(int s,int t) {
  s = s+M-1; t = t+M+1;
  for(int i = M;i;i>>=1)
    push_down(s/i), push_down(t/i);
}
void change(int s,int t,bool val) {
  force(s,t);
  for(s = s+M-1,t = t+M+1;s^t^1;s>>=1,t>>=1) {
    if(~s&1) Tree[s^1].op = val+1, _change(s^1,val);
    if( t&1) Tree[t^1].op = val+1, _change(t^1,val);
    push_up(s>>1); push_up(t>>1);
  }
  while(s) push_up(s>>=1);
}
void rev(int s,int t) {
  force(s,t);
  for(s = s+M-1,t = t+M+1;s^t^1;s>>=1,t>>=1) {
    if(~s&1) _rev(s^1);
    if( t&1) _rev(t^1);
    push_up(s>>1); push_up(t>>1);
  }
  while(s) push_up(s>>=1);
}
int query_sum(int s,int t) {
  force(s,t);
  int ret(0);
  for(s = s+M-1,t = t+M+1;s^t^1;s>>=1,t>>=1) {
    if(~s&1) ret+=Tree[s^1].sum[1];
    if( t&1) ret+=Tree[t^1].sum[1];
  }
  return ret;
}
int query_len(int s,int t) {
  force(s,t);
  int llen(0),rlen(0),mmax(0);
  for(s = s+M-1,t = t+M+1;s^t^1;s>>=1,t>>=1) {
    if(~s&1) {
      mmax = max(mmax,max(Tree[s^1].m[1],llen+Tree[s^1].l[1]));
      if(Tree[s^1].sum[0]==0) llen+=Tree[s^1].l[1];
      else llen = Tree[s^1].r[1];
    }
    if( t&1) {
      mmax = max(mmax,max(Tree[t^1].m[1],rlen+Tree[t^1].r[1]));
      if(Tree[t^1].sum[0]==0) rlen+=Tree[t^1].r[1];
      else rlen = Tree[t^1].l[1];
    }
  }
  mmax = max(mmax,llen+rlen);
  return mmax;
}
int main() {
  int t;
  for(cin>>t;t;--t) {
    for(int i(0);i!=MAX;++i)
      for(int j(0);j!=2;++j)
        Tree[i].l[j] = Tree[i].r[j] = Tree[i].m[j] = Tree[i].sum[j] =  Tree[i].op = 0;
    int n,q;
    cin>>n>>q;
    for(int i(0),tmp;i!=n;++i) {
      scanf("%d",&tmp);
      add(i+1,tmp);
    }
    for(int i(0),op,s,t;i!=q;++i) {
      scanf("%d%d%d",&op,&s,&t);
      if(op==0 || op==1) change(s+1,t+1,op);
      if(op==2) rev(s+1,t+1);
      if(op==3) cout<<query_sum(s+1,t+1)<<'\n';
      if(op==4) cout<<query_len(s+1,t+1)<<'\n';
    }
  }
  return 0;
}