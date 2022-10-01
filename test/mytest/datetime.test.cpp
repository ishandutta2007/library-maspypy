#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"
#include "my_template.hpp"
#include "other/io.hpp"

#include "datetime/datetime.hpp"

using DT = DateTime;

void test_from_int() {
  DT A(1, 1, 1);
  FOR(x, 1000000) {
    DT B = DT::from_int(x);
    assert(A == B);
    assert(A.to_int() == x);
    ++A;
  }
}

void solve() {
  LL(a, b);
  print(a + b);
}

signed main() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);
  cout << setprecision(15);

  test_from_int();
  solve();

  return 0;
}
