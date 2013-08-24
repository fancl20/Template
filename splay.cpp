#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
struct Node {
	Node(int key,Node *f = NULL):
		size(1),key(key),sum(key),lazy(0),f(f),lc(c[0]),rc(c[1]) {
			lc = rc = NULL;
		}
	static int sz(Node *x) {
		return x?x->size:0;
	}
	static long long sm(Node *x) {
		return x?x->sum:0;
	}
	void update(long long c) {
		lazy+=c;
		key+=c;
		sum+=size*c;
	}
	void push_up() {
		size = sz(lc)+sz(rc)+1;
		sum = sm(lc)+sm(rc)+key;
	}
	void push_down() {
		if(lc) lc->update(lazy);
		if(rc) rc->update(lazy);
		lazy = 0;
	}
	int size;
	long long key,sum,lazy;
	Node *c[2],*f,*&lc,*&rc;
	~Node() { delete lc; delete rc; };
} *root;
void zig(Node *y,bool w) {
	Node *x = y->f;
	if(x) x->push_down();
	if(y) y->push_down();
	if(x->f) {
		if(x==x->f->lc)
			x->f->lc = y;
		else x->f->rc = y;
	}
	y->f = x->f;
	x->c[w] = y->c[!w];
	if(x->c[w]) x->c[w]->f = x;
	y->c[!w] = x;
	x->f = y;
	x->push_up();
}
void splay(Node *x,Node *rt = NULL) {
	while(x->f!=rt) {
		Node *y = x->f;
		bool w = x==y->rc;
		if(y->f!=rt && w==(y==y->f->rc))
			zig(y,w);
		zig(x,w);
	}
	x->push_up();
}
Node *nth(Node *x,int pos) {
	while(true) {
		int l = Node::sz(x->lc);
		if(l+1==pos) return x;
		if(l>=pos) x = x->lc;
		else pos-=l+1, x = x->rc;
	}
}
void change(Node *&x,int s,int t,int c) {
	Node *l = nth(x,s-1), *r = nth(x,t+1);
	splay(l);
	splay(r,l);
	Node *m = r->lc;
	m->update(c);
	splay(m);
	x = m;
}
long long query(Node *&x,int s,int t) {
	Node *l = nth(x,s-1), *r = nth(x,t+1);
	splay(l);
	splay(r,l);
	x = l;
	return r->lc->sum;
}
int a[100010];
Node *build(int s,int t,Node *f) {
	if(s>t) return NULL;
	int m = (s+t)/2;
	Node *ret = new Node(a[m],f);
	ret->lc = build(s,m-1,ret);
	ret->rc = build(m+1,t,ret);
	ret->push_up();
	return ret;
}
int main() {
	int n,m,s,t,c;
	char op[10];
	while(cin>>n>>m) {
		for(int i(0);i!=n;++i)
			scanf("%d",&a[i+1]);
		delete root;
		root = build(0,n+1,NULL);
		for(int i(0);i!=m;++i) {
			scanf("%s",op);
			if(op[0]=='Q') {
				scanf("%d%d",&s,&t);
				cout<<query(root,s+1,t+1)<<'\n';
			} else {
				scanf("%d%d%d",&s,&t,&c);
				change(root,s+1,t+1,c);
			}
		}
	}
	return 0;
}
