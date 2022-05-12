#define PROBLEM "https://yukicoder.me/problems/no/1332"
#include "my_template.hpp"
#include "other/io.hpp"
#include "ds/waveletmatrix.hpp"

void solve() {
  LL(N);
  VEC(ll, X, N);
  WaveletMatrix<ll> WM(X);
  const ll INF = 1LL << 60;
  LL(Q);
  FOR(Q) {
    LL(l, r, x);
    --l;
    ll ANS = INF;
    ll n = WM.freq(l, r, 0, x);
    if (n > 0) chmin(ANS, abs(x - WM.kth(l, r, n - 1)));
    if (n < r - l) chmin(ANS, abs(x - WM.kth(l, r, n)));
    print(ANS);
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
