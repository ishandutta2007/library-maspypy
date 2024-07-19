#include "poly/multipoint.hpp"
#include "poly/sum_of_rationals.hpp"
#include "poly/fps_div.hpp"

// transpose = 0：g[p] = sum pow(ap,q) f[q]
// transpose = 1：g[p] = sum pow(aq,p) f[q]
// (false, false) = multipoint eval
// (false, true) = multipoint interpolate
// (true, false) = sum of rationals
// (true, true) = partial frac decomposition (fps -> coefs)
template <typename mint>
vc<mint> vandermonde(vc<mint> f, vc<mint> A, bool transpose, bool inverse) {
  if (len(f) == 0) return vc<mint>();
  int N = len(f);
  if (!transpose) {
    if (!inverse) { return multipoint_eval(f, A); }
    if (inverse) { return multipoint_interpolate(A, f); }
  }
  if (!inverse) {
    auto [num, den] = sum_of_rationals_1<mint>(A, f);
    num.resize(N);
    return fps_div(num, den);
  }
  SubproductTree<mint> X(A);
  vc<mint> g = X.T[1]; // prod(1-ax)
  g.resize(N + 1);
  f = convolution<mint>(f, g);
  f.resize(N);
  reverse(all(f));
  reverse(all(g));
  FOR(i, len(g) - 1) g[i] = g[i + 1] * mint(i + 1);
  g.pop_back();
  auto num = X.evaluation(f);
  auto den = X.evaluation(g);
  vc<mint> B(len(A));
  FOR(i, len(A)) B[i] = num[i] / den[i];
  return B;
}