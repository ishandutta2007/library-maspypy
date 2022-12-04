template <class T, typename XY>
struct KDTree {
  // 小数も考慮すると、閉で持つ設計方針になる。ただし、クエリはいつもの半開を使う
  vc<tuple<XY, XY, XY, XY>> closed_range;
  // 同じ座標の点も集約しないようにして、座標ごとに unique なデータを使う
  vc<T> dat;
  vc<int> size;
  int n;

  KDTree(vc<XY> xs, vc<XY> ys, vc<T> vs) : n(len(xs)) {
    assert(n > 0);
    int log = 0;
    while ((1 << log) < n) ++log;
    dat.resize(1 << (log + 1));
    size.resize(1 << (log + 1));
    closed_range.resize(1 << (log + 1));
    build(1, xs, ys, vs);
  }

  // [xl, xr) x [yl, yr)
  vc<T> collect_rect(XY xl, XY xr, XY yl, XY yr, int max_size = -1) {
    assert(xl <= xr && yl <= yr);
    if (max_size == -1) max_size = n;
    vc<T> res;
    collect_rect_rec(1, xl, xr, yl, yr, res, max_size);
    return res;
  }

  // r^2 を渡すことに気を付ける
  vc<T> collect_circle(XY x, XY y, XY r_squared, int max_size = -1) {
    if (max_size == -1) max_size = n;
    vc<T> res;
    collect_circle_rec(1, x, y, r_squared, res, max_size);
    return res;
  }

private:
  void build(int idx, vc<XY> xs, vc<XY> ys, vc<T> vs, bool divx = true) {
    int n = len(xs);
    size[idx] = n;
    auto& [xmin, xmax, ymin, ymax] = closed_range[idx];
    xmin = ymin = numeric_limits<XY>::max();
    xmax = ymax = numeric_limits<XY>::lowest();

    FOR(i, n) {
      auto x = xs[i], y = ys[i];
      chmin(xmin, x), chmax(xmax, x), chmin(ymin, y), chmax(ymax, y);
    }
    if (n == 1) {
      dat[idx] = vs[0];
      return;
    }

    int m = n / 2;
    vc<int> I(n);
    iota(all(I), 0);
    if (divx) {
      nth_element(I.begin(), I.begin() + m, I.end(),
                  [xs](int i, int j) { return xs[i] < xs[j]; });
    } else {
      nth_element(I.begin(), I.begin() + m, I.end(),
                  [ys](int i, int j) { return ys[i] < ys[j]; });
    }
    xs = rearrange(xs, I), ys = rearrange(ys, I), vs = rearrange(vs, I);
    build(2 * idx + 0, {xs.begin(), xs.begin() + m},
          {ys.begin(), ys.begin() + m}, {vs.begin(), vs.begin() + m}, !divx);
    build(2 * idx + 1, {xs.begin() + m, xs.end()}, {ys.begin() + m, ys.end()},
          {vs.begin() + m, vs.end()}, !divx);
  }

  void collect_rect_rec(int i, XY x1, XY x2, XY y1, XY y2, vc<T>& res, int ms) {
    if (len(res) == ms) return;
    auto& [xmin, xmax, ymin, ymax] = closed_range[i];
    if (x2 <= xmin || xmax < x1) return;
    if (y2 <= ymin || ymax < y1) return;
    if (size[i] == 1) {
      res.eb(dat[i]);
      return;
    }
    collect_rect_rec(2 * i + 0, x1, x2, y1, y2, res, ms);
    collect_rect_rec(2 * i + 1, x1, x2, y1, y2, res, ms);
  }
};
