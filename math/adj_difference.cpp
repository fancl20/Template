#include <iostream>
#include <cstdio>
#include <numeric>
using namespace std;
int a[110];
int main() {
	int _,s,c; cin>>_;
	while(_--) {
		scanf("%d%d",&s,&c);
		for(int i(0);i!=s;++i)
			scanf("%d",&a[i]);
		for(int i(0);i!=s-1;++i)
			adjacent_difference(a+i,a+s,a+i);
		for(int i(0);i!=c;++i)
			a[s+i] = a[s-1];
		for(int i(0);i!=s-1;++i)
			partial_sum(a+s-2-i,a+s+c,a+s-2-i);
		for(int i(0);i!=c;++i)
			cout<<a[s+i]<<' ';
		cout<<'\n';
	}
	return 0;
}
