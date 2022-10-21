#define PROBLEM \
  "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_H"

#include "my_template.hpp"
#include "other/io.hpp"
#include "alg/lazy/min_add.hpp"
#include "ds/lazysegtree.hpp"

void solve() {
  using Lazy = Lazy_Min_Add<ll>;
  LL(N, Q);
  vi A(N);
  LazySegTree<Lazy> seg(A);
  FOR(Q) {
    LL(t, L, R);
    ++R;
    if (t == 0) {
      LL(x);
      seg.apply(L, R, x);
    } else {
      print(seg.prod(L, R));
    }
  }
}

signed main() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);
  cout << setprecision(15);

  ll T = 1;
  // LL(T);
  FOR(_, T) solve();

  return 0;
}
