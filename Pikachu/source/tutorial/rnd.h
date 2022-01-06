#pragma once

#include <random>

namespace Random {
    using ll = long long;
    static std::random_device device;
    static std::default_random_engine engine(device());

    static ll rnd(ll min, ll max) {
        const std::uniform_int_distribution<ll> uniform_dist(min, max);

        return uniform_dist(engine);
    }
}