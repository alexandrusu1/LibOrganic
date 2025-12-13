#pragma once
#include <chrono>
#include <iostream>
#include "IDecayable.h"
#include "DecayManager.h"


template <typename T>
class Organic : public IDecayable {
private:
    T value;
    std::chrono::steady_clock::time_point lastAccess;
    std::chrono::milliseconds timeToLive;

public:
   
    Organic(T initialValue, int ttlMs = 3000) 
        : value(initialValue), timeToLive(ttlMs) {
        touch(); 
        DecayManager::getInstance().registerObject(this);
    }

    ~Organic() {
        DecayManager::getInstance().unregisterObject(this);
    }

    void touch() {
        lastAccess = std::chrono::steady_clock::now();
    }

    
    T* operator->() {
        touch();
        return &value;
    }

    T& operator*() {
        touch();
        return value;
    }


    bool isExpired(std::chrono::steady_clock::time_point now) const override {
        return std::chrono::duration_cast<std::chrono::milliseconds>(now - lastAccess) > timeToLive;
    }

    void decay() override {
        if constexpr (std::is_arithmetic<T>::value) {
            value = value * 0.9; 
            std::cout << "[Organic] Degradation: " << value << "\n";
        } else {
            std::cout << "⚠️ [Organic] Degradation on complex object(not implemented yet).\n";
        }
    }
};