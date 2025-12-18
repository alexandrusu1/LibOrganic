#pragma once
#include <chrono>
#include <iostream>
#include <memory>
#include <atomic>
#include <functional>
#include <type_traits>
#include "IDecayable.h"
#include "DecayManager.h"
#include "CorruptionStrategy.h"
#include "DriftStrategy.h"

template <typename T>
class Organic : public IDecayable, public std::enable_shared_from_this<Organic<T>> {
    T value;
    std::atomic<long long> lastAccessMs{};
    std::chrono::milliseconds timeToLive;
    std::unique_ptr<CorruptionStrategy<T>> strategy;
    std::function<void(const T&, const T&)> decayCallback;
    std::atomic<bool> paused{false};

    Organic(T initialValue, int ttlMs)
        : value(initialValue)
        , timeToLive(ttlMs)
        , strategy(std::make_unique<DriftStrategy<T>>()) {
        touch();
    }

public:
    Organic(const Organic&) = delete;
    Organic& operator=(const Organic&) = delete;
    Organic(Organic&&) = default;
    Organic& operator=(Organic&&) = default;

    static std::shared_ptr<Organic<T>> create(T initialValue, int ttlMs = 3000) {
        auto ptr = std::shared_ptr<Organic<T>>(new Organic<T>(initialValue, ttlMs));
        DecayManager::getInstance().registerObject(std::static_pointer_cast<IDecayable>(ptr));
        return ptr;
    }

    ~Organic() override {
        DecayManager::getInstance().unregisterObject(this);
    }

    void setStrategy(std::unique_ptr<CorruptionStrategy<T>> newStrategy) {
        strategy = std::move(newStrategy);
    }

    void onDecay(std::function<void(const T&, const T&)> callback) {
        decayCallback = std::move(callback);
    }

    void pause() noexcept { paused.store(true, std::memory_order_relaxed); }
    void resume() noexcept { paused.store(false, std::memory_order_relaxed); touch(); }
    bool isPaused() const noexcept { return paused.load(std::memory_order_relaxed); }

    void touch() noexcept {
        auto now = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::steady_clock::now().time_since_epoch()).count();
        lastAccessMs.store(now, std::memory_order_relaxed);
    }

    T& get() noexcept {
        touch();
        return value;
    }

    const T& peek() const noexcept {
        return value;
    }

    bool isAlive() const noexcept {
        return !isExpired(std::chrono::steady_clock::now());
    }

    bool isExpired(std::chrono::steady_clock::time_point now) const override {
        if (paused.load(std::memory_order_relaxed)) return false;
        auto nowMs = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
        auto last = lastAccessMs.load(std::memory_order_relaxed);
        return (nowMs - last) > timeToLive.count();
    }

    void decay() override {
        if (paused.load(std::memory_order_relaxed)) return;
        if (strategy) {
            T oldValue = value;
            strategy->corrupt(value);
            if (decayCallback) decayCallback(oldValue, value);
        }
    }
};