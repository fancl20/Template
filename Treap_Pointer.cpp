#include <iostream>
#include <cstdio>
#include <algorithm>
#include <ctime>
#include <cstdlib>
using namespace std;
class treap {
  private:
    struct node {
      int key,fix; node *c[2];
      node(int k):key(k),fix(rand()){}
    } *root;
  public:
    treap():root(NULL) { srand(time(NULL)); }
    void clear() { clear(root); }
    void clear(node* p) {
      if(p->c[0]) clear(p->c[0]);
      if(p->c[1]) clear(p->c[1]);
      delete p;
    }
    void rot(node* &x,bool z) {
      node* y=x->c[!z];
      x->c[!z]=y->c[z];
      y->c[z]=x; x=y;
    }
    void insert(int k) { insert(root,k); }
    void insert(node* &p,int k) {
      if(!p) { p = new node(k); return; }
      if(p->key==k) return; //set
      bool z = k>p->key; insert(p->c[z],k);
      if(p->c[z]->fix>p->fix) rot(p,!z);
    }
    bool remove(int k) { return remove(root,k); }
    bool remove(node* &p,int k) {
      if(!p) return false; node *t = p;
      if(p->key!=k) return remove(p->c[k>p->key],k);
      if(!p->c[0] || !p->c[1]) {
        p = p->c[!p->c[0]];
        delete t; return true;
      } else {
        bool z = p->c[0]->fix>p->c[1]->fix;
        return rot(p,z), remove(p->c[z],k);
      }
    }
    bool find(int k) { return find(root,k); }
    bool find(node* p,int k) {
      if(!p) return false;
      return p->key==k || find(p->c[k>p->key],k);
    }
    bool print() { if(root) print(root); }
    bool print(node* p) {
      if(p->c[0]) print(p->c[0]);
      cout<<(p->key)<<" : "<<(p->fix)<<'\n';
      if(p->c[1]) print(p->c[1]);
    }
};
int main() {
  return 0;
}
