#pragma once

#include <random>

namespace Random {
    using ll = long long;
    inline std::random_device r;
    inline std::default_random_engine e1(r());

    inline ll rnd(ll a, ll b) {
        std::uniform_int_distribution<ll> uniform_dist(a, b);
        return uniform_dist(e1);
    }
}