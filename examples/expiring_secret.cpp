#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include "../include/Organic.h"
#include "../include/NullifyStrategy.h"

using namespace std::chrono_literals;

int main() {
    std::cout << "=== Auto-Expiring Secret Demo ===\n\n";
    std::cout << "Simulating a secret key that self-destructs if not used.\n\n";

    auto secretKey = Organic<int>::create(0xDEADBEEF, 2000);
    secretKey->setStrategy(std::make_unique<NullifyStrategy<int>>());

    std::cout << "Secret key created: 0x" << std::hex << secretKey->get() << std::dec << "\n";
    std::cout << "Key expires in 2 seconds if not accessed.\n\n";

    std::cout << "Accessing key immediately: 0x" << std::hex << secretKey->get() << std::dec << "\n";
    std::cout << "Timer reset!\n\n";

    std::cout << "Waiting 3 seconds without accessing...\n";
    std::this_thread::sleep_for(3500ms);

    std::cout << "\nAttempting to read key: 0x" << std::hex << secretKey->peek() << std::dec << "\n";
    
    if (secretKey->peek() == 0) {
        std::cout << "\n🔒 KEY EXPIRED — Self-destructed for security!\n";
    }

    return 0;
}
