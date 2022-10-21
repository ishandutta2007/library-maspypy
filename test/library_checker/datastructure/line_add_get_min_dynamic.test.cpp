#define PROBLEM "https://judge.yosupo.jp/problem/line_add_get_min"
#include "my_template.hpp"
#include "other/io.hpp"

#include "ds/cht/dynamic_lichao.hpp"

void solve() {
  LL(N, Q);
  ll max = 1'000'000'000;
  Dynamic_LiChaoTree<ll, 500'000> seg(-max, max + 1);
  FOR(N) {
    LL(a, b);
    seg.add_line(a, b);
  }
  const ll INF = 1LL << 60;
  FOR(Q) {
    LL(t);
    if (t == 0) {
      LL(a, b);
      seg.add_line(a, b);
    }
    if (t == 1) {
      LL(x);
      ll y = seg.query(x).fi;
      if (y >= INF)
        print("INFINITY");
      else
        print(y);
    }
  }
}

signed main() {
  solve();

  return 0;
}
