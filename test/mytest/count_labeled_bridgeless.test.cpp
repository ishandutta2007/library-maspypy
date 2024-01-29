#line 1 "main.cpp"
#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#line 1 "library/my_template.hpp"
#if defined(LOCAL)
#include <my_template_compiled.hpp>
#else
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;
using u128 = unsigned __int128;
using f128 = __float128;

template <class T>
constexpr T infty = 0;
template <>
constexpr int infty<int> = 1'000'000'000;
template <>
constexpr ll infty<ll> = ll(infty<int>) * infty<int> * 2;
template <>
constexpr u32 infty<u32> = infty<int>;
template <>
constexpr u64 infty<u64> = infty<ll>;
template <>
constexpr i128 infty<i128> = i128(infty<ll>) * infty<ll>;
template <>
constexpr double infty<double> = infty<ll>;
template <>
constexpr long double infty<long double> = infty<ll>;

using pi = pair<ll, ll>;
using vi = vector<ll>;
template <class T>
using vc = vector<T>;
template <class T>
using vvc = vector<vc<T>>;
template <class T>
using vvvc = vector<vvc<T>>;
template <class T>
using vvvvc = vector<vvvc<T>>;
template <class T>
using vvvvvc = vector<vvvvc<T>>;
template <class T>
using pq = priority_queue<T>;
template <class T>
using pqg = priority_queue<T, vector<T>, greater<T>>;

#define vv(type, name, h, ...) \
  vector<vector<type>> name(h, vector<type>(__VA_ARGS__))
#define vvv(type, name, h, w, ...)   \
  vector<vector<vector<type>>> name( \
      h, vector<vector<type>>(w, vector<type>(__VA_ARGS__)))
#define vvvv(type, name, a, b, c, ...)       \
  vector<vector<vector<vector<type>>>> name( \
      a, vector<vector<vector<type>>>(       \
             b, vector<vector<type>>(c, vector<type>(__VA_ARGS__))))

// https://trap.jp/post/1224/
#define FOR1(a) for (ll _ = 0; _ < ll(a); ++_)
#define FOR2(i, a) for (ll i = 0; i < ll(a); ++i)
#define FOR3(i, a, b) for (ll i = a; i < ll(b); ++i)
#define FOR4(i, a, b, c) for (ll i = a; i < ll(b); i += (c))
#define FOR1_R(a) for (ll i = (a)-1; i >= ll(0); --i)
#define FOR2_R(i, a) for (ll i = (a)-1; i >= ll(0); --i)
#define FOR3_R(i, a, b) for (ll i = (b)-1; i >= ll(a); --i)
#define overload4(a, b, c, d, e, ...) e
#define overload3(a, b, c, d, ...) d
#define FOR(...) overload4(__VA_ARGS__, FOR4, FOR3, FOR2, FOR1)(__VA_ARGS__)
#define FOR_R(...) overload3(__VA_ARGS__, FOR3_R, FOR2_R, FOR1_R)(__VA_ARGS__)

#define FOR_subset(t, s) \
  for (ll t = (s); t >= 0; t = (t == 0 ? -1 : (t - 1) & (s)))
#define all(x) x.begin(), x.end()
#define len(x) ll(x.size())
#define elif else if

#define eb emplace_back
#define mp make_pair
#define mt make_tuple
#define fi first
#define se second

#define stoi stoll

int popcnt(int x) { return __builtin_popcount(x); }
int popcnt(u32 x) { return __builtin_popcount(x); }
int popcnt(ll x) { return __builtin_popcountll(x); }
int popcnt(u64 x) { return __builtin_popcountll(x); }
int popcnt_mod_2(int x) { return __builtin_parity(x); }
int popcnt_mod_2(u32 x) { return __builtin_parity(x); }
int popcnt_mod_2(ll x) { return __builtin_parityll(x); }
int popcnt_mod_2(u64 x) { return __builtin_parityll(x); }
// (0, 1, 2, 3, 4) -> (-1, 0, 1, 1, 2)
int topbit(int x) { return (x == 0 ? -1 : 31 - __builtin_clz(x)); }
int topbit(u32 x) { return (x == 0 ? -1 : 31 - __builtin_clz(x)); }
int topbit(ll x) { return (x == 0 ? -1 : 63 - __builtin_clzll(x)); }
int topbit(u64 x) { return (x == 0 ? -1 : 63 - __builtin_clzll(x)); }
// (0, 1, 2, 3, 4) -> (-1, 0, 1, 0, 2)
int lowbit(int x) { return (x == 0 ? -1 : __builtin_ctz(x)); }
int lowbit(u32 x) { return (x == 0 ? -1 : __builtin_ctz(x)); }
int lowbit(ll x) { return (x == 0 ? -1 : __builtin_ctzll(x)); }
int lowbit(u64 x) { return (x == 0 ? -1 : __builtin_ctzll(x)); }

template <typename T>
T floor(T a, T b) {
  return a / b - (a % b && (a ^ b) < 0);
}
template <typename T>
T ceil(T x, T y) {
  return floor(x + y - 1, y);
}
template <typename T>
T bmod(T x, T y) {
  return x - y * floor(x, y);
}
template <typename T>
pair<T, T> divmod(T x, T y) {
  T q = floor(x, y);
  return {q, x - q * y};
}

template <typename T, typename U>
T SUM(const vector<U>& A) {
  T sm = 0;
  for (auto&& a: A) sm += a;
  return sm;
}

#define MIN(v) *min_element(all(v))
#define MAX(v) *max_element(all(v))
#define LB(c, x) distance((c).begin(), lower_bound(all(c), (x)))
#define UB(c, x) distance((c).begin(), upper_bound(all(c), (x)))
#define UNIQUE(x) \
  sort(all(x)), x.erase(unique(all(x)), x.end()), x.shrink_to_fit()

template <typename T>
T POP(deque<T>& que) {
  T a = que.front();
  que.pop_front();
  return a;
}
template <typename T>
T POP(pq<T>& que) {
  T a = que.top();
  que.pop();
  return a;
}
template <typename T>
T POP(pqg<T>& que) {
  T a = que.top();
  que.pop();
  return a;
}
template <typename T>
T POP(vc<T>& que) {
  T a = que.back();
  que.pop_back();
  return a;
}

template <typename F>
ll binary_search(F check, ll ok, ll ng, bool check_ok = true) {
  if (check_ok) assert(check(ok));
  while (abs(ok - ng) > 1) {
    auto x = (ng + ok) / 2;
    (check(x) ? ok : ng) = x;
  }
  return ok;
}
template <typename F>
double binary_search_real(F check, double ok, double ng, int iter = 100) {
  FOR(iter) {
    double x = (ok + ng) / 2;
    (check(x) ? ok : ng) = x;
  }
  return (ok + ng) / 2;
}

template <class T, class S>
inline bool chmax(T& a, const S& b) {
  return (a < b ? a = b, 1 : 0);
}
template <class T, class S>
inline bool chmin(T& a, const S& b) {
  return (a > b ? a = b, 1 : 0);
}

// ? は -1
vc<int> s_to_vi(const string& S, char first_char) {
  vc<int> A(S.size());
  FOR(i, S.size()) { A[i] = (S[i] != '?' ? S[i] - first_char : -1); }
  return A;
}

template <typename T, typename U>
vector<T> cumsum(vector<U>& A, int off = 1) {
  int N = A.size();
  vector<T> B(N + 1);
  FOR(i, N) { B[i + 1] = B[i] + A[i]; }
  if (off == 0) B.erase(B.begin());
  return B;
}

// stable sort
template <typename T>
vector<int> argsort(const vector<T>& A) {
  vector<int> ids(len(A));
  iota(all(ids), 0);
  sort(all(ids),
       [&](int i, int j) { return (A[i] == A[j] ? i < j : A[i] < A[j]); });
  return ids;
}

// A[I[0]], A[I[1]], ...
template <typename T>
vc<T> rearrange(const vc<T>& A, const vc<int>& I) {
  vc<T> B(len(I));
  FOR(i, len(I)) B[i] = A[I[i]];
  return B;
}
#endif
#line 4 "main.cpp"

#line 2 "library/mod/modint_common.hpp"

struct has_mod_impl {
  template <class T>
  static auto check(T&& x) -> decltype(x.get_mod(), std::true_type{});
  template <class T>
  static auto check(...) -> std::false_type;
};

template <class T>
class has_mod : public decltype(has_mod_impl::check<T>(std::declval<T>())) {};

template <typename mint>
mint inv(int n) {
  static const int mod = mint::get_mod();
  static vector<mint> dat = {0, 1};
  assert(0 <= n);
  if (n >= mod) n %= mod;
  while (len(dat) <= n) {
    int k = len(dat);
    int q = (mod + k - 1) / k;
    dat.eb(dat[k * q - mod] * mint::raw(q));
  }
  return dat[n];
}

template <typename mint>
mint fact(int n) {
  static const int mod = mint::get_mod();
  assert(0 <= n && n < mod);
  static vector<mint> dat = {1, 1};
  while (len(dat) <= n) dat.eb(dat[len(dat) - 1] * mint::raw(len(dat)));
  return dat[n];
}

template <typename mint>
mint fact_inv(int n) {
  static vector<mint> dat = {1, 1};
  if (n < 0) return mint(0);
  while (len(dat) <= n) dat.eb(dat[len(dat) - 1] * inv<mint>(len(dat)));
  return dat[n];
}

template <class mint, class... Ts>
mint fact_invs(Ts... xs) {
  return (mint(1) * ... * fact_inv<mint>(xs));
}

template <typename mint, class Head, class... Tail>
mint multinomial(Head&& head, Tail&&... tail) {
  return fact<mint>(head) * fact_invs<mint>(std::forward<Tail>(tail)...);
}

template <typename mint>
mint C_dense(int n, int k) {
  static vvc<mint> C;
  static int H = 0, W = 0;
  auto calc = [&](int i, int j) -> mint {
    if (i == 0) return (j == 0 ? mint(1) : mint(0));
    return C[i - 1][j] + (j ? C[i - 1][j - 1] : 0);
  };
  if (W <= k) {
    FOR(i, H) {
      C[i].resize(k + 1);
      FOR(j, W, k + 1) { C[i][j] = calc(i, j); }
    }
    W = k + 1;
  }
  if (H <= n) {
    C.resize(n + 1);
    FOR(i, H, n + 1) {
      C[i].resize(W);
      FOR(j, W) { C[i][j] = calc(i, j); }
    }
    H = n + 1;
  }
  return C[n][k];
}

template <typename mint, bool large = false, bool dense = false>
mint C(ll n, ll k) {
  assert(n >= 0);
  if (k < 0 || n < k) return 0;
  if constexpr (dense) return C_dense<mint>(n, k);
  if constexpr (!large) return multinomial<mint>(n, k, n - k);
  k = min(k, n - k);
  mint x(1);
  FOR(i, k) x *= mint(n - i);
  return x * fact_inv<mint>(k);
}

template <typename mint, bool large = false>
mint C_inv(ll n, ll k) {
  assert(n >= 0);
  assert(0 <= k && k <= n);
  if (!large) return fact_inv<mint>(n) * fact<mint>(k) * fact<mint>(n - k);
  return mint(1) / C<mint, 1>(n, k);
}

// [x^d](1-x)^{-n}
template <typename mint, bool large = false, bool dense = false>
mint C_negative(ll n, ll d) {
  assert(n >= 0);
  if (d < 0) return mint(0);
  if (n == 0) { return (d == 0 ? mint(1) : mint(0)); }
  return C<mint, large, dense>(n + d - 1, d);
}
#line 3 "library/mod/modint.hpp"

template <int mod>
struct modint {
  static constexpr u32 umod = u32(mod);
  static_assert(umod < u32(1) << 31);
  u32 val;

  static modint raw(u32 v) {
    modint x;
    x.val = v;
    return x;
  }
  constexpr modint() : val(0) {}
  constexpr modint(u32 x) : val(x % umod) {}
  constexpr modint(u64 x) : val(x % umod) {}
  constexpr modint(u128 x) : val(x % umod) {}
  constexpr modint(int x) : val((x %= mod) < 0 ? x + mod : x){};
  constexpr modint(ll x) : val((x %= mod) < 0 ? x + mod : x){};
  constexpr modint(i128 x) : val((x %= mod) < 0 ? x + mod : x){};
  bool operator<(const modint& other) const { return val < other.val; }
  modint& operator+=(const modint& p) {
    if ((val += p.val) >= umod) val -= umod;
    return *this;
  }
  modint& operator-=(const modint& p) {
    if ((val += umod - p.val) >= umod) val -= umod;
    return *this;
  }
  modint& operator*=(const modint& p) {
    val = u64(val) * p.val % umod;
    return *this;
  }
  modint& operator/=(const modint& p) {
    *this *= p.inverse();
    return *this;
  }
  modint operator-() const { return modint::raw(val ? mod - val : u32(0)); }
  modint operator+(const modint& p) const { return modint(*this) += p; }
  modint operator-(const modint& p) const { return modint(*this) -= p; }
  modint operator*(const modint& p) const { return modint(*this) *= p; }
  modint operator/(const modint& p) const { return modint(*this) /= p; }
  bool operator==(const modint& p) const { return val == p.val; }
  bool operator!=(const modint& p) const { return val != p.val; }
  modint inverse() const {
    int a = val, b = mod, u = 1, v = 0, t;
    while (b > 0) {
      t = a / b;
      swap(a -= t * b, b), swap(u -= t * v, v);
    }
    return modint(u);
  }
  modint pow(ll n) const {
    assert(n >= 0);
    modint ret(1), mul(val);
    while (n > 0) {
      if (n & 1) ret *= mul;
      mul *= mul;
      n >>= 1;
    }
    return ret;
  }
  static constexpr int get_mod() { return mod; }
  // (n, r), r は 1 の 2^n 乗根
  static constexpr pair<int, int> ntt_info() {
    if (mod == 120586241) return {20, 74066978};
    if (mod == 167772161) return {25, 17};
    if (mod == 469762049) return {26, 30};
    if (mod == 754974721) return {24, 362};
    if (mod == 880803841) return {23, 211};
    if (mod == 943718401) return {22, 663003469};
    if (mod == 998244353) return {23, 31};
    if (mod == 1045430273) return {20, 363};
    if (mod == 1051721729) return {20, 330};
    if (mod == 1053818881) return {20, 2789};
    return {-1, -1};
  }
  static constexpr bool can_ntt() { return ntt_info().fi != -1; }
};

#ifdef FASTIO
template <int mod>
void rd(modint<mod>& x) {
  fastio::rd(x.val);
  x.val %= mod;
  // assert(0 <= x.val && x.val < mod);
}
template <int mod>
void wt(modint<mod> x) {
  fastio::wt(x.val);
}
#endif

using modint107 = modint<1000000007>;
using modint998 = modint<998244353>;
#line 1 "library/graph/count/count_labeled_undirected.hpp"
// https://oeis.org/A006125
template <typename mint>
vc<mint> count_labeled_undirected(int N) {
  vc<mint> F(N + 1);
  mint pow2 = 1;
  F[0] = 1;
  FOR(i, 1, N + 1) F[i] = F[i - 1] * pow2, pow2 += pow2;
  return F;
}
#line 2 "library/poly/fps_log.hpp"

#line 2 "library/poly/count_terms.hpp"
template <typename mint>
int count_terms(const vc<mint>& f) {
  int t = 0;
  FOR(i, len(f)) if (f[i] != mint(0))++ t;
  return t;
}
#line 2 "library/mod/mod_inv.hpp"

// long でも大丈夫
// (val * x - 1) が mod の倍数になるようにする
// 特に mod=0 なら x=0 が満たす
ll mod_inv(ll val, ll mod) {
  if (mod == 0) return 0;
  mod = abs(mod);
  val %= mod;
  if (val < 0) val += mod;
  ll a = val, b = mod, u = 1, v = 0, t;
  while (b > 0) {
    t = a / b;
    swap(a -= t * b, b), swap(u -= t * v, v);
  }
  if (u < 0) u += mod;
  return u;
}
#line 1 "library/mod/crt3.hpp"

constexpr u32 mod_pow_constexpr(u64 a, u64 n, u32 mod) {
  a %= mod;
  u64 res = 1;
  FOR(32) {
    if (n & 1) res = res * a % mod;
    a = a * a % mod, n /= 2;
  }
  return res;
}

template <typename T, u32 p0, u32 p1, u32 p2>
T CRT3(u64 a0, u64 a1, u64 a2) {
  static_assert(p0 < p1 && p1 < p2);
  static constexpr u64 x0_1 = mod_pow_constexpr(p0, p1 - 2, p1);
  static constexpr u64 x01_2 = mod_pow_constexpr(u64(p0) * p1 % p2, p2 - 2, p2);
  u64 c = (a1 - a0 + p1) * x0_1 % p1;
  u64 a = a0 + c * p0;
  c = (a2 - a % p2 + p2) * x01_2 % p2;
  return T(a) + T(c) * T(p0) * T(p1);
}
#line 2 "library/poly/convolution_naive.hpp"

template <class T, typename enable_if<!has_mod<T>::value>::type* = nullptr>
vc<T> convolution_naive(const vc<T>& a, const vc<T>& b) {
  int n = int(a.size()), m = int(b.size());
  if (n > m) return convolution_naive<T>(b, a);
  if (n == 0) return {};
  vector<T> ans(n + m - 1);
  FOR(i, n) FOR(j, m) ans[i + j] += a[i] * b[j];
  return ans;
}

template <class T, typename enable_if<has_mod<T>::value>::type* = nullptr>
vc<T> convolution_naive(const vc<T>& a, const vc<T>& b) {
  int n = int(a.size()), m = int(b.size());
  if (n > m) return convolution_naive<T>(b, a);
  if (n == 0) return {};
  vc<T> ans(n + m - 1);
  if (n <= 16 && (T::get_mod() < (1 << 30))) {
    for (int k = 0; k < n + m - 1; ++k) {
      int s = max(0, k - m + 1);
      int t = min(n, k + 1);
      u64 sm = 0;
      for (int i = s; i < t; ++i) { sm += u64(a[i].val) * (b[k - i].val); }
      ans[k] = sm;
    }
  } else {
    for (int k = 0; k < n + m - 1; ++k) {
      int s = max(0, k - m + 1);
      int t = min(n, k + 1);
      u128 sm = 0;
      for (int i = s; i < t; ++i) { sm += u64(a[i].val) * (b[k - i].val); }
      ans[k] = T::raw(sm % T::get_mod());
    }
  }
  return ans;
}
#line 2 "library/poly/convolution_karatsuba.hpp"

// 任意の環でできる
template <typename T>
vc<T> convolution_karatsuba(const vc<T>& f, const vc<T>& g) {
  const int thresh = 30;
  if (min(len(f), len(g)) <= thresh) return convolution_naive(f, g);
  int n = max(len(f), len(g));
  int m = ceil(n, 2);
  vc<T> f1, f2, g1, g2;
  if (len(f) < m) f1 = f;
  if (len(f) >= m) f1 = {f.begin(), f.begin() + m};
  if (len(f) >= m) f2 = {f.begin() + m, f.end()};
  if (len(g) < m) g1 = g;
  if (len(g) >= m) g1 = {g.begin(), g.begin() + m};
  if (len(g) >= m) g2 = {g.begin() + m, g.end()};
  vc<T> a = convolution_karatsuba(f1, g1);
  vc<T> b = convolution_karatsuba(f2, g2);
  FOR(i, len(f2)) f1[i] += f2[i];
  FOR(i, len(g2)) g1[i] += g2[i];
  vc<T> c = convolution_karatsuba(f1, g1);
  vc<T> F(len(f) + len(g) - 1);
  assert(2 * m + len(b) <= len(F));
  FOR(i, len(a)) F[i] += a[i], c[i] -= a[i];
  FOR(i, len(b)) F[2 * m + i] += b[i], c[i] -= b[i];
  if (c.back() == T(0)) c.pop_back();
  FOR(i, len(c)) if (c[i] != T(0)) F[m + i] += c[i];
  return F;
}
#line 2 "library/poly/ntt.hpp"

template <class mint>
void ntt(vector<mint>& a, bool inverse) {
  assert(mint::can_ntt());
  const int rank2 = mint::ntt_info().fi;
  const int mod = mint::get_mod();
  static array<mint, 30> root, iroot;
  static array<mint, 30> rate2, irate2;
  static array<mint, 30> rate3, irate3;

  assert(rank2 != -1 && len(a) <= (1 << max(0, rank2)));

  static bool prepared = 0;
  if (!prepared) {
    prepared = 1;
    root[rank2] = mint::ntt_info().se;
    iroot[rank2] = mint(1) / root[rank2];
    FOR_R(i, rank2) {
      root[i] = root[i + 1] * root[i + 1];
      iroot[i] = iroot[i + 1] * iroot[i + 1];
    }
    mint prod = 1, iprod = 1;
    for (int i = 0; i <= rank2 - 2; i++) {
      rate2[i] = root[i + 2] * prod;
      irate2[i] = iroot[i + 2] * iprod;
      prod *= iroot[i + 2];
      iprod *= root[i + 2];
    }
    prod = 1, iprod = 1;
    for (int i = 0; i <= rank2 - 3; i++) {
      rate3[i] = root[i + 3] * prod;
      irate3[i] = iroot[i + 3] * iprod;
      prod *= iroot[i + 3];
      iprod *= root[i + 3];
    }
  }

  int n = int(a.size());
  int h = topbit(n);
  assert(n == 1 << h);
  if (!inverse) {
    int len = 0;
    while (len < h) {
      if (h - len == 1) {
        int p = 1 << (h - len - 1);
        mint rot = 1;
        FOR(s, 1 << len) {
          int offset = s << (h - len);
          FOR(i, p) {
            auto l = a[i + offset];
            auto r = a[i + offset + p] * rot;
            a[i + offset] = l + r;
            a[i + offset + p] = l - r;
          }
          rot *= rate2[topbit(~s & -~s)];
        }
        len++;
      } else {
        int p = 1 << (h - len - 2);
        mint rot = 1, imag = root[2];
        for (int s = 0; s < (1 << len); s++) {
          mint rot2 = rot * rot;
          mint rot3 = rot2 * rot;
          int offset = s << (h - len);
          for (int i = 0; i < p; i++) {
            u64 mod2 = u64(mod) * mod;
            u64 a0 = a[i + offset].val;
            u64 a1 = u64(a[i + offset + p].val) * rot.val;
            u64 a2 = u64(a[i + offset + 2 * p].val) * rot2.val;
            u64 a3 = u64(a[i + offset + 3 * p].val) * rot3.val;
            u64 a1na3imag = (a1 + mod2 - a3) % mod * imag.val;
            u64 na2 = mod2 - a2;
            a[i + offset] = a0 + a2 + a1 + a3;
            a[i + offset + 1 * p] = a0 + a2 + (2 * mod2 - (a1 + a3));
            a[i + offset + 2 * p] = a0 + na2 + a1na3imag;
            a[i + offset + 3 * p] = a0 + na2 + (mod2 - a1na3imag);
          }
          rot *= rate3[topbit(~s & -~s)];
        }
        len += 2;
      }
    }
  } else {
    mint coef = mint(1) / mint(len(a));
    FOR(i, len(a)) a[i] *= coef;
    int len = h;
    while (len) {
      if (len == 1) {
        int p = 1 << (h - len);
        mint irot = 1;
        FOR(s, 1 << (len - 1)) {
          int offset = s << (h - len + 1);
          FOR(i, p) {
            u64 l = a[i + offset].val;
            u64 r = a[i + offset + p].val;
            a[i + offset] = l + r;
            a[i + offset + p] = (mod + l - r) * irot.val;
          }
          irot *= irate2[topbit(~s & -~s)];
        }
        len--;
      } else {
        int p = 1 << (h - len);
        mint irot = 1, iimag = iroot[2];
        FOR(s, (1 << (len - 2))) {
          mint irot2 = irot * irot;
          mint irot3 = irot2 * irot;
          int offset = s << (h - len + 2);
          for (int i = 0; i < p; i++) {
            u64 a0 = a[i + offset + 0 * p].val;
            u64 a1 = a[i + offset + 1 * p].val;
            u64 a2 = a[i + offset + 2 * p].val;
            u64 a3 = a[i + offset + 3 * p].val;
            u64 x = (mod + a2 - a3) * iimag.val % mod;
            a[i + offset] = a0 + a1 + a2 + a3;
            a[i + offset + 1 * p] = (a0 + mod - a1 + x) * irot.val;
            a[i + offset + 2 * p] = (a0 + a1 + 2 * mod - a2 - a3) * irot2.val;
            a[i + offset + 3 * p] = (a0 + 2 * mod - a1 - x) * irot3.val;
          }
          irot *= irate3[topbit(~s & -~s)];
        }
        len -= 2;
      }
    }
  }
}
#line 1 "library/poly/fft.hpp"
namespace CFFT {
using real = double;

struct C {
  real x, y;

  C() : x(0), y(0) {}

  C(real x, real y) : x(x), y(y) {}
  inline C operator+(const C& c) const { return C(x + c.x, y + c.y); }
  inline C operator-(const C& c) const { return C(x - c.x, y - c.y); }
  inline C operator*(const C& c) const {
    return C(x * c.x - y * c.y, x * c.y + y * c.x);
  }

  inline C conj() const { return C(x, -y); }
};

const real PI = acosl(-1);
int base = 1;
vector<C> rts = {{0, 0}, {1, 0}};
vector<int> rev = {0, 1};

void ensure_base(int nbase) {
  if (nbase <= base) return;
  rev.resize(1 << nbase);
  rts.resize(1 << nbase);
  for (int i = 0; i < (1 << nbase); i++) {
    rev[i] = (rev[i >> 1] >> 1) + ((i & 1) << (nbase - 1));
  }
  while (base < nbase) {
    real angle = PI * 2.0 / (1 << (base + 1));
    for (int i = 1 << (base - 1); i < (1 << base); i++) {
      rts[i << 1] = rts[i];
      real angle_i = angle * (2 * i + 1 - (1 << base));
      rts[(i << 1) + 1] = C(cos(angle_i), sin(angle_i));
    }
    ++base;
  }
}

void fft(vector<C>& a, int n) {
  assert((n & (n - 1)) == 0);
  int zeros = __builtin_ctz(n);
  ensure_base(zeros);
  int shift = base - zeros;
  for (int i = 0; i < n; i++) {
    if (i < (rev[i] >> shift)) { swap(a[i], a[rev[i] >> shift]); }
  }
  for (int k = 1; k < n; k <<= 1) {
    for (int i = 0; i < n; i += 2 * k) {
      for (int j = 0; j < k; j++) {
        C z = a[i + j + k] * rts[j + k];
        a[i + j + k] = a[i + j] - z;
        a[i + j] = a[i + j] + z;
      }
    }
  }
}
} // namespace CFFT
#line 9 "library/poly/convolution.hpp"

template <class mint>
vector<mint> convolution_ntt(vector<mint> a, vector<mint> b) {
  if (a.empty() || b.empty()) return {};
  int n = int(a.size()), m = int(b.size());
  int sz = 1;
  while (sz < n + m - 1) sz *= 2;

  // sz = 2^k のときの高速化。分割統治的なやつで損しまくるので。
  if ((n + m - 3) <= sz / 2) {
    auto a_last = a.back(), b_last = b.back();
    a.pop_back(), b.pop_back();
    auto c = convolution(a, b);
    c.resize(n + m - 1);
    c[n + m - 2] = a_last * b_last;
    FOR(i, len(a)) c[i + len(b)] += a[i] * b_last;
    FOR(i, len(b)) c[i + len(a)] += b[i] * a_last;
    return c;
  }

  a.resize(sz), b.resize(sz);
  bool same = a == b;
  ntt(a, 0);
  if (same) {
    b = a;
  } else {
    ntt(b, 0);
  }
  FOR(i, sz) a[i] *= b[i];
  ntt(a, 1);
  a.resize(n + m - 1);
  return a;
}

template <typename mint>
vector<mint> convolution_garner(const vector<mint>& a, const vector<mint>& b) {
  int n = len(a), m = len(b);
  if (!n || !m) return {};
  static constexpr int p0 = 167772161;
  static constexpr int p1 = 469762049;
  static constexpr int p2 = 754974721;
  using mint0 = modint<p0>;
  using mint1 = modint<p1>;
  using mint2 = modint<p2>;
  vc<mint0> a0(n), b0(m);
  vc<mint1> a1(n), b1(m);
  vc<mint2> a2(n), b2(m);
  FOR(i, n) a0[i] = a[i].val, a1[i] = a[i].val, a2[i] = a[i].val;
  FOR(i, m) b0[i] = b[i].val, b1[i] = b[i].val, b2[i] = b[i].val;
  auto c0 = convolution_ntt<mint0>(a0, b0);
  auto c1 = convolution_ntt<mint1>(a1, b1);
  auto c2 = convolution_ntt<mint2>(a2, b2);
  vc<mint> c(len(c0));
  FOR(i, n + m - 1) {
    c[i] = CRT3<mint, p0, p1, p2>(c0[i].val, c1[i].val, c2[i].val);
  }
  return c;
}

template <typename R>
vc<double> convolution_fft(const vc<R>& a, const vc<R>& b) {
  using C = CFFT::C;
  int need = (int)a.size() + (int)b.size() - 1;
  int nbase = 1;
  while ((1 << nbase) < need) nbase++;
  CFFT::ensure_base(nbase);
  int sz = 1 << nbase;
  vector<C> fa(sz);
  for (int i = 0; i < sz; i++) {
    double x = (i < (int)a.size() ? a[i] : 0);
    double y = (i < (int)b.size() ? b[i] : 0);
    fa[i] = C(x, y);
  }
  CFFT::fft(fa, sz);
  C r(0, -0.25 / (sz >> 1)), s(0, 1), t(0.5, 0);
  for (int i = 0; i <= (sz >> 1); i++) {
    int j = (sz - i) & (sz - 1);
    C z = (fa[j] * fa[j] - (fa[i] * fa[i]).conj()) * r;
    fa[j] = (fa[i] * fa[i] - (fa[j] * fa[j]).conj()) * r;
    fa[i] = z;
  }
  for (int i = 0; i < (sz >> 1); i++) {
    C A0 = (fa[i] + fa[i + (sz >> 1)]) * t;
    C A1 = (fa[i] - fa[i + (sz >> 1)]) * t * CFFT::rts[(sz >> 1) + i];
    fa[i] = A0 + A1 * s;
  }
  CFFT::fft(fa, sz >> 1);
  vector<double> ret(need);
  for (int i = 0; i < need; i++) {
    ret[i] = (i & 1 ? fa[i >> 1].y : fa[i >> 1].x);
  }
  return ret;
}

vector<ll> convolution(const vector<ll>& a, const vector<ll>& b) {
  int n = len(a), m = len(b);
  if (!n || !m) return {};
  if (min(n, m) <= 2500) return convolution_naive(a, b);
  ll abs_sum_a = 0, abs_sum_b = 0;
  ll LIM = 1e15;
  FOR(i, n) abs_sum_a = min(LIM, abs_sum_a + abs(a[i]));
  FOR(i, m) abs_sum_b = min(LIM, abs_sum_b + abs(b[i]));
  if (i128(abs_sum_a) * abs_sum_b < 1e15) {
    vc<double> c = convolution_fft<ll>(a, b);
    vc<ll> res(len(c));
    FOR(i, len(c)) res[i] = ll(floor(c[i] + .5));
    return res;
  }

  static constexpr unsigned long long MOD1 = 754974721; // 2^24
  static constexpr unsigned long long MOD2 = 167772161; // 2^25
  static constexpr unsigned long long MOD3 = 469762049; // 2^26
  static constexpr unsigned long long M2M3 = MOD2 * MOD3;
  static constexpr unsigned long long M1M3 = MOD1 * MOD3;
  static constexpr unsigned long long M1M2 = MOD1 * MOD2;
  static constexpr unsigned long long M1M2M3 = MOD1 * MOD2 * MOD3;

  static const unsigned long long i1 = mod_inv(MOD2 * MOD3, MOD1);
  static const unsigned long long i2 = mod_inv(MOD1 * MOD3, MOD2);
  static const unsigned long long i3 = mod_inv(MOD1 * MOD2, MOD3);

  using mint1 = modint<MOD1>;
  using mint2 = modint<MOD2>;
  using mint3 = modint<MOD3>;

  vc<mint1> a1(n), b1(m);
  vc<mint2> a2(n), b2(m);
  vc<mint3> a3(n), b3(m);
  FOR(i, n) a1[i] = a[i], a2[i] = a[i], a3[i] = a[i];
  FOR(i, m) b1[i] = b[i], b2[i] = b[i], b3[i] = b[i];

  auto c1 = convolution_ntt<mint1>(a1, b1);
  auto c2 = convolution_ntt<mint2>(a2, b2);
  auto c3 = convolution_ntt<mint3>(a3, b3);

  vc<ll> c(n + m - 1);
  FOR(i, n + m - 1) {
    u64 x = 0;
    x += (c1[i].val * i1) % MOD1 * M2M3;
    x += (c2[i].val * i2) % MOD2 * M1M3;
    x += (c3[i].val * i3) % MOD3 * M1M2;
    ll diff = c1[i].val - ((long long)(x) % (long long)(MOD1));
    if (diff < 0) diff += MOD1;
    static constexpr unsigned long long offset[5]
        = {0, 0, M1M2M3, 2 * M1M2M3, 3 * M1M2M3};
    x -= offset[diff % 5];
    c[i] = x;
  }
  return c;
}

template <typename mint>
vc<mint> convolution(const vc<mint>& a, const vc<mint>& b) {
  int n = len(a), m = len(b);
  if (!n || !m) return {};
  if (mint::can_ntt()) {
    if (min(n, m) <= 50) return convolution_karatsuba<mint>(a, b);
    return convolution_ntt(a, b);
  }
  if (min(n, m) <= 200) return convolution_karatsuba<mint>(a, b);
  return convolution_garner(a, b);
}
#line 4 "library/poly/fps_inv.hpp"

template <typename mint>
vc<mint> fps_inv_sparse(const vc<mint>& f) {
  int N = len(f);
  vc<pair<int, mint>> dat;
  FOR(i, 1, N) if (f[i] != mint(0)) dat.eb(i, f[i]);
  vc<mint> g(N);
  mint g0 = mint(1) / f[0];
  g[0] = g0;
  FOR(n, 1, N) {
    mint rhs = 0;
    for (auto&& [k, fk]: dat) {
      if (k > n) break;
      rhs -= fk * g[n - k];
    }
    g[n] = rhs * g0;
  }
  return g;
}

template <typename mint>
vc<mint> fps_inv_dense_ntt(const vc<mint>& F) {
  vc<mint> G = {mint(1) / F[0]};
  ll N = len(F), n = 1;
  G.reserve(N);
  while (n < N) {
    vc<mint> f(2 * n), g(2 * n);
    FOR(i, min(N, 2 * n)) f[i] = F[i];
    FOR(i, n) g[i] = G[i];
    ntt(f, false), ntt(g, false);
    FOR(i, 2 * n) f[i] *= g[i];
    ntt(f, true);
    FOR(i, n) f[i] = 0;
    ntt(f, false);
    FOR(i, 2 * n) f[i] *= g[i];
    ntt(f, true);
    FOR(i, n, min(N, 2 * n)) G.eb(-f[i]);
    n *= 2;
  }
  return G;
}

template <typename mint>
vc<mint> fps_inv_dense(const vc<mint>& F) {
  if (mint::can_ntt()) return fps_inv_dense_ntt(F);
  const int N = len(F);
  vc<mint> R = {mint(1) / F[0]};
  vc<mint> p;
  int m = 1;
  while (m < N) {
    p = convolution(R, R);
    p.resize(m + m);
    vc<mint> f = {F.begin(), F.begin() + min(m + m, N)};
    p = convolution(p, f);
    R.resize(m + m);
    FOR(i, m + m) R[i] = R[i] + R[i] - p[i];
    m += m;
  }
  R.resize(N);
  return R;
}

template <typename mint>
vc<mint> fps_inv(const vc<mint>& f) {
  assert(f[0] != mint(0));
  int n = count_terms(f);
  int t = (mint::can_ntt() ? 160 : 820);
  return (n <= t ? fps_inv_sparse<mint>(f) : fps_inv_dense<mint>(f));
}
#line 5 "library/poly/fps_log.hpp"

template <typename mint>
vc<mint> fps_log_dense(const vc<mint>& f) {
  assert(f[0] == mint(1));
  ll N = len(f);
  vc<mint> df = f;
  FOR(i, N) df[i] *= mint(i);
  df.erase(df.begin());
  auto f_inv = fps_inv(f);
  auto g = convolution(df, f_inv);
  g.resize(N - 1);
  g.insert(g.begin(), 0);
  FOR(i, N) g[i] *= inv<mint>(i);
  return g;
}

template <typename mint>
vc<mint> fps_log_sparse(const vc<mint>& f) {
  int N = f.size();
  vc<pair<int, mint>> dat;
  FOR(i, 1, N) if (f[i] != mint(0)) dat.eb(i, f[i]);
  vc<mint> F(N);
  vc<mint> g(N - 1);
  for (int n = 0; n < N - 1; ++n) {
    mint rhs = mint(n + 1) * f[n + 1];
    for (auto&& [i, fi]: dat) {
      if (i > n) break;
      rhs -= fi * g[n - i];
    }
    g[n] = rhs;
    F[n + 1] = rhs * inv<mint>(n + 1);
  }
  return F;
}

template <typename mint>
vc<mint> fps_log(const vc<mint>& f) {
  assert(f[0] == mint(1));
  int n = count_terms(f);
  int t = (mint::can_ntt() ? 200 : 1200);
  return (n <= t ? fps_log_sparse<mint>(f) : fps_log_dense<mint>(f));
}
#line 3 "library/graph/count/count_labeled_connected.hpp"

// https://oeis.org/A001187
template <typename mint>
vc<mint> count_labeled_connected(int N) {
  vc<mint> F = count_labeled_undirected<mint>(N);
  FOR(i, N + 1) F[i] *= fact_inv<mint>(i);
  F = fps_log(F);
  FOR(i, N + 1) F[i] *= fact<mint>(i);
  return F;
}
#line 2 "library/poly/differentiate.hpp"

template <typename mint>
vc<mint> differentiate(const vc<mint>& f) {
  if (len(f) <= 1) return {};
  vc<mint> g(len(f) - 1);
  FOR(i, len(g)) g[i] = f[i + 1] * mint(i + 1);
  return g;
}
#line 2 "library/poly/composition.hpp"

template <typename mint>
vc<mint> composition(vc<mint>& Q, vc<mint>& P) {
  int n = len(P);
  assert(len(P) == len(Q));
  int k = 1;
  while (k * k < n) ++k;
  // compute powers of P
  vv(mint, pow1, k + 1);
  pow1[0] = {1};
  pow1[1] = P;
  FOR3(i, 2, k + 1) {
    pow1[i] = convolution(pow1[i - 1], pow1[1]);
    pow1[i].resize(n);
  }
  vv(mint, pow2, k + 1);
  pow2[0] = {1};
  pow2[1] = pow1[k];
  FOR3(i, 2, k + 1) {
    pow2[i] = convolution(pow2[i - 1], pow2[1]);
    pow2[i].resize(n);
  }
  vc<mint> ANS(n);
  FOR(i, k + 1) {
    vc<mint> f(n);
    FOR(j, k) {
      if (k * i + j < len(Q)) {
        mint coef = Q[k * i + j];
        FOR(d, len(pow1[j])) f[d] += pow1[j][d] * coef;
      }
    }
    f = convolution(f, pow2[i]);
    f.resize(n);
    FOR(d, n) ANS[d] += f[d];
  }
  return ANS;
}
#line 2 "library/poly/fps_div.hpp"

#line 5 "library/poly/fps_div.hpp"

// f/g. f の長さで出力される.
template <typename mint, bool SPARSE = false>
vc<mint> fps_div(vc<mint> f, vc<mint> g) {
  if (SPARSE || count_terms(g) < 200) return fps_div_sparse(f, g);
  int n = len(f);
  g.resize(n);
  g = fps_inv<mint>(g);
  f = convolution(f, g);
  f.resize(n);
  return f;
}

// f/g ただし g は sparse
template <typename mint>
vc<mint> fps_div_sparse(vc<mint> f, vc<mint>& g) {
  if (g[0] != mint(1)) {
    mint cf = g[0].inverse();
    for (auto&& x: f) x *= cf;
    for (auto&& x: g) x *= cf;
  }

  vc<pair<int, mint>> dat;
  FOR(i, 1, len(g)) if (g[i] != mint(0)) dat.eb(i, -g[i]);
  FOR(i, len(f)) {
    for (auto&& [j, x]: dat) {
      if (i >= j) f[i] += x * f[i - j];
    }
  }
  return f;
}
#line 4 "library/poly/compositional_inverse.hpp"

template <typename mint>
vc<mint> compositional_inverse(const vc<mint>& F) {
  const int N = len(F);
  assert(N <= 0 || F[0] == mint(0));
  assert(N <= 1 || F[1] != mint(0));
  vc<mint> DF = differentiate(F);

  vc<mint> G(2);
  G[1] = mint(1) / F[1];
  while (len(G) < N) {
    // G:= G(x)-(F(G(x))-x)/DF(G(x))
    int n = len(G);
    vc<mint> G1, G2;
    {
      vc<mint> FF(2 * n), GG(2 * n), DFF(n);
      FOR(i, min<int>(len(F), 2 * n)) FF[i] = F[i];
      FOR(i, min<int>(len(DF), n)) DFF[i] = DF[i];
      FOR(i, n) GG[i] = G[i];
      G1 = composition(FF, GG);
      G2 = composition(DFF, G);
    }
    G1 = {G1.begin() + n, G1.end()};
    G1 = fps_div(G1, G2);
    G.resize(2 * n);
    FOR(i, n) G[n + i] -= G1[i];
  }
  G.resize(N);
  return G;
}
#line 2 "library/poly/integrate.hpp"

// 不定積分：integrate(f)
// 定積分：integrate(f, L, R)
template <typename mint>
vc<mint> integrate(const vc<mint>& f) {
  vc<mint> g(len(f) + 1);
  FOR3(i, 1, len(g)) g[i] = f[i - 1] * inv<mint>(i);
  return g;
}

// 不定積分：integrate(f)
// 定積分：integrate(f, L, R)
template <typename mint>
mint integrate(const vc<mint>& f, mint L, mint R) {
  mint I = 0;
  mint pow_L = 1, pow_R = 1;
  FOR(i, len(f)) {
    pow_L *= L, pow_R *= R;
    I += inv<mint>(i + 1) * f[i] * (pow_R - pow_L);
  }
  return I;
}
#line 6 "library/poly/fps_exp.hpp"

template <typename mint>
vc<mint> fps_exp_sparse(vc<mint>& f) {
  if (len(f) == 0) return {mint(1)};
  assert(f[0] == 0);
  int N = len(f);
  // df を持たせる
  vc<pair<int, mint>> dat;
  FOR(i, 1, N) if (f[i] != mint(0)) dat.eb(i - 1, mint(i) * f[i]);
  vc<mint> F(N);
  F[0] = 1;
  FOR(n, 1, N) {
    mint rhs = 0;
    for (auto&& [k, fk]: dat) {
      if (k > n - 1) break;
      rhs += fk * F[n - 1 - k];
    }
    F[n] = rhs * inv<mint>(n);
  }
  return F;
}

template <typename mint>
vc<mint> fps_exp_dense(vc<mint>& h) {
  const int n = len(h);
  assert(n > 0 && h[0] == mint(0));
  if (mint::can_ntt()) {
    vc<mint>& f = h;
    vc<mint> b = {1, (1 < n ? f[1] : 0)};
    vc<mint> c = {1}, z1, z2 = {1, 1};
    while (len(b) < n) {
      int m = len(b);
      auto y = b;
      y.resize(2 * m);
      ntt(y, 0);
      z1 = z2;
      vc<mint> z(m);
      FOR(i, m) z[i] = y[i] * z1[i];
      ntt(z, 1);
      FOR(i, m / 2) z[i] = 0;
      ntt(z, 0);
      FOR(i, m) z[i] *= -z1[i];
      ntt(z, 1);
      c.insert(c.end(), z.begin() + m / 2, z.end());
      z2 = c;
      z2.resize(2 * m);
      ntt(z2, 0);

      vc<mint> x(f.begin(), f.begin() + m);
      FOR(i, len(x) - 1) x[i] = x[i + 1] * mint(i + 1);
      x.back() = 0;
      ntt(x, 0);
      FOR(i, m) x[i] *= y[i];
      ntt(x, 1);

      FOR(i, m - 1) x[i] -= b[i + 1] * mint(i + 1);

      x.resize(m + m);
      FOR(i, m - 1) x[m + i] = x[i], x[i] = 0;
      ntt(x, 0);
      FOR(i, m + m) x[i] *= z2[i];
      ntt(x, 1);
      FOR_R(i, len(x) - 1) x[i + 1] = x[i] * inv<mint>(i + 1);
      x[0] = 0;

      FOR3(i, m, min(n, m + m)) x[i] += f[i];
      FOR(i, m) x[i] = 0;
      ntt(x, 0);
      FOR(i, m + m) x[i] *= y[i];
      ntt(x, 1);
      b.insert(b.end(), x.begin() + m, x.end());
    }
    b.resize(n);
    return b;
  }

  const int L = len(h);
  assert(L > 0 && h[0] == mint(0));
  int LOG = 0;
  while (1 << LOG < L) ++LOG;
  h.resize(1 << LOG);
  auto dh = differentiate(h);
  vc<mint> f = {1}, g = {1};
  int m = 1;

  vc<mint> p;

  FOR(LOG) {
    p = convolution(f, g);
    p.resize(m);
    p = convolution(p, g);
    p.resize(m);
    g.resize(m);
    FOR(i, m) g[i] += g[i] - p[i];
    p = {dh.begin(), dh.begin() + m - 1};
    p = convolution(f, p);
    p.resize(m + m - 1);
    FOR(i, m + m - 1) p[i] = -p[i];
    FOR(i, m - 1) p[i] += mint(i + 1) * f[i + 1];
    p = convolution(p, g);

    p.resize(m + m - 1);
    FOR(i, m - 1) p[i] += dh[i];
    p = integrate(p);
    FOR(i, m + m) p[i] = h[i] - p[i];
    p[0] += mint(1);
    f = convolution(f, p);
    f.resize(m + m);
    m += m;
  }
  f.resize(L);
  return f;
}

template <typename mint>
vc<mint> fps_exp(vc<mint>& f) {
  int n = count_terms(f);
  int t = (mint::can_ntt() ? 320 : 3000);
  return (n <= t ? fps_exp_sparse<mint>(f) : fps_exp_dense<mint>(f));
}
#line 4 "library/graph/count/count_labeled_bridgeless.hpp"

// 橋のない連結グラフ
// https://oeis.org/A095983
// N=1: 1
template <typename mint>
vc<mint> count_labeled_bridgeless(int N) {
  vc<mint> C = count_labeled_connected<mint>(N);
  FOR(i, N + 1) C[i] *= fact_inv<mint>(i);

  vc<mint> D(N + 1);
  FOR(i, N + 1) D[i] = mint(i) * C[i];

  vc<mint> E = fps_exp(D);
  E.insert(E.begin(), mint(0));
  E.pop_back();

  // D(x)=B(E(x))
  vc<mint> IE = compositional_inverse(E);
  vc<mint> B = composition(D, IE);

  vc<mint> A(N + 1);
  FOR(i, 1, N + 1) A[i] = B[i] * inv<mint>(i);

  FOR(i, 1, N + 1) A[i] *= fact<mint>(i);
  return A;
}
#line 7 "main.cpp"

using mint = modint998;

void test() {
  vc<mint> F = count_labeled_bridgeless<mint>(10);
  vi ANS = {0,
            1,
            0,
            1,
            10,
            253,
            11968,
            1047613,
            169181040,
            51017714393,
            29180467201536};
  FOR(n, 11) assert(F[n] == mint(ANS[n]));
}

void solve() {
  int a, b;
  cin >> a >> b;
  cout << a + b << '\n';
}

signed main() {
  test();
  solve();
  return 0;
}
