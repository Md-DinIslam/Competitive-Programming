# Competitive Programming

A curated collection of Data Structures, Algorithms, and solutions to competitive programming problems implemented in modern C++.

---

## Repository Structure

| Topic | Description / Focus Areas |
| :--- | :--- |
| **[DP](DP/)** | Classical & advanced dynamic programming (CSES, AtCoder, etc.) |
| **[Graph](Graph/)** | Traversal, shortest paths, spanning trees, flows, and trees |
| **[DSA](DSA/)** | Core and advanced data structures (Trees, Segment Trees, Fenwick, DSU) |
| **[Number Theory](Number%20Theory/)** | Prime factorization, modular arithmetic, GCD/LCM, combinatorics |
| **[String](String/) & [Trie](Trie/)** | Hashing, pattern matching, prefix trees, KMP |
| **[Geometry](Geometry/)** | Computational geometry, convex hull, point & line primitives |
| **[Bit Manipulation](Bit%20Manipulation/)** | Bitwise masks, bit hacks, subset generation |
| **[Sorting & Searching](Sorting%20%26%20Searching/)** | Binary search variants, sorting algorithms, two pointers |
| **[Backtracking](Backtracking/) & [Linked List](Linked%20List/)** | State exploration, pruning, recursion, pointer-based structures |

---

## Utilities & Templates

- **[debug.h](debug.h)**: Universal recursive debugging tool for local testing. Pretty-prints primitives, pairs, tuples, and nested STL containers.
- **[debug_onsite.h](debug_onsite.h)**: Lightweight debugger tailored for on-site contests.
- **[CP_Cheat_Sheet.pdf](CP_Cheat_Sheet.pdf)**: Quick-reference cheat sheet for algorithms, complexity, and formulas.

### Debugging Usage

```cpp
#ifdef LOCAL
#include "debug.h"
#else
#define dg(...)
#endif
```

---

## Compilation

Recommended flags for local compilation:

```bash
g++ -O2 -std=c++17 -DLOCAL solution.cpp -o solution
./solution
```