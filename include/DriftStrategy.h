#pragma once
#include "CorruptionStrategy.h"
#include <random>
#include <type_traits>
#include <cmath>

template <typename T>
class DriftStrategy : public CorruptionStrategy<T> {
    std::mt19937 rng{std::random_device{}()};
    double driftFactor;

public:
    explicit DriftStrategy(double factor = 0.1) : driftFactor(factor) {}

    void corrupt(T& value) override {
        if constexpr (std::is_integral_v<T>) {
            std::uniform_int_distribution<int> dir(-1, 1);
            T delta = static_cast<T>(std::max<T>(1, static_cast<T>(std::abs(value) * driftFactor)));
            value += static_cast<T>(dir(rng)) * delta;
        } else if constexpr (std::is_floating_point_v<T>) {
            std::uniform_real_distribution<double> dir(-1.0, 1.0);
            value += static_cast<T>(dir(rng) * std::abs(value) * driftFactor);
        }
    }
};
