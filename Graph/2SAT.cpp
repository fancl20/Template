#include <iostream>
#include <cstdio>
#include <algorithm>
#include <stack>
#include <cstring>
const int MAXV = 1010;
const int MAXE = 1000010;
using namespace std;
class two_sat {
	public:
		two_sat() { clear(); }
		void clear() {
			cur = edge;
			memset(vertex,0,sizeof vertex);
		}
		void add_and(int a,int b,bool val) {
			if(val) set(a,1), set(b,1);
			else except(a,b,1,1);
		}
		void add_or(int a,int b,bool val) {
			if(!val) set(a,0), set(b,0);
			else except(a,b,0,0);
		}
		void add_xor(int a,int b,bool val) {
			equal(a,b,!val);
		}
		void set(int a,bool val) {
			a<<=1;
			add(a^val,a^val^1);
		}
		void except(int a,int b,bool val1,bool val2) {
			a<<=1, b<<=1;
			add(a^val1^1,b^val2);
			add(b^val2^1,a^val1);
		}
		void equal(int a,int b,int val) {
			a<<=1, b<<=1;
			add(a,b^val^1);
			add(b,a^val^1);
			add(a^1,b^val);
			add(b^1,a^val);
		}
		bool check(int n) {
			tarjan(n<<1);
			for(int i(0);i!=n;++i)
				if(col[i<<1]==col[i<<1^1])
					return false;
			return true;
		}
	private:
		int DFS(int u) {
			in_stack[u] = true;
			s.push(u);
			int low = DFN[u] = ++T;
			for(Edge *e = vertex[u];e;e = e->next) {
				if(!DFN[e->v])
					low = min(low,DFS(e->v));
				else if(in_stack[e->v])
					low = min(low,DFN[e->v]);
			}
			if(low==DFN[u])
				for(int v(-1);u!=v;s.pop()) {
					v = s.top();
					col[v] = low;
					in_stack[v] = false;
				}
			return low;
		}
		void tarjan(int n) {
			memset(in_stack,0,sizeof in_stack);
			memset(DFN,0,sizeof DFN);
			T = 0;
			for(int u(0);u!=n;++u)
				if(!DFN[u]) DFS(u);
		}
		void add(int u,int v) {
			cur->v = v;
			cur->next = vertex[u];
			vertex[u] = cur++;
		}
		struct Edge {
			int v;
			Edge *next;
		} edge[MAXE],*vertex[MAXV],*cur;
		int T,DFN[MAXV],col[MAXV];
		bool in_stack[MAXV];
		stack<int> s;
} G;
const int MAXN = 505;
int in[MAXN][MAXN];
//ZOJ 3656
int main() {
  int n,ans;
  while(cin>>n) {
    ans = 1;
    for(int i(0);i!=n;++i)
      for(int j(0);j!=n;++j)
        scanf("%d",&in[i][j]);
    for(int i(0);i!=n;++i)
      for(int j(0);j!=n;++j)
        if(in[i][j]!=in[j][i])
          ans = 0;
    for(int i(0);i!=n;++i)
      if(in[i][i]!=0)
        ans = 0;
    for(int k(0);ans && k!=31;++k) {
      G.clear();
      for(int i(0);ans && i!=n;++i)
        for(int j(i+1); ans && j!=n;++j) {
          if(i&1 && j&1) G.add_or(i,j,in[i][j]&(1<<k));
          else if(~i&1 && ~j&1) G.add_and(i,j,in[i][j]&(1<<k));
          else G.add_xor(i,j,in[i][j]&(1<<k));
        }
      ans&=G.check(n);
    }
    puts(ans?"YES":"NO");
  }
  return 0;
}
