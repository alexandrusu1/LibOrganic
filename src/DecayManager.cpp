#include "../include/DecayManager.h"
#include <chrono>

DecayManager::DecayManager() : running(true) {
    decayThread = std::thread(&DecayManager::entropyLoop, this);
}

DecayManager::~DecayManager() {
    running = false;
    if (decayThread.joinable()) {
        decayThread.join();
    }
}

DecayManager& DecayManager::getInstance() {
    static DecayManager instance;
    return instance;
}

void DecayManager::registerObject(IDecayable* obj) {
    std::lock_guard<std::mutex> lock(mtx);
    managedObjects.push_back(obj);

}

void DecayManager::unregisterObject(IDecayable* obj) {
    std::lock_guard<std::mutex> lock(mtx);
    auto it = std::remove(managedObjects.begin(), managedObjects.end(), obj);
    managedObjects.erase(it, managedObjects.end());

}

void DecayManager::entropyLoop() {
    while (running) {
        std::this_thread::sleep_for(std::chrono::milliseconds(checkIntervalMs));
        
        auto now = std::chrono::steady_clock::now();

        std::lock_guard<std::mutex> lock(mtx);
        
        for (auto* obj : managedObjects) {
            if (obj->isExpired(now)) {
                obj->decay();
            }
        }
    }
}