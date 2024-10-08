/*
partition は、「減少列」として辞書式の降順に列挙する。
N = 50（204226）：12 ms
N = 60（966467）：60 ms
N = 70（4087968）：270 ms
N = 80（15796476）：1100 ms
N = 90（56634173）：4800 ms
N = 100 (190569292) : 15600 ms
*/
template <typename F>
void enumerate_partition(int N, F query, int LIM_len = -1, int LIM_val = -1) {
  assert(N >= 0);
  auto dfs = [&](auto self, vc<int>& p, int sum) -> void {
    if (sum == N) {
      query(p);
      return;
    }
    if (LIM_len != -1 && len(p) == LIM_len) return;
    int nxt = (len(p) == 0 ? N : p.back());
    if (LIM_val != -1) chmin(nxt, LIM_val);
    chmin(nxt, N - sum);
    p.eb(0);
    FOR3_R(x, 1, nxt + 1) {
      p.back() = x;
      self(self, p, sum + x);
    }
    p.pop_back();
  };
  vc<int> p;
  dfs(dfs, p, 0);
}
