#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
const int MOD = 1000000007;
long long d[2][1010],cur[1010],ans[1010],x[1010],val[1010],re[1010];
long long rev(long long a) {
	long long res(1),tmp(a);
	for(int i(MOD-2);i;i>>=1) {
		if(i&1) res = (res*tmp)%MOD;
		tmp = (tmp*tmp)%MOD;
	}
	return res;
}
void init() {
	memset(d,0,sizeof d);
	memset(cur,0,sizeof cur);
	memset(ans,0,sizeof ans);
	cur[0] = 1;
}
void inter(int n) {
	long long *p = d[0], *q = d[1];
	init();
	for(int i(0);i!=n;++i) {
		swap(p,q);
		q[0] = val[i];
		for(int j(0);j!=i;++j)
			q[j+1] = (q[j]-p[j]+MOD)*re[j+1]%MOD;
		for(int j(i);j>0;--j)
			cur[j] = (cur[j-1]-x[i-1]*cur[j])%MOD;
		if(i) cur[0] = -cur[0]*x[i-1]%MOD;
		for(int j(0);j!=i+1;++j) {
			ans[j] = (ans[j]+cur[j]*q[i])%MOD;
			if(ans[j]<0) ans[j]+=MOD;
		}
	}
}
long long get(long long a,int n) {
	long long res(0);
	for(int i(n-1);i>=0;--i)
		res = (res*a+ans[i])%MOD;
	return res;
}
int main() {
	int _,n,x0,d; cin>>_;
	while(_--) {
		scanf("%d%d%d",&n,&x0,&d);
		++n;
		for(int i(0);i<=n;++i) {
			x[i] = x0+i*d;
			re[i] = rev(i*d);
		}
		for(int i(0);i!=n;++i)
			scanf("%lld",&val[i]);
		inter(n);
		for(int i(0);i!=n;++i)
			printf("%lld ",ans[i]);
		puts("");
	}
	return 0;
}
