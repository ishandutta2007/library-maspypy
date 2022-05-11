#include "nt/factor.hpp"
#include "mod/mod_pow.hpp"

template <typename INT>
struct Gaussian_Integer {
  INT x, y;
  using G = Gaussian_Integer;

  Gaussian_Integer(INT x = 0, INT y = 0) : x(x), y(y) {}
  Gaussian_Integer(pair<INT, INT> p) : x(p.fi), y(p.se) {}

  INT norm() const { return x * x + y * y; }
  G conjugate() const { return G(x, -y); }

  G &operator+=(const G &g) {
    x += g.x, y += g.y;
    return *this;
  }
  G &operator-=(const G &g) {
    x -= g.x, y -= g.y;
    return *this;
  }
  G &operator*=(const G &g) {
    tie(x, y) = mp(x * g.x - y * g.y, x * g.y + y * g.x);
    return *this;
  }
  G &operator/=(const G &g) {
    *this *= g.conjugate();
    INT n = g.norm();
    x = floor(x + n / 2, n);
    y = floor(y + n / 2, n);
    return *this;
  }
  G &operator%=(const G &g) {
    auto q = G(*this) / g;
    q *= g;
    (*this) -= q;
    return *this;
  }
  G operator-() { return G(-x, -y); }
  G operator+(const G &g) { return G(*this) += g; }
  G operator-(const G &g) { return G(*this) -= g; }
  G operator*(const G &g) { return G(*this) *= g; }
  G operator/(const G &g) { return G(*this) /= g; }
  G operator%(const G &g) { return G(*this) %= g; }
  bool operator==(const G &g) { return (x == g.x && y == g.y); }

  static G gcd(G a, G b) {
    while (b.x != 0 || b.y != 0) {
      a %= b;
      swap(a, b);
    }
    return a;
  }
};

template <typename INT>
vc<Gaussian_Integer<INT>> solve_norm_equation_factor(vc<pi> pfs) {
  using G = Gaussian_Integer<INT>;
  vc<G> res;
  for (auto &&[p, e]: pfs) {
    if (p % 4 == 3 && e % 2 == 1) return {};
  }
  auto find = [&](INT p) -> G {
    // p は素数. ノルム p のガウス整数をひとつ見つける
    if (p == 2) return G(1, 1);
    // x^2 = -1 mod p をひとつ見つける
    INT x = [&]() -> INT {
      INT x = 1;
      while (1) {
        ++x;
        INT pow_x = 1;
        if (p < (1 << 30)) {
          pow_x = mod_pow(x, (p - 1) / 4, p);
          if (pow_x * pow_x % p == p - 1) return pow_x;
        } else {
          pow_x = mod_pow_long(x, (p - 1) / 4, p);
          if (i128(pow_x) * pow_x % p == p - 1) return pow_x;
        }
      }
      return -1;
    }();
    assert(x != -1);
    // x は非剰余
    G a(p, 0), b(x, 1);
    a = G::gcd(a, b);
    assert(a.norm() == p);
    return a;
  };

  res.eb(G(1, 0));
  for (auto &&[p, e]: pfs) {
    if (p % 4 == 3) {
      INT pp = 1;
      FOR(e / 2) pp *= p;
      for (auto &&g: res) {
        g.x *= pp;
        g.y *= pp;
      }
      continue;
    }
    auto pi = find(p);
    vc<G> pows(e + 1);
    pows[0] = G(1, 0);
    FOR(i, e) pows[i + 1] = pows[i] * pi;
    if (p == 2) {
      for (auto &&g: res) g *= pows[e];
      continue;
    }
    vc<G> pis(e + 1);
    FOR(j, e + 1) { pis[j] = pows[j] * (pows[e - j].conjugate()); }
    vc<G> new_res;
    new_res.reserve(len(res) * (e + 1));
    for (auto &&g: res) {
      for (auto &&a: pis) { new_res.eb(g * a); }
    }
    swap(res, new_res);
  }

  for (auto &&g: res) {
    while (g.x <= 0 || g.y < 0) { g = G(-g.y, g.x); }
  }
  return res;
}

// ノルムがとれるように、2 乗してもオーバーフローしない型を使おう
// 0 <= arg < 90 となるもののみ返す。
// 単数倍は作らないので、使うときに気を付ける。
template <typename INT>
vc<Gaussian_Integer<INT>> solve_norm_equation(INT N) {
  using G = Gaussian_Integer<INT>;
  vc<G> res;
  if (N < 0) return {};
  if (N == 0) {
    res.eb(G(0, 0));
    return res;
  }
  auto pfs = factor(N);
  return solve_norm_equation_factor<INT>(pfs);
}
