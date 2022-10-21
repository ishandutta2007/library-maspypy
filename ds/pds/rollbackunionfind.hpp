#include "ds/pds/rollbackarray.hpp"

struct RollbackUnionFind {
  RollbackArray<int> dat; // parent or size

  RollbackUnionFind(int n) : dat(vc<int>(n, -1)) {}

  int operator[](int v) {
    while (dat.get(v) >= 0) v = dat.get(v);
    return v;
  }

  int size(int v) { return -dat.get((*this)[v]); }
  int time() { return dat.time(); }
  void rollback(int t) { dat.rollback(t); }

  bool merge(int a, int b) {
    a = (*this)[a], b = (*this)[b];
    if (a == b) return false;
    if (dat.get(a) > dat.get(b)) swap(a, b);
    dat.set(a, dat.get(a) + dat.get(b));
    dat.set(b, a);
    return true;
  }
};
