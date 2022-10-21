#define PROBLEM "https://judge.yosupo.jp/problem/vertex_add_path_sum"
#include "my_template.hpp"
#include "other/io.hpp"

#include "graph/ds/treemonoid.hpp"
#include "alg/group/add.hpp"

void solve() {
  LL(N, Q);
  VEC(ll, A, N);
  Graph G(N);
  G.read_tree(0, 0);

  TREE tree(G);
  const bool is_edge = false;
  using Mono = Group_Add<ll>;
  TreeMonoid<decltype(tree), Mono, is_edge> TM(tree, A);

  FOR(_, Q) {
    LL(t);
    if (t == 0) {
      LL(v, x);
      A[v] += x;
      TM.set(v, A[v]);
    } else {
      LL(u, v);
      print(TM.prod_path(u, v));
    }
  }
}

signed main() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);
  cout << setprecision(15);

  solve();

  return 0;
}
