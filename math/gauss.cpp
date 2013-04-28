#include <valarray>
#include <iostream>
#include <cmath>
using namespace std;
const int MAX = 10;
const double eps = 1e-8;
int sign(double x) {
	if(abs(x)<eps) return 0;
	return x<0?-1:1;
}
valarray<double> a[MAX];
void init() {
	for(int i(0);i!=n;++i)
		a[i].resize(MAX);
}
bool cal(int n) {
	for(int i(0);i!=n;++i) {
		for(int j(i);j!=n;++j)
			if(abs(a[j][i])>abs(a[i][i]))
				swap(a[i],a[j]);
		if(sign(a[i][i])==0) return false;
		a[i]/=(double)a[i][i];
		for(int j(i+1);j!=n;++j)
			if(a[j][i]!=0)
				a[j]-=a[j][i]*a[i];
	}
	return true;
}
int main() {
	return 0;
}
