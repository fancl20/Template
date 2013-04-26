#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
int exgcd(int a,int b,int &x,int &y) {
	if(!b) return x = 1, y = 0, a;
	int g = exgcd(b,a%b,y,x);
	y-=a/b*x;
	return g;
}
int main() {
	int a,b,x,y;
	while(cin>>a>>b) {
		cout<<exgcd(a,b,x,y)<<' ';
		cout<<x<<' '<<y<<endl;
	}
	return 0;
}
