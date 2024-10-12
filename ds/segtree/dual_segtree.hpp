#pragma once

template <typename Monoid>
struct Dual_SegTree {
  using MA = Monoid;
  using A = typename MA::value_type;
  int n, log, size;
  vc<A> laz;

  Dual_SegTree() : Dual_SegTree(0) {}
  Dual_SegTree(int n) {
    build(n, [&](int i) -> A { return MA::unit(); });
  }
  template <typename F>
  Dual_SegTree(int n, F f) {
    build(n, f);
  }

  template <typename F>
  void build(int m, F f) {
    n = m;
    log = 1;
    while ((1 << log) < n) ++log;
    size = 1 << log;
    laz.assign(size << 1, MA::unit());
    FOR(i, n) laz[size + i] = f(i);
  }
  void build(int n) {
    build(n, [&](int i) -> A { return MA::unit(); });
  }

  A get(int p) {
    assert(0 <= p && p < n);
    p += size;
    for (int i = log; i >= 1; i--) push(p >> i);
    return laz[p];
  }

  vc<A> get_all() {
    FOR(i, size) push(i);
    return {laz.begin() + size, laz.begin() + size + n};
  }

  void set(int p, A x) {
    get(p);
    laz[p + size] = x;
  }

  void apply(int l, int r, const A& a) {
    assert(0 <= l && l <= r && r <= n);
    if (l == r) return;
    l += size, r += size;
    if (!MA::commute) {
      for (int i = log; i >= 1; i--) {
        if (((l >> i) << i) != l) push(l >> i);
        if (((r >> i) << i) != r) push((r - 1) >> i);
      }
    }
    while (l < r) {
      if (l & 1) all_apply(l++, a);
      if (r & 1) all_apply(--r, a);
      l >>= 1, r >>= 1;
    }
  }

private:
  void push(int k) {
    if (laz[k] == MA::unit()) return;
    all_apply(2 * k, laz[k]), all_apply(2 * k + 1, laz[k]);
    laz[k] = MA::unit();
  }
  void all_apply(int k, A a) { laz[k] = MA::op(laz[k], a); }
};
