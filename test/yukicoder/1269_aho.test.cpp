#define PROBLEM "https://yukicoder.me/problems/no/1269"
#include "my_template.hpp"
#include "other/io.hpp"
#include "string/trie.hpp"
#include "mod/modint.hpp"

using mint = modint107;

void solve() {
  LL(N, L, R);
  vi F = {1, 2};
  while (F.back() <= R) F.eb(F[len(F) - 2] + F[len(F) - 1]);
  {
    vi tmp;
    for (auto&& x: F)
      if (L <= x && x <= R) tmp.eb(x);
    F = tmp;
  }
  Trie<10> X;
  for (auto&& f: F) {
    string s = to_string(f);
    X.add(s, '0', 1);
  }
  X.make_failure();

  ll n = X.n_node;
  vc<mint> dp(n);
  dp[0] = 1;
  FOR(N) {
    vc<mint> newdp(n);
    FOR(v, n) {
      FOR(d, 10) {
        int to = X.TO[v][d];
        if (X.node_value[to]) continue;
        assert(0 <= to && to < n);
        newdp[to] += dp[v];
      }
    }
    swap(dp, newdp);
  }
  print(SUM(dp) - mint(1));
}

signed main() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);
  cout << setprecision(15);

  ll T = 1;
  // LL(T);
  FOR(T) solve();

  return 0;
}
