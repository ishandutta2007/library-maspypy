#include "setfunc/subset_convolution.hpp"
#include "poly/convolution.hpp"

// for fixed sps s, consider linear map F:a->b = subset-conv(a,s)
// given x, calculate transpose(F)(x)
template <typename mint, int LIM>
vc<mint> transposed_subset_convolution(vc<mint> s, vc<mint> x) {
  /*
  sum_{j}x_jb_j = sum_{i subset j}x_ja_is_{j-i} = sum_{i}y_ia_i.
  y_i = sum_{j supset i}x_js_{j-i}
  (rev y)_i = sum_{j subset i}(rev x)_js_{i-j}
  y = rev(conv(rev x), s)
  */
  reverse(all(x));
  x = subset_convolution<mint, LIM>(x, s);
  reverse(all(x));
  return x;
}

// assume s[0]==0
// calculate sum_i wt_i(s^k/k!)_i for k=0,1,...,N
template <typename mint, int LIM>
vc<mint> power_projection_of_sps_egf(vc<mint> wt, vc<mint>& s) {
  const int N = topbit(len(s));
  assert(len(s) == (1 << N) && len(wt) == (1 << N) && s[0] == mint(0));
  vc<mint> y(N + 1);
  y[0] = wt[0];
  auto& dp = wt;
  FOR(i, N) {
    vc<mint> newdp(1 << (N - 1 - i));
    FOR(j, N - i) {
      vc<mint> a = {s.begin() + (1 << j), s.begin() + (2 << j)};
      vc<mint> b = {dp.begin() + (1 << j), dp.begin() + (2 << j)};
      b = transposed_subset_convolution<mint, LIM>(a, b);
      FOR(k, len(b)) newdp[k] += b[k];
    }
    swap(dp, newdp);
    y[1 + i] = dp[0];
  }
  return y;
}

// calculate sum_i x_i(s^k)_i for k=0,1,...,M-1
template <typename mint, int LIM>
vc<mint> power_projection_of_sps(vc<mint> wt, vc<mint> s, int M) {
  const int N = topbit(len(s));
  assert(len(s) == (1 << N) && len(wt) == (1 << N));
  mint c = s[0];
  s[0] -= c;
  vc<mint> x = power_projection_of_sps_egf<mint, LIM>(wt, s);
  vc<mint> g(M);
  mint pow = 1;
  FOR(i, M) { g[i] = pow * fact_inv<mint>(i), pow *= c; }
  x = convolution<mint>(x, g);
  x.resize(M);
  FOR(i, M) x[i] *= fact<mint>(i);
  return x;
}
