
template <class Monoid, bool DEQUE>
struct SWAG {
  using X = typename Monoid::value_type;
  using value_type = X;
  int sz;
  vc<X> dat_l, dat_r;
  vc<X> cum_l, cum_r;

  SWAG() : sz(0), cum_l({Monoid::unit()}), cum_r({Monoid::unit()}) {}

  int size() { return sz; }

  void push_back(X x) {
    ++sz;
    dat_r.eb(x);
    cum_r.eb(Monoid::op(cum_r.back(), x));
  }

  void push_front(X x) {
    ++sz;
    dat_l.eb(x);
    cum_l.eb(Monoid::op(x, cum_l.back()));
  }

  void push(X x) { push_back(x); }

  void clear() {
    sz = 0;
    dat_l.clear(), dat_r.clear();
    cum_l = {Monoid::unit()}, cum_r = {Monoid::unit()};
  }

  void pop_front() {
    if (sz == 1) return clear();
    if (dat_l.empty()) rebuild();
    --sz;
    dat_l.pop_back();
    cum_l.pop_back();
  }

  void pop_back() {
    if (sz == 1) return clear();
    if (dat_r.empty()) rebuild();
    --sz;
    dat_r.pop_back();
    cum_r.pop_back();
  }

  void pop() { pop_front(); }

  void rebuild() {
    vc<X> X;
    FOR_R(i, len(dat_l)) X.eb(dat_l[i]);
    X.insert(X.end(), all(dat_r));
    clear();
    int m = (DEQUE ? len(X) / 2 : len(X));
    FOR_R(i, m) push_front(X[i]);
    FOR(i, m, len(X)) push_back(X[i]);
    assert(sz == len(X));
  }

  X lprod() { return cum_l.back(); }
  X rprod() { return cum_r.back(); }
  X prod() { return Monoid::op(cum_l.back(), cum_r.back()); }
  X prod_all() { return prod(); }

  void debug() {
    print("swag");
    print("dat_l", dat_l);
    print("dat_r", dat_r);
    print("cum_l", cum_l);
    print("cum_r", cum_r);
  }
};
