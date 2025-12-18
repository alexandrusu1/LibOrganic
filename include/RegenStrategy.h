#pragma once
#include "CorruptionStrategy.h"
#include <type_traits>

template <typename T>
class RegenStrategy : public CorruptionStrategy<T> {
    T maxValue;
    double regenRate;

public:
    RegenStrategy(T max, double rate = 0.1) : maxValue(max), regenRate(rate) {}

    void corrupt(T& value) override {
        if constexpr (std::is_arithmetic_v<T>) {
            T increase = static_cast<T>(value * regenRate);
            if (increase == 0) increase = 1;
            value = std::min(value + increase, maxValue);
        }
    }
};
