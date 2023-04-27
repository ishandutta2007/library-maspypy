#include "graph/strongly_connected_component.hpp"

struct TwoSat {
  Graph<bool, 1> G;
  vc<int> values;
  vc<pair<int, int>> edges;

  TwoSat(ll n) : G(n + n), values(n, -1) {}
  void add(int a, int b) {
    a = (a >= 0 ? 2 * a + 1 : 2 * (~a));
    b = (b >= 0 ? 2 * b + 1 : 2 * (~b));
    edges.eb(a ^ 1, b);
    edges.eb(b ^ 1, a);
  }
  void set(int a) {
    if (a >= 0)
      values[a] = 1;
    else
      values[~a] = 0;
    a = (a >= 0 ? 2 * a + 1 : 2 * (~a));
    edges.eb(a ^ 1, a);
  }
  void implies(int a, int b) { add(~a, b); }

  pair<bool, vc<int>> calc() {
    UNIQUE(edges);
    for (auto&& [a, b]: edges) G.add(a, b);
    G.build();
    ll n = len(values);
    auto [C, comp] = strongly_connected_component(G);
    FOR(i, n) {
      if (comp[2 * i] == comp[2 * i + 1]) return {false, values};
      values[i] = comp[2 * i] < comp[2 * i + 1];
    }
    return {true, values};
  }
};