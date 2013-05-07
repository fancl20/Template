#include <iostream>
#include <cstdio>
#include <algorithm>
#include <functional>
#include <vector>
#include <ext/pb_ds/priority_queue.hpp>
#define mp(x,y) make_pair(x,y)
using namespace std;
typedef pair<int,int> pii;
typedef __gnu_pbds::priority_queue<pii> pq;
vector<pq::point_iterator> a_it;
pq q1,q2;
int main() {
  a_it.push_back(q1.push(mp(1,1)));
  a_it.push_back(q1.push(mp(3,2)));
  a_it.push_back(q2.push(mp(2,3)));
  a_it.push_back(q2.push(mp(4,4)));
  cout<<q1.size()<<' '<<q2.size()<<endl;
  q1.join(q2);
  cout<<q1.size()<<' '<<q2.size()<<endl;
  cout<<q1.top().first<<' '<<q1.top().second<<endl;
  q1.modify(a_it[q1.top().second-1],mp(0,4));
  cout<<q1.top().first<<' '<<q1.top().second<<endl;
  return  0;
}
