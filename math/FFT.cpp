#include <iostream>
#include <cstdio>
#include <algorithm>
#include <complex>
#include <cmath>
#include <cstring>
using namespace std;
typedef complex<long double> cmplx;
const double pi = acos(-1.0);
int get(int n) {
	int ret(1);
	while(ret<n) ret<<=1;
	return ret;
}
void FFT(cmplx y[],int n,double z) {
	for(int i(1),j(0);i<n;++i) {
		for(int k=n>>1;k>(j^=k);k>>=1);
		if(i<j) swap(y[i],y[j]);
	}
	for(int h(2);h<=n;h<<=1) {
		cmplx wn = exp(cmplx(0,z*2*pi/h));
		for(int j(0);j<n;j+=h) {
			cmplx w(1,0);
			for(int k(j);k<j+h/2;++k) {
				cmplx u = y[k], t = w*y[k+h/2];
				y[k] = u+t;
				y[k+h/2] = u-t;
				w*=wn;
			}
		}
	}
	if(z<0) for(int i(0);i<n;++i) y[i]/=n;
}
cmplx x[1<<17],y[1<<17];
int main() {
	int n,k,tmp,nn;
	while(~scanf("%d",&n)) {
		memset(x,0,sizeof x);
		memset(y,0,sizeof y);
		nn = get(5000*(n-1));
		for(int i(0);i!=n-1;++i) {
			scanf("%d",&k);
			memset(x,0,sizeof x);
			for(int j(0);j!=k;++j) {
				scanf("%d",&tmp);
				x[tmp]+=1;
			}
			FFT(x,nn,1);
			for(int j(0);j!=nn;++j) {
				if(i) y[j]*=x[j];
				else y[j] = x[j];
			}
		}
		FFT(y,nn,-1);
		cout.setf(ios::fixed);
		cout.precision(0);
		for(int i(0);i!=nn;++i) if(y[i].real()>0.9)
			cout<<i<<' '<<y[i].real()<<'\n';
				//printf("%d %.0Lf\n",i,y[i].real());
	}
	return 0;
}
