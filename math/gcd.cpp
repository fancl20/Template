#include <iostream>
using namespace std;
int gcd(int a,int b) {
	while(a^=b^=a^=b%=a?a:a=b);
	return b;
}
int main() {
  for(int a,b;cin>>a>>b;cout<<gcd(a,b)<<endl)
  return 0;
}
