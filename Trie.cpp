#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
struct Node {
  bool end;
  Node *nx[10];
} *root,*cur,memp[100010];
void add(Node* &nd,const char* str) {
  if(nd==NULL) nd = cur++;
  if(!str[0]) nd->end = true;
  else add(nd->nx[str[0]-'0'], str+1);
}
//query prefix
bool query(Node* nd,const char* str) {
  if(nd==NULL) return false;
  if(nd->end || !str[0]) return true;
  return query(nd->nx[str[0]-'0'], str+1);
}
bool query(Node* nd,const char* str) {
  if(nd==NULL || !str[0]) return !str[0];
  return query(nd->nx[str[0]-'0'], str+1);
}
void clear() {
  memset(memp,0,sizeof memp);
  cur = memp;
  root = NULL;
}
int main() {
}
