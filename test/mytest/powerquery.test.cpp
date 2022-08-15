#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"
#include "my_template.hpp"
#include "other/io.hpp"
#include "other/random.hpp"

#include "ds/powerquery.hpp"
#include "alg/group_mul.hpp"
#include "mod/modint.hpp"

using mint = modint998;

void test() {
  RandomNumberGenerator RNG;
  mint base = RNG(0, mint::get_mod());
  PowerQuery<Group_Mul<mint>> X(base);
  FOR(1000) {
    ll exp = RNG(0, 1'000'000'000'000'000'000);
    mint a = base.pow(exp);
    mint b = X(exp);
    assert(a == b);
  }
}

void solve() {
  LL(a, b);
  print(a + b);
}

signed main() {
  cout << fixed << setprecision(15);

  FOR(10) test();
  solve();

  return 0;
}
