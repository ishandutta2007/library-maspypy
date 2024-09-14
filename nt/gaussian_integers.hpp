#include "nt/factor.hpp"
#include "mod/mod_pow.hpp"

template <typename T>
struct Gaussian_Integer {
  T x, y;
  using G = Gaussian_Integer;

  Gaussian_Integer(T x = 0, T y = 0) : x(x), y(y) {}
  Gaussian_Integer(pair<T, T> p) : x(p.fi), y(p.se) {}

  T norm() const { return x * x + y * y; }
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
    T n = g.norm();
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

  G pow(ll n) const {
    assert(n >= 0);
    G ret(1), mul(*this);
    while (n > 0) {
      if (n & 1) ret *= mul;
      mul *= mul;
      n >>= 1;
    }
    return ret;
  }

  // (g,x,y) s.t ax+by=g
  static tuple<G, G, G> extgcd(G a, G b) {
    if (b.x != 0 || b.y != 0) {
      G q = a / b;
      auto [g, x, y] = extgcd(b, a - q * b);
      return {g, y, x - q * y};
    }
    return {a, G{1, 0}, G{0, 0}};
  }
};

pair<ll, ll> solve_norm_equation_prime(ll p) {
  using G = Gaussian_Integer<i128>;
  assert(p == 2 || p % 4 == 1);
  if (p == 2) return {1, 1};
  ll x = [&]() -> ll {
    ll x = 1;
    while (1) {
      ++x;
      ll pow_x = 1;
      if (p < (1 << 30)) {
        pow_x = mod_pow(x, (p - 1) / 4, p);
        if (pow_x * pow_x % p == p - 1) return pow_x;
      } else {
        pow_x = mod_pow_64(x, (p - 1) / 4, p);
        if (i128(pow_x) * pow_x % p == p - 1) return pow_x;
      }
    }
    return -1;
  }();
  G a(p, 0), b(x, 1);
  a = G::gcd(a, b);
  assert(a.norm() == p);
  return {a.x, a.y};
}

template <typename T>
vc<Gaussian_Integer<T>> solve_norm_equation_factor(vc<pair<ll, int>> pfs) {
  using G = Gaussian_Integer<T>;
  vc<G> res;
  for (auto &&[p, e]: pfs) {
    if (p % 4 == 3 && e % 2 == 1) return {};
  }

  res.eb(G(1, 0));
  for (auto &&[p, e]: pfs) {
    if (p % 4 == 3) {
      T pp = 1;
      FOR(e / 2) pp *= p;
      for (auto &&g: res) {
        g.x *= pp;
        g.y *= pp;
      }
      continue;
    }
    auto [pix, piy] = solve_norm_equation_prime(p);
    G pi(pix, piy);
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

// i128 を使うと N <= 10^{18} もできる
// ノルムがとれるように、2 乗してもオーバーフローしない型を使おう
// 0 <= arg < 90 となるもののみ返す。
// 単数倍は作らないので、使うときに気を付ける。
template <typename T>
vc<Gaussian_Integer<T>> solve_norm_equation(T N) {
  using G = Gaussian_Integer<T>;
  vc<G> res;
  if (N < 0) return {};
  if (N == 0) {
    res.eb(G(0, 0));
    return res;
  }
  auto pfs = factor(N);
  return solve_norm_equation_factor<T>(pfs);
}
