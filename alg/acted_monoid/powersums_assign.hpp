#pragma once

#include "alg/monoid/assign.hpp"
#include "alg/monoid/add_array.hpp"

template <typename mint, int K>
struct ActedMonoid_Power_Sums_Assign {
  using Monoid_X = Monoid_Add_Array<mint, K>;
  using Monoid_A = Monoid_Assign<int, -1>;
  using X = typename Monoid_X::value_type;
  using A = typename Monoid_A::value_type;
  static X act(const X &x, const A &b) {
    if (b == -1) return x;
    X y;
    mint pow = 1;
    FOR(i, K) { y[i] = x[0] * pow, pow *= mint(b); }
    return y;
  }
};
