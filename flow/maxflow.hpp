
// 頂点数は渡さなくてよい
template <typename Cap>
struct MaxFlowGraph {
  struct Edge {
    int to, rev;
    Cap cap;
  };

  const Cap INF;
  int N;
  vvc<Edge> G;
  vc<int> prog, level;
  Cap flow_ans;
  bool calculated;

  MaxFlowGraph(Cap INF) : INF(INF), N(0), calculated(0) {}

  void add(int frm, int to, Cap cap) {
    chmax(N, frm + 1);
    chmax(N, to + 1);
    if (len(G) < N) G.resize(N);
    G[frm].eb(Edge{to, (int)G[to].size(), cap});
    G[to].eb(Edge{frm, (int)G[frm].size() - 1, 0});
  }

  Cap flow(int source, int sink) {
    if (calculated) return flow_ans;
    calculated = true;
    chmax(N, source + 1);
    chmax(N, sink + 1);
    G.resize(N);
    flow_ans = 0;
    while (set_level(source, sink)) {
      fill(all(prog), 0);
      prog.assign(N, 0);
      while (1) {
        Cap x = flow_dfs(source, sink, INF);
        if (x == 0) break;
        flow_ans += x;
        chmin(flow_ans, INF);
        if (flow_ans == INF) return flow_ans;
      }
    }
    return flow_ans;
  }

  // 最小カットの値および、カットを表す 01 列を返す
  pair<Cap, vc<int>> cut(int source, int sink) {
    Cap f = flow(source, sink);
    vc<int> res(N);
    FOR(v, N) res[v] = (level[v] >= 0 ? 0 : 1);
    return {f, res};
  }

private:
  bool set_level(int source, int sink) {
    level.assign(N, -1);
    level[source] = 0;
    queue<int> que;
    que.push(source);
    while (!que.empty()) {
      int v = que.front();
      que.pop();
      for (auto&& e: G[v]) {
        if (e.cap > 0 && level[e.to] == -1) {
          level[e.to] = level[v] + 1;
          if (e.to == sink) return true;
          que.push(e.to);
        }
      }
    }
    return false;
  }

  Cap flow_dfs(int v, int sink, Cap lim) {
    if (v == sink) return lim;
    Cap res = 0;
    for (int& i = prog[v]; i < (int)G[v].size(); ++i) {
      auto& e = G[v][i];
      if (e.cap > 0 && level[e.to] == level[v] + 1) {
        Cap a = flow_dfs(e.to, sink, min(lim, e.cap));
        if (a > 0) {
          e.cap -= a;
          G[e.to][e.rev].cap += a;
          res += a;
          lim -= a;
          if (lim == 0) break;
        }
      }
    }
    return res;
  }
};
