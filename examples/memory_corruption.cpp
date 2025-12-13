#include <iostream>
#include <thread>
#include <chrono>
#include <iomanip>
#include "../include/Organic.h"
#include "../include/BitFlipStrategy.h"

using namespace std::chrono_literals;

void printBinary(int value) {
    for (int i = 7; i >= 0; --i) {
        std::cout << ((value >> i) & 1);
    }
}

int main() {
    std::cout << "=== Memory Corruption Simulation ===\n\n";
    std::cout << "Demonstrating how cosmic rays / bit rot corrupt data.\n\n";

    auto sensorData = Organic<int>::create(0b11111111, 800);
    sensorData->setStrategy(std::make_unique<BitFlipStrategy<int>>());

    std::cout << "Initial sensor reading: ";
    printBinary(sensorData->get());
    std::cout << " (255)\n\n";

    std::cout << "Simulating data sitting in memory without ECC...\n\n";

    for (int i = 1; i <= 6; ++i) {
        std::this_thread::sleep_for(1200ms);
        int current = sensorData->peek();
        std::cout << "After " << i << "s: ";
        printBinary(current);
        std::cout << " (" << current << ")";
        
        if (current != 255) {
            std::cout << " ⚡ BIT FLIP!";
        }
        std::cout << "\n";
    }

    std::cout << "\n=== Corruption Complete ===\n";
    std::cout << "This demonstrates why ECC memory exists!\n";

    return 0;
}
