#define PROBLEM "https://atcoder.jp/contests/arc154/tasks/arc154_f"
#include "my_template.hpp"
#include "other/io.hpp"
#include "mod/modint.hpp"
#include "poly/fps_div.hpp"
#include "poly/convolution_all.hpp"
#include "poly/composition_f_ex.hpp"

using mint = modint998;
using poly = vc<mint>;

void solve() {
  LL(N, M);
  vc<poly> DEN;
  mint cf = 1;
  FOR(i, N) {
    mint p = inv<mint>(N) * mint(N - i);
    mint q = mint(1) - p;
    cf *= p;
    DEN.eb(poly{mint(1), -q});
  }
  poly g = convolution_all(DEN);
  g.resize(M + 1);

  // e^{Nx}
  poly f(M + 1);
  mint pow = 1;
  FOR(i, M + 1) {
    f[i] = fact_inv<mint>(i) * pow;
    pow *= mint(N);
  }
  print(len(g), "g", g);
  g = composition_f_ex(g);
  print(len(g), "g", g);
  f = fps_div(f, g);
  FOR(i, 1, M + 1) print(f[i] * fact<mint>(i) * cf);
}

signed main() {
  solve();
  return 0;
}