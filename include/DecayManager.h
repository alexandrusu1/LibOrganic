#pragma once
#include <vector>
#include <mutex>
#include <thread>
#include <atomic>
#include <algorithm>
#include <iostream>
#include <memory>
#include <chrono>
#include "IDecayable.h"

class DecayManager {
public:
    DecayManager(const DecayManager&) = delete;
    void operator=(const DecayManager&) = delete;
    ~DecayManager();
    static DecayManager& getInstance();

    void registerObject(IDecayablePtr obj);
    void unregisterObject(const IDecayable* rawPtr);

private:
    DecayManager();
    void entropyLoop(std::stop_token stopToken);

    std::vector<std::weak_ptr<IDecayable>> managedObjects;
    std::mutex mtx;
    std::jthread decayThread;
    const std::chrono::milliseconds checkInterval{1000};
};