#include <iostream>
#include <cstdio>
#define ENUM(x,s) for(int x(s);x;x=s&(x-1)) //enum subset x in s
#define popcount(x) __builtin_popcount(x)
#define parity(x) __builtin_parity(x) //popcount mod 2
#define ffs(x) __builtin_ffs(x) //index of the least significant 1-bis PLUS 1!
#define clz(x) __builtin_clz(x) //counting leading  0-bits.
#define ctz(x) __builtin_ctz(x) //counting trailing 0-bits.
#define MOD 1000000009
using namespace std;
inline int mul_mod(int a,int b){
  int ret;
  __asm__ __volatile__ ("\tmull %%ebx\n\tdivl %%ecx\n"
          :"=d"(ret):"a"(a),"b"(b),"c"(MOD));
  return ret;
}
inline int next(int x) {
  int s = -x&x, t = x+s;
  return t|(x^t)/s>>2;
}
inline int _next(int x) {
  unsigned int t=x|x-1;
  return t+1|(~t&-~t)-1>>ctz(x)+1;
}
//STACK OVERFLOW
#define N_MAX (100000)
int dfs(int d) { return 0; }
int call_dfs(int d) {
  static int stack[N_MAX*5],bak;
  asm __volatile__
    (
     "movl %%esp, %0\n\t"
     "movl %1, %%esp\n\t":
     "=g"(bak):
     "g"(stack + N_MAX * 5 - 1):
    );
  int ret = dfs(d); 
  asm __volatile__
    (
     "movl %0, %%esp\n\t":
     :
     "g"(bak)
    );
  return ret;
}
int main() {
  return 0;
}
