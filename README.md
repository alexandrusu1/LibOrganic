# LibOrganic

Slogan: Memory that dies if you don't feed it.

LibOrganic este o bibliotecă C++ care oferă un wrapper „biodegradabil” pentru date în memorie. Obiectele `Organic<T>` își pierd `last_access` dacă nu sunt accesate; un `DecayManager` de fond scanează obiectele și aplică strategii de corupere când acestora le expiră viața.

Principalele componente

- `include/Organic.h` — wrapper template `Organic<T>` (header-only).
- `include/IDecayable.h` — interfața pentru obiecte gestionabile de manager.
- `include/DecayManager.h` + `src/DecayManager.cpp` — manager singleton care rulează un fir de execuție pentru a declanșa decăderile.
- `src/main.cpp` — exemplu de utilizare.

Quick start

Build (cu CMake):

```bash
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build . --parallel
```

Apoi rulează exemplul:

```bash
./example
```

Contribuții

Următorii pași planificați:

- Migrare la C++20 complet (folosirea `std::jthread`, `std::weak_ptr` în manager).
- Adăugarea pattern-ului `CorruptionStrategy` (BitFlip, Drift, Nullify).
- Transformarea în header-only acolo unde este posibil.
- Teste unitare și workflow CI.

License

(Alege o licență și adaug-o aici.)
