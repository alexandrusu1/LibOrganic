#include <iostream>
#include <thread>
#include <string>
#include "../include/Organic.h"
#include "../include/BitFlipStrategy.h"
#include "../include/DriftStrategy.h"
#include "../include/NullifyStrategy.h"
#include "../include/RegenStrategy.h"

int main() {
    std::cout << "=== LibOrganic Demo ===\n\n";

    {
        std::cout << "--- Callback Demo ---\n";
        auto health = Organic<int>::create(100, 1500);
        health->onDecay([](const int& old, const int& now) {
            std::cout << "Health changed: " << old << " -> " << now << "\n";
        });
        std::cout << "Waiting for decay...\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(3500));
        std::cout << "Final: " << health->peek() << "\n\n";
    }

    {
        std::cout << "--- Pause/Resume Demo ---\n";
        auto mana = Organic<int>::create(50, 1500);
        mana->onDecay([](const int& old, const int& now) {
            std::cout << "Mana: " << old << " -> " << now << "\n";
        });
        std::cout << "Pausing decay...\n";
        mana->pause();
        std::this_thread::sleep_for(std::chrono::milliseconds(3000));
        std::cout << "After 3s paused: " << mana->peek() << " (no change)\n";
        std::cout << "Resuming...\n";
        mana->resume();
        std::this_thread::sleep_for(std::chrono::milliseconds(3500));
        std::cout << "After resume + wait: " << mana->peek() << "\n\n";
    }

    {
        std::cout << "--- Regen Strategy Demo ---\n";
        auto stamina = Organic<int>::create(30, 1500);
        stamina->setStrategy(std::make_unique<RegenStrategy<int>>(100, 0.2));
        stamina->onDecay([](const int& old, const int& now) {
            std::cout << "Stamina regen: " << old << " -> " << now << "\n";
        });
        std::cout << "Starting at 30, max 100...\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(5000));
        std::cout << "Final stamina: " << stamina->peek() << "\n\n";
    }

    std::cout << "=== Done ===\n";
    return 0;
}