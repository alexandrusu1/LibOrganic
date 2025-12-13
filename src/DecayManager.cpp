#include "../include/DecayManager.h"

DecayManager::DecayManager() : decayThread([this](std::stop_token st){ entropyLoop(st); }) {}

DecayManager::~DecayManager() = default;

DecayManager& DecayManager::getInstance() {
    static DecayManager instance;
    return instance;
}

void DecayManager::registerObject(IDecayablePtr obj) {
    std::lock_guard<std::mutex> lock(mtx);
    managedObjects.push_back(obj);
}

void DecayManager::unregisterObject(const IDecayable* rawPtr) {
    std::lock_guard<std::mutex> lock(mtx);
    managedObjects.erase(std::remove_if(managedObjects.begin(), managedObjects.end(),
        [rawPtr](const std::weak_ptr<IDecayable>& w){
            auto s = w.lock();
            return !s || s.get() == rawPtr;
        }), managedObjects.end());
}

void DecayManager::entropyLoop(std::stop_token stopToken) {
    while (!stopToken.stop_requested()) {
        std::this_thread::sleep_for(checkInterval);
        auto now = std::chrono::steady_clock::now();

        std::lock_guard<std::mutex> lock(mtx);
        for (auto it = managedObjects.begin(); it != managedObjects.end(); ) {
            if (auto obj = it->lock()) {
                if (obj->isExpired(now)) obj->decay();
                ++it;
            } else {
                it = managedObjects.erase(it);
            }
        }
    }
}