#include "random/base.hpp"
#include "linalg/mat_mul.hpp"
#include "linalg/mat_inv.hpp"
#include "linalg/characteristic_poly.hpp"
#include "poly/poly_taylor_shift.hpp"

// det(A + xB) = f(x) となる N 次多項式 f を返す
// 確率 N / mod で正しく解ける（乱数に依存しない方法もあるようだ）
template <typename mint>
vc<mint> det_A_plus_xB(vvc<mint> A, vvc<mint> B) {
  int N = len(A);
  vc<mint> f(N + 1);
  mint a = RNG(mint::get_mod());
  FOR(i, N) FOR(j, N) A[i][j] += a * B[i][j];
  auto [det_A, inv_A] = mat_inv(A);
  if (det_A == 0) { return f; }
  B = mat_mul(B, inv_A);
  FOR(i, N) FOR(j, N) B[i][j] = -B[i][j];
  f = characteristic_poly(B);
  reverse(all(f));
  for (auto&& x: f) x *= det_A;
  f = poly_taylor_shift(f, -a);
  return f;
}