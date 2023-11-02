#include "my_template.hpp"
#include "other/io.hpp"

#include "ds/my_bitset.hpp"
#include "flow/bipartite_dense.hpp"

void solve() {
  INT(H, W);
  VEC(string, G, H);

  vv(int, IDX, H, W);
  int a = 0, b = 0;
  FOR(x, H) FOR(y, W) {
    if ((x + y) % 2 == 0) IDX[x][y] = a++;
    if ((x + y) % 2 == 1) IDX[x][y] = b++;
  }

  auto isin = [&](int x, int y) -> bool {
    return (0 <= x && x < H && 0 <= y && y < W);
  };
  int dx[] = {1, 0, -1, 0, 1, 1, -1, -1};
  int dy[] = {0, 1, 0, -1, 1, -1, 1, -1};

  vc<My_Bitset> adj(a, My_Bitset(b));
  FOR(x, H) FOR(y, W) {
    if ((x + y) & 1) continue;
    FOR(d, 2) {
      int nx = x + dx[d], ny = y + dy[d];
      if (!isin(nx, ny)) continue;
      if (G[x][y] == G[nx][ny]) continue;
      if (G[x][y] == '.') continue;
      if (G[nx][ny] == '.') continue;
      adj[IDX[x][y]][IDX[nx][ny]] = 1;
    }
  }

  BipartiteMatching_Dense<My_Bitset> BM(adj, a, b);
  auto match = BM.matching();
  int n = len(match);
  int x = 0;
  FOR(i, H) FOR(j, W) x += (G[i][j] != '.');
  print(100 * n + (x - 2 * n));
}

signed main() {
  solve();
  return 0;
}