// 商が q の区間 [l,r) を q について昇順
template <typename F>
void ceil_range(ll N, F f) {
  assert(N <= (1LL << 50));
  ll sq = sqrtl(N);
  ll prev = infty<ll>;
  for (int q = 1; q <= sq; ++q) {
    ll x = (N + q - 1) / q;
    f(q, x, prev), prev = x;
  }
  int n = (N <= sq * sq + sq ? sq : sq + 1);
  if (N == sq * sq) --n;
  for (int l = n; l >= 1; --l) { f((N + l - 1) / l, l, l + 1); }
}
