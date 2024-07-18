#pragma once

#include "poly/ntt.hpp"

// 2^k 次多項式の長さ 2^k が与えられるので 2^k+1 にする
template <typename mint>
void ntt_doubling(vector<mint>& a) {
  static array<mint, 30> root;
  static bool prepared = 0;
  if (!prepared) {
    prepared = 1;
    const int rank2 = mint::ntt_info().fi;
    root[rank2] = mint::ntt_info().se;
    FOR_R(i, rank2) { root[i] = root[i + 1] * root[i + 1]; }
  }

  const int M = (int)a.size();
  auto b = a;
  ntt(b, 1);
  mint r = 1, zeta = root[topbit(2 * M)];
  FOR(i, M) b[i] *= r, r *= zeta;
  ntt(b, 0);
  copy(begin(b), end(b), back_inserter(a));
}
