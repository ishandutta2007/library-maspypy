#include "poly/convolution.hpp"

struct BigInteger_Binary {
  static constexpr int LOG = 30;
  static constexpr int MOD = 1 << LOG;
  using bint = BigInteger_Binary;
  int sgn;
  vc<int> dat;

  BigInteger_Binary() : sgn(0) {}
  BigInteger_Binary(i128 val) {
    if (val == 0) {
      sgn = 0;
      return;
    }
    sgn = 1;
    if (val < 0) sgn = -1, val = -val;
    while (val > 0) {
      dat.eb(val % MOD);
      val /= MOD;
    }
  }
  BigInteger_Binary(string s) {
    assert(!s.empty());
    sgn = 1;
    if (s[0] == '-') {
      sgn = -1;
      s.erase(s.begin());
      assert(!s.empty());
    }
    if (s[0] == '0') {
      sgn = 0;
      return;
    }
    reverse(all(s));
    int n = len(s);
    int m = ceil(n, LOG);
    dat.assign(m, 0);
    FOR(i, n) { dat[i / LOG] += ((s[i] - '0') << (i % LOG)); }
  }
  bint &operator=(const bint &p) {
    sgn = p.sgn;
    dat = p.dat;
    return *this;
  }
  bool operator<(const bint &p) const {
    if (sgn != p.sgn) return sgn < p.sgn;
    if (sgn == 0) return false;
    if (len(dat) != len(p.dat)) {
      if (sgn == 1) return len(dat) < len(p.dat);
      if (sgn == -1) return len(dat) > len(p.dat);
    }
    FOR_R(i, len(dat)) {
      if (dat[i] == p.dat[i]) continue;
      if (sgn == 1) return dat[i] < p.dat[i];
      if (sgn == -1) return dat[i] > p.dat[i];
    }
    return false;
  }
  bool operator>(const bint &p) const { return p < *this; }
  bool operator<=(const bint &p) const { return !(*this > p); }
  bool operator>=(const bint &p) const { return !(*this < p); }
  bint &operator+=(const bint p) {
    if (sgn == 0) { return *this = p; }
    if (p.sgn == 0) { return *this; }
    if (sgn != p.sgn) {
      *this -= (-p);
      return *this;
    }
    int n = max(len(dat), len(p.dat));
    dat.resize(n + 1);
    FOR(i, n) {
      if (i < len(p.dat)) dat[i] += p.dat[i];
      if (dat[i] >= MOD) dat[i] -= MOD, dat[i + 1] += 1;
    }
    while (len(dat) && dat.back() == 0) dat.pop_back();
    return *this;
  }
  bint &operator-=(const bint p) {
    if (sgn == 0) return *this = (-p);
    if (p.sgn == 0) return *this;
    if (sgn != p.sgn) {
      *this += (-p);
      return *this;
    }
    if ((sgn == 1 && *this < p) || (sgn == -1 && *this > p)) {
      *this = p - *this;
      sgn = -sgn;
      return *this;
    }
    FOR(i, len(p.dat)) { dat[i] -= p.dat[i]; }
    FOR(i, len(dat) - 1) {
      if (dat[i] < 0) dat[i] += MOD, dat[i + 1] -= 1;
    }
    while (len(dat) && dat.back() == 0) { dat.pop_back(); }
    if (dat.empty()) sgn = 0;
    return *this;
  }
  bint &operator*=(const bint &p) {
    sgn *= p.sgn;
    dat = convolve(dat, p.dat);
    return *this;
  }
  // bint &operator/=(const bint &p) { return *this; }
  bint operator-() const {
    bint p = *this;
    p.sgn *= -1;
    return p;
  }
  bint operator+(const bint &p) const { return bint(*this) += p; }
  bint operator-(const bint &p) const { return bint(*this) -= p; }
  bint operator*(const bint &p) const { return bint(*this) *= p; }
  // bint operator/(const modint &p) const { return modint(*this) /= p; }
  bool operator==(const bint &p) const {
    return (sgn == p.sgn && dat == p.dat);
  }
  bool operator!=(const bint &p) const {
    return (sgn != p.sgn || dat != p.dat);
  }

  vc<int> convolve(const vc<int> &a, const vc<int> &b) {
    int n = len(a), m = len(b);
    if (!n || !m) return {};
    if (min(n, m) <= 500) {
      vc<int> c(n + m - 1);
      u128 x = 0;
      FOR(k, n + m - 1) {
        int s = max<int>(0, k + 1 - m), t = min<int>(k, n - 1);
        FOR(i, s, t + 1) { x += u64(a[i]) * b[k - i]; }
        c[k] = x % MOD, x = x / MOD;
      }
      while (x > 0) { c.eb(x % MOD), x = x / MOD; }
      return c;
    }
    static constexpr int p0 = 167772161;
    static constexpr int p1 = 469762049;
    static constexpr int p2 = 754974721;
    using mint0 = modint<p0>;
    using mint1 = modint<p1>;
    using mint2 = modint<p2>;
    vc<mint0> a0(all(a)), b0(all(b));
    vc<mint1> a1(all(a)), b1(all(b));
    vc<mint2> a2(all(a)), b2(all(b));
    auto c0 = convolution_ntt<mint0>(a0, b0);
    auto c1 = convolution_ntt<mint1>(a1, b1);
    auto c2 = convolution_ntt<mint2>(a2, b2);
    vc<int> c(len(c0));
    u128 x = 0;
    FOR(i, n + m - 1) {
      x += CRT3<u128, p0, p1, p2>(c0[i].val, c1[i].val, c2[i].val);
      c[i] = x % MOD, x = x / MOD;
    }
    while (x) { c.eb(x % MOD), x = x / MOD; }
    return c;
  }

  string to_string() {
    if (dat.empty()) return "0";
    string s;
    for (int x: dat) {
      FOR(LOG) {
        s += '0' + (x & 1);
        x /= 2;
      }
    }
    while (s.back() == '0') s.pop_back();
    if (sgn == -1) s += '-';
    reverse(all(s));
    return s;
  }

  string to_decimal_string() {
    assert(0);
    return "";
  }

  // https://codeforces.com/contest/477/problem/D
  pair<bint, int> divmod(int p) {
    assert(dat.empty() || sgn == 1);
    vc<int> after;
    ll rm = 0;
    FOR_R(i, len(dat)) {
      rm = rm * MOD + dat[i];
      after.eb(rm / p);
      rm = rm % p;
    }
    reverse(all(after));
    while (len(after) && after.back() == 0) POP(after);
    bint q;
    q.sgn = 1;
    q.dat = after;
    return {q, rm};
  }

  vc<int> base_p_representation(int p) {
    vc<u32> A(all(dat));
    vc<int> res;
    while (1) {
      while (len(A) && A.back() == u32(0)) POP(A);
      if (A.empty()) break;
      u64 rm = 0;
      FOR_R(i, len(A)) {
        rm = rm * MOD + A[i];
        A[i] = rm / p;
        rm %= p;
      }
      res.eb(rm);
    }
    reverse(all(res));
    return res;
  }

  void add_power_of_2(int k) {
    int q = k / LOG, r = k % LOG;
    if (sgn == 0) sgn = 1;
    if (q >= len(dat)) dat.resize(q + 1);
    if (sgn == 1) {
      dat[q] += 1 << r;
      while (dat[q] >= MOD) {
        dat[q] -= MOD;
        if (q + 1 >= len(dat)) dat.resize(q + 2);
        dat[q + 1] += 1;
        q += 1;
      }
    } else {
      dat[q] += 1 << r;
      while (dat[q] >= MOD) {
        dat[q] -= MOD;
        if (q + 1 >= len(dat)) dat.resize(q + 2);
        dat[q + 1] += 1;
        q += 1;
      }
    }
  }

  void substract_power_of_2(int k) {}
};

#ifdef FASTIO
void wt(BigInteger_Binary x) { fastio::wt(x.to_string()); }
#endif