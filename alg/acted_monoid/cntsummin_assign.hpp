#include "alg/monoid/cntsummin.hpp"
#include "alg/monoid/assign.hpp"

template <typename E, ll none_val>
struct ActedMonoid_CntSumMin_Assign {
  static constexpr ll INF = 1LL << 60;
  using Monoid_X = Monoid_CntSumMin<E>;
  using Monoid_A = Monoid_Assign<ll, none_val>;
  using X = typename Monoid_X::value_type;
  using A = typename Monoid_A::value_type;
  static constexpr X act(const X& x, const A& a) {
    if (a == MA::unit()) return x;
    auto [xc, xs, xm] = x;
    return {xc, xc * a, a};
  }
};
