#pragma once
#include <vector>
#include <mutex>
#include <thread>
#include <atomic>
#include <algorithm>
#include <iostream>
#include "IDecayable.h"

class DecayManager {
private:
    std::vector<IDecayable*> managedObjects; 
    std::mutex mtx; 
    std::thread decayThread;
    std::atomic<bool> running;
    

    const int checkIntervalMs = 1000; 


    DecayManager();

    void entropyLoop();

public:
    DecayManager(const DecayManager&) = delete;
    void operator=(const DecayManager&) = delete;

    ~DecayManager();

    static DecayManager& getInstance();

    void registerObject(IDecayable* obj);
    void unregisterObject(IDecayable* obj);
};