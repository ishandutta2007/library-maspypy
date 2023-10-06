#pragma once

template <typename E, int K>
struct Monoid_Add_Array {
  using value_type = array<E, K>;
  using X = value_type;
  static X op(X x, X y) {
    FOR(i, K) x[i] += y[i];
    return x;
  }
  static constexpr X unit() { return X{}; }
  static constexpr bool commute = 1;
};
