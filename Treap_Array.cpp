#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#define MAX (1000)
using namespace std;
class treap {
  public:
    treap() { srand(time(NULL)); clear(); }
    void clear() { last_p=root=-1; }
    void rot(int &x,bool z) {
      int y = p[x].s[!z];
      p[x].s[!z] = p[y].s[z];
      p[y].s[z] = x, x = y;
    }
    bool insert(int key) { return insert(root,key); }
    bool insert(int &x,int key) {
      if(x==-1) { x = ++last_p; p[x].add(key); return true; }
      if(key==p[x].key) return false; //set
      bool z = key>p[x].key; insert(p[x].s[z],key);
      if(p[p[x].s[z]].fix>p[x].fix) rot(x,!z);
    }
    bool remove(int key) { return remove(root,key); }
    bool remove(int &x,int key) {
      if(x==-1) return false;
      bool z = p[p[x].s[0]].fix>p[p[x].s[1]].fix;
      if(key==p[x].key) {
        if(p[x].s[0]==-1 && p[x].s[1]==-1) x = -1;
        else if(p[x].s[0]==-1) x = p[x].s[1];
        else if(p[x].s[1]==-1) x = p[x].s[0];
        else rot(x,z), remove(p[x].s[z],key);
        return true;
      } else return remove(p[x].s[key>p[x].key],key);
    }
    bool find(int key) { return find(root,key); }
    bool find(int x,int key) {
      if(x==-1) return false;
      if(key==p[x].key) return true;
      return find(p[x].s[key>p[x].key],key);
    }
    void print() { print(root); }
    void print(int x) {
      if(p[x].s[0]!=-1) print(p[x].s[0]);
      cout<<p[x].key<<" : "<<p[x].fix<<endl;
      if(p[x].s[1]!=-1) print(p[x].s[1]);
    }
  private:
    struct _node {
      int s[2],key,fix;
      void add(int _key) { s[0]=s[1]=-1; key=_key; fix=rand();}
    } p[MAX];
    int root,last_p;
} QAQ;
int main() {
  return 0;
}
