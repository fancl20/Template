#include <iostream>
#include <cstdio>
#include <algorithm>
#include <functional>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
//old version
//using namespace pb_ds;
//typedef tree<int,null_mapped_type,less<int>, rb_tree_tag> set_t;
typedef tree<int,null_type,less<int>, rb_tree_tag,
        tree_order_statistics_node_update> set_t;
set_t ss,r;
int main() {
  ss.insert(1);
  ss.insert(2);
  ss.insert(10);
  cout<<*ss.find_by_order(1)<<endl;
  cout<<ss.order_of_key(5)<<endl;
  ss.split(1,r);
  cout<<ss.size()<<' '<<r.size()<<endl;
  //every element in ss must less than r
  ss.join(r);
  cout<<ss.size()<<' '<<r.size()<<endl;
  return 0;
}
