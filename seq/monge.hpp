#include "ds/larsch.hpp"
#include "seq/monotone_minima.hpp"

// 定義域 [0, N] の範囲で f の monge 性を確認
template <typename T, typename F>
bool check_monge(int N, F f) {
  FOR(l, N + 1) FOR(k, l) FOR(j, k) FOR(i, j) {
    T lhs = f(i, l) + f(j, k);
    T rhs = f(i, k) + f(j, l);
    if (lhs < rhs) return false;
  }
  return true;
}

template <ll INF, typename F>
vi monge_shortest_path(int N, F f) {
  vi dp(N + 1, INF);
  dp[0] = 0;
  LARSCH<ll> larsch(N, [&](int i, int j) {
    ++i;
    if (i <= j) return INF;
    return dp[j] + f(j, i);
  });
  FOR3(r, 1, N + 1) {
    ll l = larsch.get_argmin();
    dp[r] = dp[l] + f(l, r);
  }
  return dp;
}

template <typename T, typename F>
vc<vc<T>> monge_shortest_path_d_edge_dense(int N, F f, T INF, int d_max) {
  vv(T, DP, d_max + 1, N + 1, INF);
  DP[0][0] = 0;
  FOR(d, d_max) {
    auto& dp = DP[d];
    auto& newdp = DP[d + 1];
    auto g = [&](int r, int l) -> T {
      //      print(l, r);
      if (r <= l) return INF;
      return dp[l] + f(l, r);
    };
    auto ret = monotone_minima<T>(N + 1, N + 1, g);
    FOR(j, N + 1) newdp[j] = ret[j].se;
  }
  return DP;
}

/*
https://dic.kimiyuki.net/d-edge-shortest-path-monge
上凸関数 calc_L(lambda) の最大値を求める問題に帰着
|f| の上限 f_lim も渡す
*/
template <ll INF, typename F>
ll monge_shortest_path_d_edge(ll N, F f, ll d, ll f_lim) {
  auto calc_L = [&](ll lambda) -> ll {
    auto cost = [&](int frm, int to) -> ll { return f(frm, to) + lambda; };
    auto dp = monge_shortest_path<INF>(N, cost);
    return dp.back() - lambda * d;
  };

  ll ANS = -INF;
  ll L = -3 * f_lim - 10;
  ll R = 3 * f_lim + 10;
  ll x = binary_search([&](ll x) { return calc_L(x - 1) <= calc_L(x); }, L, R);
  return calc_L(x);
}
