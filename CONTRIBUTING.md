# Contributing to LibOrganic

Thank you for your interest in contributing to LibOrganic! 🧬

## How to Contribute

### Reporting Bugs

1. Check existing [Issues](https://github.com/alexandrusu1/LibOrganic/issues)
2. Create a new issue with:
   - Clear title
   - Steps to reproduce
   - Expected vs actual behavior
   - Compiler and OS version

### Suggesting Features

Open an issue with the `enhancement` label describing:
- The problem you're trying to solve
- Your proposed solution
- Alternative approaches considered

### Pull Requests

1. Fork the repository
2. Create a feature branch: `git checkout -b feat/amazing-feature`
3. Write your code following our style guide
4. Add tests if applicable
5. Commit with semantic messages: `feat:`, `fix:`, `docs:`, `refactor:`
6. Push and open a PR

## Code Style

- **Modern C++20** — Use concepts, ranges, and modern idioms
- **No comments** — Code should be self-documenting
- **RAII everywhere** — No manual memory management
- **Naming conventions:**
  - Classes: `PascalCase`
  - Methods: `camelCase`
  - Constants: `SCREAMING_SNAKE_CASE`
  - Files: `PascalCase.h` / `PascalCase.cpp`

## Project Structure

```
LibOrganic/
├── include/           # Header files (public API)
│   ├── Organic.h
│   ├── DecayManager.h
│   ├── IDecayable.h
│   └── *Strategy.h
├── src/               # Implementation files
│   ├── DecayManager.cpp
│   └── main.cpp       # Example/demo
├── examples/          # Additional examples
└── tests/             # Unit tests (coming soon)
```

## Ideas for Contribution

- [ ] **New Strategies**: Gaussian noise, byte shuffle, gradual zeroing
- [ ] **Decay Curves**: Linear, exponential, step functions
- [ ] **Thread Safety**: Optional mutex-protected value access
- [ ] **Callbacks**: `onDecay`, `onExpire` hooks
- [ ] **Serialization**: Save/restore organic state
- [ ] **Benchmarks**: Performance testing suite
- [ ] **Documentation**: Doxygen or mdBook docs

## Development Setup

```bash
git clone https://github.com/alexandrusu1/LibOrganic.git
cd LibOrganic
g++ -std=c++20 src/main.cpp src/DecayManager.cpp -Iinclude -pthread -o example
./example
```

## Questions?

Open an issue or reach out — we're happy to help!

---

*"In LibOrganic, all contributions are immortal."* 🧬
