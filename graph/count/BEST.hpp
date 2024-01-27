#include "graph/base.hpp"
#include "ds/unionfind/unionfind.hpp"
#include "linalg/blackbox/det.hpp"

/*
ひとつ選んだ辺から始めて全ての点・辺を通る closed walk を数える.
多重辺は vc<int>(eid) で渡す，なければすべて 1. e.cost は参照しない.
辺はラベル付きで考える. 多重辺を同一視する場合などは後で階乗で割ること.
O(N^2+NM) （ + 最後に重複度の階乗をかける）．
*/
template <typename mint, typename GT>
mint BEST_theorem(GT& G, vc<int> edge_multiplicity = {}) {
  static_assert(GT::is_directed);
  int N = G.N, M = G.M;
  if (M == 0) return 0;
  if (edge_multiplicity.empty()) edge_multiplicity.assign(M, 1);

  // やらなくても 0 になるはずだが一応
  UnionFind uf(N);
  vc<int> indeg(N), outdeg(N);
  FOR(i, M) {
    int a = G.edges[i].frm, b = G.edges[i].to, x = edge_multiplicity[i];
    if (!x) continue;
    outdeg[a] += x, indeg[b] += x;
    uf.merge(a, b);
  }
  if (uf.n_comp != 1) return 0;
  FOR(v, N) if (indeg[v] != outdeg[v]) return 0;

  vc<tuple<int, int, mint>> mat;
  FOR(i, M) {
    int a = G.edges[i].frm, b = G.edges[i].to, x = edge_multiplicity[i];
    if (a < N - 1 && b < N - 1) mat.eb(a, b, -x);
    if (a < N - 1) mat.eb(a, a, x);
  }
  auto apply = [&](vc<mint> A) -> vc<mint> {
    vc<mint> B(N - 1);
    for (auto& [a, b, c]: mat) B[b] += A[a] * c;
  };
  mint d = blackbox_det(N - 1, apply);
  for (auto& x: outdeg) { d *= fact<mint>(x - 1); }
  return d;
}
