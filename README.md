# LibOrganic

Memory that dies if you don't feed it.

A modern C++20 library providing `Organic<T>`: a biodegradable memory wrapper that decays when not accessed.

## Features

- **Organic\<T\>** — Smart wrapper that tracks last access time
- **DecayManager** — Background thread (std::jthread) that monitors all organic objects
- **Strategy Pattern** — Pluggable corruption algorithms:
  - `DriftStrategy` — Gradually shifts numeric values (default)
  - `BitFlipStrategy` — Flips random bits in memory
  - `NullifyStrategy` — Resets value to default (zero)

## Quick Start

```cpp
#include "Organic.h"
#include "BitFlipStrategy.h"

auto health = Organic<int>::create(100, 2000);  // 2s lifetime
health->get();  // access resets decay timer

health->setStrategy(std::make_unique<BitFlipStrategy<int>>());
// after 2s without access, bits will flip
```

## Build

```bash
g++ -std=c++20 src/main.cpp src/DecayManager.cpp -Iinclude -pthread -o example
./example
```

Or with CMake:

```bash
mkdir build && cd build
cmake ..
cmake --build . --parallel
./example
```

<<<<<<< HEAD
=======
## Architecture

```
Organic<T>  ──registers──▶  DecayManager (singleton, jthread)
     │                            │
     └── CorruptionStrategy ◀─────┘ (called on expired objects)
            ├── DriftStrategy
            ├── BitFlipStrategy
            └── NullifyStrategy
```

## License

MIT
>>>>>>> bc77f22 (feat(corruption): add Strategy pattern (BitFlip/Drift/Nullify) and update README)
