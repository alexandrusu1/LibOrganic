#include <iostream>
#include <thread>
#include <chrono>
#include "../include/Organic.h"
#include "../include/DriftStrategy.h"

using namespace std::chrono_literals;

int main() {
    std::cout << "=== Game Health System Demo ===\n\n";
    std::cout << "Simulating a game where health decays if player is idle.\n\n";

    auto playerHealth = Organic<int>::create(100, 1000);
    playerHealth->setStrategy(std::make_unique<DriftStrategy<int>>(0.05));

    std::cout << "Player spawned with " << playerHealth->get() << " HP\n";
    std::cout << "Health will decay if player doesn't perform actions.\n\n";

    for (int round = 1; round <= 5; ++round) {
        std::cout << "--- Round " << round << " ---\n";
        
        if (round % 2 == 1) {
            std::cout << "Player attacks! (health accessed)\n";
            std::cout << "Current HP: " << playerHealth->get() << "\n";
        } else {
            std::cout << "Player is AFK...\n";
            std::this_thread::sleep_for(2500ms);
            std::cout << "Current HP: " << playerHealth->peek() << " (decayed!)\n";
        }
        std::cout << "\n";
    }

    std::cout << "=== Game Over ===\n";
    std::cout << "Final HP: " << playerHealth->peek() << "\n";

    return 0;
}
