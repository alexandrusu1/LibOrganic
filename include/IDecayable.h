#pragma once
#include <chrono>
#include <memory>

class IDecayable {
public:
    virtual ~IDecayable() = default;
    virtual void decay() = 0;
    virtual bool isExpired(std::chrono::steady_clock::time_point now) const = 0;
};

using IDecayablePtr = std::shared_ptr<IDecayable>;