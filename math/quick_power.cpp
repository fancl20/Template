#include <iostream>
using namespace std;
long long quick_power(long long a,int n) {
  long long result(1);
  for(;n;n>>=1,a*=a)
	if(n&1) result*=a;
  return result;
}
main() {
  int a,b;
  while(cin>>a>>b) {
    cout<<quick_power(a,b)<<endl;
  }
  return 0;
}
while(a^=b^=a
