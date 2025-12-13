#include <iostream>
#include <thread>
#include <string>
#include "../include/Organic.h"
#include "../include/BitFlipStrategy.h"
#include "../include/DriftStrategy.h"
#include "../include/NullifyStrategy.h"

int main() {
    std::cout << "=== LibOrganic Demo ===\n";
    std::cout << "Memory that dies if you don't feed it.\n\n";

    std::cout << "--- DriftStrategy (default) ---\n";
    auto driftVar = Organic<int>::create(100, 1500);
    std::cout << "Initial: " << driftVar->get() << "\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(3500));
    std::cout << "After decay: " << driftVar->peek() << "\n\n";

    std::cout << "--- BitFlipStrategy ---\n";
    auto bitVar = Organic<int>::create(255, 1500);
    bitVar->setStrategy(std::make_unique<BitFlipStrategy<int>>());
    std::cout << "Initial: " << bitVar->get() << "\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(3500));
    std::cout << "After decay: " << bitVar->peek() << "\n\n";

    std::cout << "--- NullifyStrategy ---\n";
    auto nullVar = Organic<int>::create(42, 1500);
    nullVar->setStrategy(std::make_unique<NullifyStrategy<int>>());
    std::cout << "Initial: " << nullVar->get() << "\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(3500));
    std::cout << "After decay: " << nullVar->peek() << "\n\n";

    std::cout << "=== Demo complete ===\n";
    return 0;
}