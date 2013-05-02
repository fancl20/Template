#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
double d[2][110],cur[110],ans[110],x[110],val[110];
void init() {
	memset(d,0,sizeof d);
	memset(cur,0,sizeof cur);
	memset(ans,0,sizeof ans);
	cur[0] = 1;
}
void inter(int n) {
	double *p = d[0], *q = d[1];
	init();
	for(int i(0);i!=n;++i) {
		swap(p,q);
		q[0] = val[i];
		for(int j(0);j!=i;++j)
			q[j+1] = (p[j]-q[j])/(x[i-j-1]-x[i]);
		for(int j(i);j>0;--j)
			cur[j] = cur[j-1]-x[i-1]*cur[j];
		if(i) cur[0]*=-x[i-1];
		for(int j(0);j!=i+1;++j)
			ans[j]+=cur[j]*q[i];
	}
}
double get(double a,int n) {
	double res(0);
	for(int i(n-1);i>=0;--i)
		res = res*a+ans[i];
	return res;
}
int main() {
	int _,s,c; cin>>_;
	for(int i(0);i!=110;++i)
		x[i] = i;
	while(_--) {
		scanf("%d%d",&s,&c);
		for(int i(0);i!=s;++i)
			scanf("%lf",&val[i]);
		inter(s);
		for(int i(0);i!=c;++i)
			printf("%.0f ",get(s+i,s));
		puts("");
	}
	return 0;
}
