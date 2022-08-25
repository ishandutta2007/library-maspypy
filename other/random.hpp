#pragma once

ll RNG(ll a, ll b) {
  static mt19937 mt(chrono::steady_clock::now().time_since_epoch().count());
  uniform_int_distribution<ll> dist(a, b - 1);
  return dist(mt);
}

ll RNG(ll a) {
  static mt19937 mt(chrono::steady_clock::now().time_since_epoch().count());
  uniform_int_distribution<ll> dist(0, a - 1);
  return dist(mt);
}
