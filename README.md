<div align="center">

# 🧬 LibOrganic

### *Memory that dies if you don't feed it.*

[![C++20](https://img.shields.io/badge/C%2B%2B-20-blue.svg?style=flat&logo=c%2B%2B)](https://en.cppreference.com/w/cpp/20)
[![License: MIT](https://img.shields.io/badge/License-MIT-green.svg)](LICENSE)
[![Platform](https://img.shields.io/badge/Platform-Linux%20%7C%20macOS%20%7C%20Windows-lightgrey.svg)]()
[![PRs Welcome](https://img.shields.io/badge/PRs-welcome-brightgreen.svg)](CONTRIBUTING.md)

<br>

**A biodegradable memory wrapper for C++20.**  
Variables that decay, corrupt, and die when neglected.

<br>

```
    ╭──────────────────────────────────────────╮
    │  int health = 100;                       │
    │                                          │
    │  // You forgot about it...               │
    │  // 3 seconds later...                   │
    │                                          │
    │  health == 73  // It's rotting 🦠        │
    ╰──────────────────────────────────────────╯
```

</div>

---

## 🎯 Why LibOrganic?

Traditional variables are **immortal** — they hold their value forever until explicitly changed.

**LibOrganic** introduces **mortal memory**: values that degrade over time unless actively used. Think of it like:

| Real World | LibOrganic |
|------------|------------|
| 🥛 Milk spoils if you don't drink it | Variables decay if you don't access them |
| 🔋 Batteries drain when idle | Values corrupt when neglected |
| 🧠 Memories fade without recall | Data rots without interaction |

---

## ✨ Features

- **🧬 Organic\<T\>** — Smart wrapper with built-in decay timer
- **⚡ DecayManager** — Lock-free background entropy (std::jthread)
- **🎨 Strategy Pattern** — Pluggable corruption algorithms:

| Strategy | Effect | Best For |
|----------|--------|----------|
| `DriftStrategy` | Gradually shifts values (±10%) | Numeric drift simulation |
| `BitFlipStrategy` | Flips random bits | Chaos/corruption testing |
| `NullifyStrategy` | Resets to zero/default | Hard expiration |

---

## 🚀 Quick Start

```cpp
#include "Organic.h"
#include "BitFlipStrategy.h"

int main() {
    // create a 2 second lifetime variable
    auto health = Organic<int>::create(100, 2000);
    
    std::cout << health->get();  // 100 — access resets decay timer
    
    // wait 3 seconds (not accesing it)
    std::this_thread::sleep_for(3s);
    
    std::cout << health->peek(); // 89 — it decayed!
    
    // switch corruption strategy
    health->setStrategy(std::make_unique<BitFlipStrategy<int>>());
    
    return 0;
}
```

---

## 🔧 Installation

### Header-Only (Recommended)

Copy the `include/` folder to your project:

```cpp
#include "liborganic/Organic.h"
```

### Build from Source

```bash
git clone https://github.com/alexandrusu1/LibOrganic.git
cd LibOrganic

#compilation
g++ -std=c++20 src/main.cpp src/DecayManager.cpp -Iinclude -pthread -o example

#compile with cmake
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build . --parallel
./example
```

---

## 🏗️ Architecture

```
┌─────────────────────────────────────────────────────────────────┐
│                         User Code                               │
│                                                                 │
│   auto x = Organic<int>::create(42, 1500);                      │
│   x->get();  // Touch! Timer reset.                             │
└─────────────────────┬───────────────────────────────────────────┘
                      │
                      ▼
┌─────────────────────────────────────────────────────────────────┐
│                      Organic<T>                                 │
│  ┌─────────────┐  ┌──────────────┐  ┌────────────────────────┐  │
│  │ T value     │  │ atomic<ms>   │  │ CorruptionStrategy<T>* │  │
│  │             │  │ lastAccess   │  │ (default: Drift)       │  │
│  └─────────────┘  └──────────────┘  └────────────────────────┘  │
└─────────────────────┬───────────────────────────────────────────┘
                      │ registers via weak_ptr
                      ▼
┌─────────────────────────────────────────────────────────────────┐
│                    DecayManager (Singleton)                     │
│                                                                 │
│   std::jthread ─────► entropyLoop() {                           │
│                         for each object:                        │
│                           if (now - lastAccess > TTL)           │
│                             object->decay();                    │
│                       }                                         │
└─────────────────────────────────────────────────────────────────┘
```

---

## 📚 API Reference

### Organic\<T\>

| Method | Description |
|--------|-------------|
| `create(value, ttlMs)` | Factory method — creates managed instance |
| `get()` | Access value & reset decay timer |
| `peek()` | Read value WITHOUT resetting timer |
| `touch()` | Reset timer without reading value |
| `setStrategy(unique_ptr)` | Change corruption algorithm |

### Built-in Strategies

```cpp
#include "DriftStrategy.h"    // gradual numeric drift
#include "BitFlipStrategy.h"  // random bit corruption  
#include "NullifyStrategy.h"  // reset to T{}
```

---

## 🎮 Use Cases

| Domain | Application |
|--------|-------------|
| 🎮 **Game Dev** | Health/stamina that drains when idle |
| 🔐 **Security** | Auto-expiring encryption keys |
| 🧪 **Testing** | Memory corruption simulation |
| 💾 **Caching** | Self-invalidating cache entries |
| 🤖 **AI/ML** | Decaying weights, forgetting mechanisms |

---

## 🛠️ Requirements

- **C++20** compiler (GCC 10+, Clang 10+, MSVC 19.29+)
- **pthread** support (Linux/macOS) or Windows threads

---

## 🤝 Contributing

Contributions welcome! See [CONTRIBUTING.md](CONTRIBUTING.md) for guidelines.

Ideas for contribution:
- [ ] New corruption strategies (Gaussian noise, byte shuffle)
- [ ] Configurable decay curves (linear, exponential)
- [ ] Thread-safe value access with mutex
- [ ] Serialization support
- [ ] Python bindings

---

## 📄 License

[MIT](LICENSE) © 2024 Alexandru Su

---

<div align="center">

**Built with 🧬 and C++20**

*"In LibOrganic, all memory is mortal."*

</div>
