#define PROBLEM "https://atcoder.jp/contests/abc174/tasks/abc174_f"
#include "my_template.hpp"
#include "other/io.hpp"
#include "ds/offline_query/uniqueproductquery.hpp"
#include "alg/monoid/add.hpp"

void solve() {
  LL(N, Q);
  VEC(int, C, N);
  UniqueProductQuery<Monoid_Add<int>> X(C);

  FOR(Q) {
    LL(l, r);
    X.add(--l, r);
  }
  for (auto&& x: X.calc()) print(x);
}

signed main() {
  solve();
  return 0;
}
