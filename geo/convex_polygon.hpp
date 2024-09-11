#pragma once

#include "geo/base.hpp"
#include "geo/convex_hull.hpp"

// n=2 は現状サポートしていない
template <typename T>
struct ConvexPolygon {
  using P = Point<T>;
  int n;
  vc<P> point;

  ConvexPolygon(vc<P> point_) : n(len(point_)), point(point_) {
    assert(n >= 3);
    FOR(i, n) {
      int j = nxt_idx(i), k = nxt_idx(j);
      assert((point[j] - point[i]).det(point[k] - point[i]) >= 0);
    }
  }

  // 比較関数 comp(i,j)
  template <typename F>
  int periodic_min_comp(F comp) {
    int L = 0, M = n, R = n + n;
    while (1) {
      if (R - L == 2) break;
      int L1 = (L + M) / 2, R1 = (M + R + 1) / 2;
      if (comp(L1 % n, M % n)) { R = M, M = L1; }
      elif (comp(R1 % n, M % n)) { L = M, M = R1; }
      else {
        L = L1, R = R1;
      }
    }
    return M % n;
  }

  int nxt_idx(int i) { return (i + 1 == n ? 0 : i + 1); }
  int prev_idx(int i) { return (i == 0 ? n - 1 : i - 1); }

  // 中：1, 境界：0, 外：-1. test した.
  int side(P p) {
    int L = 1, R = n - 1;
    T a = (point[L] - point[0]).det(p - point[0]);
    T b = (point[R] - point[0]).det(p - point[0]);
    if (a < 0 || b > 0) return -1;
    // p は 0 から見て [L,R] 方向
    while (R - L >= 2) {
      int M = (L + R) / 2;
      T c = (point[M] - point[0]).det(p - point[0]);
      if (c < 0)
        R = M, b = c;
      else
        L = M, a = c;
    }
    T c = (point[R] - point[L]).det(p - point[L]);
    T x = min({a, -b, c});
    if (x < 0) return -1;
    if (x > 0) return 1;
    // on triangle p[0]p[L]p[R]
    if (p == point[0]) return 0;
    if (c != 0 && a == 0 && L != 1) return 1;
    if (c != 0 && b == 0 && R != n - 1) return 1;
    return 0;
  }

  // return {min, idx}. test した.
  pair<T, int> min_dot(P p) {
    int idx = periodic_min_comp([&](int i, int j) -> bool { return point[i].dot(p) < point[j].dot(p); });
    return {point[idx].dot(p), idx};
  }

  // return {max, idx}. test した.
  pair<T, int> max_dot(P p) {
    int idx = periodic_min_comp([&](int i, int j) -> bool { return point[i].dot(p) > point[j].dot(p); });
    return {point[idx].dot(p), idx};
  }

  // p から見える範囲. p 辺に沿って見えるところも見えるとする. test した.
  // 多角形からの反時計順は [l,r] だが p から見た偏角順は [r,l] なので注意
  pair<int, int> visible_range(P p) {
    int a = periodic_min_comp([&](int i, int j) -> bool { return ((point[i] - p).det(point[j] - p) < 0); });
    int b = periodic_min_comp([&](int i, int j) -> bool { return ((point[i] - p).det(point[j] - p) > 0); });
    if ((p - point[a]).det(p - point[prev_idx(a)]) == T(0)) a = prev_idx(a);
    if ((p - point[b]).det(p - point[nxt_idx(b)]) == T(0)) b = nxt_idx(b);
    return {a, b};
  }

  // 線分が「内部と」交わるか
  // https://codeforces.com/contest/1906/problem/D
  bool check_cross(P A, P B) {
    FOR(2) {
      swap(A, B);
      auto [a, b] = visible_range(A);
      if ((point[a] - A).det(B - A) >= 0) return 0;
      if ((point[b] - A).det(B - A) <= 0) return 0;
    }
    return 1;
  }
};