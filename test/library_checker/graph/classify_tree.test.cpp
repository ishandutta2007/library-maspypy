#define PROBLEM \
  "https://judge.yosupo.jp/problem/rooted_tree_isomorphism_classification"

#include "my_template.hpp"
#include "other/io.hpp"
#include "graph/classify_subtree.hpp"

void solve() {
  LL(N);
  Graph<int, 0> G(N);
  G.read_parent(0);
  TREE<decltype(G)> tree(G);

  auto ANS = classify_subtree(tree);
  vi key = ANS;
  UNIQUE(key);
  for (auto&& x: ANS) x = LB(key, x);
  print(MAX(ANS) + 1);
  print(ANS);
}

signed main() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);
  cout << setprecision(15);

  ll T = 1;
  // LL(T);
  FOR(T) solve();

  return 0;
}
