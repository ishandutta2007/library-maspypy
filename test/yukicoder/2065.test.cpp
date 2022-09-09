#define PROBLEM "https://yukicoder.me/problems/no/2065"
#include "my_template.hpp"
#include "other/io.hpp"
#include "ds/waveletmatrix.hpp"

void solve() {
  LL(N, Q);
  VEC(ll, A, N);
  WaveletMatrix_Sum<ll, true, Group_Add<ll>> X(A);
  FOR(Q) {
    LL(l, r, x);
    --l;
    ll k = X.freq(l, r, 0, x);
    ll sm = X.sum(l, r, k);
    ll ANS = (r - l - k) * x + sm;
    print(ANS);
  }
}

signed main() {
  cout << fixed << setprecision(15);

  ll T = 1;
  // LL(T);
  FOR(T) solve();

  return 0;
}
