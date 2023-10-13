#include "poly/convolution.hpp"

struct BigInteger_Binary {
  static constexpr int LOG = 30;
  static constexpr int MOD = 1 << LOG;
  using bint = BigInteger_Binary;
  int sgn; // +1 or -1. 内部状態で -0 を許容する.
  vc<int> dat;

  BigInteger_Binary() : sgn(1) {}
  BigInteger_Binary(i128 val) {
    sgn = 1;
    if (val != 0) {
      if (val < 0) sgn = -1, val = -val;
      while (val > 0) {
        dat.eb(val % MOD);
        val /= MOD;
      }
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
    if (s[0] == '0') s.clear();
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
  bint &operator+=(const bint &p) {
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
  bint &operator-=(const bint &p) {
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

  vc<int> convolve(const vc<int> &A, const vc<int> &B) {
    assert(0);
    return {};
    /*
    vc<ll> A1 = {A.begin(), A.end()};
    vc<ll> B1 = {B.begin(), B.end()};
    vc<ll> F = convolution(A1, B1);
    F.eb(0);
    FOR(i, len(F) - 1) { F[i + 1] += F[i] / MOD, F[i] = F[i] % MOD; }
    while (len(F) && F.back() == 0) POP(F);
    return {F.begin(), F.end()};
    */
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

#ifdef FASTIO
  void write() { fastio::printer.write(to_string()); }
  void read() {
    string s;
    fastio::scanner.read(s);
    *this = bint(s);
  }
#endif
};