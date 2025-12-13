#pragma once
#include <cstddef>

template <typename T>
class CorruptionStrategy {
public:
    virtual ~CorruptionStrategy() = default;
    virtual void corrupt(T& value) = 0;
};
