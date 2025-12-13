#pragma once
#include "CorruptionStrategy.h"
#include <type_traits>

template <typename T>
class NullifyStrategy : public CorruptionStrategy<T> {
public:
    void corrupt(T& value) override {
        if constexpr (std::is_default_constructible_v<T>) {
            value = T{};
        }
    }
};
