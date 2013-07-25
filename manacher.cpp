#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
const int MAXN = 110010;
char s[MAXN*2],in[MAXN];
int dp[MAXN*2];
void manacher(char str[],int n) {
	for(int i(1),r(0),id;i!=n;++i) {
		if(i<r) dp[i] = min(dp[id*2-i],r-i);
		else dp[i] = 1;
		for(int &d = dp[i];i-d>=0;++d)
			if(str[i+d]!=str[i-d]) break;
		if(dp[i]+i>r) id = i, r = dp[i]+i;
	}
}
int init(char str1[],int n,char str2[]) {
	int ptr(1);
	str2[0] = '$';
	for(int i(0);i!=n;++i) {
		str2[ptr++] = str1[i];
		str2[ptr++] = '$';
	}
	str2[ptr] = '\0';
	return ptr;
}
//hdu 3068
int main() {
	while(~scanf("%s",in)) {
		int l = init(in,strlen(in),s);
		manacher(s,l);
		cout<<*max_element(dp,dp+l)-1<<'\n';
	}
	return 0;
}
