#include <iostream>
#include <thread>
#include <string>
#include "../include/Organic.h"

int main() {
    std::cout << "=== LibOrganic Demo ===\n";
    std::cout << "Creating (int) with lifetime 2 seconds.\n";

    Organic<int> myHealth(100, 2000);

    std::cout << "Initial value " << *myHealth << "\n";

    for (int i = 0; i < 3; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        std::cout << "Accesing the variable... is still " << *myHealth << "\n"; 
    }

    std::cout << "\nIgnoring it 4 seconds...\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(4000));

  
    std::cout << "\nVerify the variable after ignore...\n";
    std::cout << "Final value: " << *myHealth << "\n";

    return 0;
}