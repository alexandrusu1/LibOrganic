#pragma once
#include "CorruptionStrategy.h"
#include <random>
#include <cstring>
#include <type_traits>

template <typename T>
class BitFlipStrategy : public CorruptionStrategy<T> {
    std::mt19937 rng{std::random_device{}()};

public:
    void corrupt(T& value) override {
        if constexpr (std::is_trivially_copyable_v<T>) {
            unsigned char* raw = reinterpret_cast<unsigned char*>(&value);
            std::uniform_int_distribution<size_t> byteDist(0, sizeof(T) - 1);
            std::uniform_int_distribution<int> bitDist(0, 7);
            size_t byteIndex = byteDist(rng);
            int bitIndex = bitDist(rng);
            raw[byteIndex] ^= (1 << bitIndex);
        }
    }
};
