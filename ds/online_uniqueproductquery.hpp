#include "alg/group_add.hpp"
#include "pds/segtree.hpp"

// sample：https://codeforces.com/contest/703/problem/D
// key = long long
// [L, R) 内の要素 (long long) を UNIQUE した上で、
// f(k),の総積をとったものを計算。 f: key -> Monoid value
// Online 化したものの、メモリ定数倍が重い
template <typename Monoid = Group_Add<int>, int NODES = 1000000>
struct OnlineUniqueProductQuery {
  using X = typename Monoid::value_type;
  int N;
  vc<ll> key;
  vc<pair<int, int>> query;
  vc<int> times;
  Persistent_SegTree<Monoid, NODES> seg;

  template <typename F>
  OnlineUniqueProductQuery(vc<ll>& key, F f) : N(len(key)), key(key), seg(N) {
    times.eb(seg.time());
    unordered_map<ll, int> pos;
    pos.reserve(N);
    FOR(i, N) {
      ll x = key[i];
      int t = seg.time();
      if (pos.count(x)) { t = seg.set(t, pos[x], Monoid::unit); }
      pos[x] = i;
      t = seg.set(t, i, f(key[i]));
      times.eb(t);
    }
  }
  
  X prod(int L, int R) {
    int t = times[R];
    return seg.prod(t, L, R);
  }
};
