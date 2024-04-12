#include "graph/base.hpp"

// ID[v]：頂点の新しい番号
// calc_range(v, dep)：v の部分木で、深さ dep のものたちの範囲
// 深さは絶対的なものであることに注意せよ
template <typename Graph>
struct BFS_Numbering {
  Graph& G;
  int root;
  vector<int> V;
  vector<int> ID;
  vector<int> depth;
  vector<int> parent;
  vector<int> LID, RID;
  vector<int> LID_seq;
  vector<int> dep_ids;
  int cnt;

  BFS_Numbering(Graph& G, int root = 0) : G(G), root(root), cnt(0) { build(); }

  void bfs() {
    deque<int> que = {root};
    while (!que.empty()) {
      int v = POP(que);
      ID[v] = V.size();
      V.eb(v);
      for (auto&& [frm, to, cost, id]: G[v]) {
        if (to == parent[v]) continue;
        que.eb(to), parent[to] = v, depth[to] = depth[v] + 1;
      }
    }
  }

  void dfs(int v) {
    LID[v] = cnt++;
    for (auto&& [frm, to, cost, id]: G[v]) {
      if (to == parent[v]) continue;
      dfs(to);
    }
    RID[v] = cnt;
  }

  void build() {
    int N = G.N;
    V.reserve(N);
    parent.assign(N, -1);
    ID.assign(N, 0), LID.assign(N, 0), RID.assign(N, 0), depth.assign(N, 0);
    bfs();
    dfs(root);
    int D = MAX(depth);
    dep_ids.resize(D + 2);
    FOR(v, N) dep_ids[depth[v] + 1]++;
    FOR(d, D + 1) dep_ids[d + 1] += dep_ids[d];
    LID_seq.reserve(N);
    FOR(i, N) LID_seq.eb(LID[V[i]]);
  }

  // dep は絶対的な深さ
  pair<int, int> calc_range(int v, int dep) {
    assert(dep >= depth[v]);
    if (dep >= len(dep_ids) - 1) return {0, 0};
    int l = LID[v], r = RID[v];
    int L = dep_ids[dep], R = dep_ids[dep + 1];
    int a = bs(L - 1, R, l);
    int b = bs(L - 1, R, r);
    return {a, b};
  }

  // dist(p,v)<=r
  vc<pair<int, int>> disk_range(int v, int r) {
    if (r < 0) return {};
    vc<pair<int, int>> res;
    int d = depth[v];
    FOR(k, r + 1) {
      if (v == -1) break;
      int hi = d + r - k;
      int lo = hi - 1;
      chmax(lo, d);
      if (parent[v] == -1) lo = 0;
      FOR(i, lo, hi + 1) { res.eb(calc_range(v, i)); }
      v = parent[v], d = d - 1;
    }
    return res;
  }

private:
  int bs(int L, int R, int x) {
    while (L + 1 < R) {
      int M = (L + R) / 2;
      if (LID_seq[M] >= x)
        R = M;
      else
        L = M;
    }
    return R;
  }
};
