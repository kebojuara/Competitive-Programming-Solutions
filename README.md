# Competitive Programming Solutions

This collection contains ten standalone C++ programs for problems from SPOJ and Eolymp. The walkthroughs explain how to turn the problem rules into a model, why the algorithm follows from that model, and how the program represents it.

## Problem collection

| ID | Problem | Platform | Main topic | Walkthrough | Official statement |
| --- | --- | --- | --- | --- | --- |
| POCALC1 | Ancient Pocket Calculator | SPOJ | Calculator state machine and numeric formatting | [README](POCALC1%20-%20Ancient%20Pocket%20Calculator/README.md) | [Statement](https://www.spoj.com/problems/POCALC1/) |
| GOLDG | Goldbach graphs | SPOJ | Prime-factor sieve and implicit graph BFS | [README](GOLDG%20-%20Goldbach%20graphs/README.md) | [Statement](https://www.spoj.com/problems/GOLDG/) |
| CFONISMG | Seating Plan | SPOJ | Backtracking over desk assignments | [README](CFONISMG%20-%20Seating%20Plan/README.md) | [Statement](https://www.spoj.com/problems/CFONISMG/) |
| RAYGUN | Ray Gun | SPOJ | Möbius inversion and quotient grouping | [README](RAYGUN%20-%20Ray%20Gun/README.md) | [Statement](https://www.spoj.com/problems/RAYGUN/) |
| JRIDE | Jill Rides Again | SPOJ | Kadane's algorithm with interval tie-breaks | [README](JRIDE%20-%20Jill%20Rides%20Again/README.md) | [Statement](https://www.spoj.com/problems/JRIDE/) |
| HISTOGRA | Largest Rectangle in a Histogram | SPOJ | Monotonic stack | [README](HISTOGRA%20-%20Largest%20Rectangle%20in%20a%20Histogram/README.md) | [Statement](https://www.spoj.com/problems/HISTOGRA/) |
| MGSINFOB | Russian Year 5 Problem | SPOJ | Complement lookup with a hash map | [README](MGSINFOB%20-%20Russian%20Year%205%20Problem/README.md) | [Statement](https://www.spoj.com/problems/MGSINFOB/) |
| 854 | Friendly Numbers | Eolymp | Amicable-number lookup table | [README](Friendly%20Numbers%20%23854/README.md) | [Statement](https://eolymp.com/problems/854) |
| 10167 | Student's queue in a canteen | Eolymp | Two-level FIFO and a team lookup | [README](Student%27s%20queue%20in%20a%20canteen%20%2310167/README.md) | [Statement](https://eolymp.com/problems/10167) |
| 26 | New-year presents | Eolymp | Two-stage scheduling with Johnson’s pairwise rule | [README](New-year%20presents%20%2326/README.md) | [Statement](https://eolymp.com/problems/26) |

## Topics covered

- **State and simulation.** The calculator tracks a pending operation between keypresses. The canteen simulator uses a queue of teams and a queue of students for each team.
- **Graphs and number theory.** Goldbach graphs generates edges from prime factors as BFS visits each vertex. Ray Gun uses Möbius inversion to count primitive lattice directions. Friendly Numbers filters a precomputed table of amicable pairs.
- **Linear scans.** Jill Rides Again keeps the best route segment as ratings arrive. The histogram solution uses a monotonic stack to find rectangle boundaries, and Russian Year 5 Problem looks up each value's complement.
- **Search and scheduling.** Seating Plan enumerates desk assignments by backtracking. New-year presents compares adjacent jobs and computes the finish time of the resulting two-stage schedule.

## Repository structure

Each problem folder contains its walkthrough, a standalone source file, and a judge screenshot. The root index lists the official statements.

```text
Competitive-Programming-Solutions/
├── README.md
├── CFONISMG - Seating Plan/
│   ├── README.md
│   ├── code.cpp
│   └── accepted.png
├── Friendly Numbers #854/
│   ├── README.md
│   ├── code.cpp
│   └── accepted.png
├── GOLDG - Goldbach graphs/
│   ├── README.md
│   ├── code.cpp
│   └── accepted.png
├── HISTOGRA - Largest Rectangle in a Histogram/
│   ├── README.md
│   ├── code.cpp
│   └── accepted.png
├── JRIDE - Jill Rides Again/
│   ├── README.md
│   ├── code.cpp
│   └── accepted.png
├── MGSINFOB - Russian Year 5 Problem/
│   ├── README.md
│   ├── code.cpp
│   └── accepted.png
├── New-year presents #26/
│   ├── README.md
│   ├── code.cpp
│   └── accepted.png
├── POCALC1 - Ancient Pocket Calculator/
│   ├── README.md
│   ├── code.cpp
│   └── accepted.png
├── RAYGUN - Ray Gun/
│   ├── README.md
│   ├── code.cpp
│   └── accepted.png
└── Student's queue in a canteen #10167/
    ├── README.md
    ├── code.cpp
    └── accepted.png
```

## Documentation

Each problem README describes the input and output, shows the key equations or invariants, and traces a worked example. Code excerpts connect the reasoning to the full C++ source. Each page gives time and space complexity and identifies the verdict or score shown in its screenshot.

## Building and running

Compile one source file at a time with `g++` in GNU C++17 mode. From the repository root, build and run the histogram solution with the following commands.

```bash
build_dir="$(mktemp -d)"
g++ -std=gnu++17 -O2 "HISTOGRA - Largest Rectangle in a Histogram/code.cpp" -o "$build_dir/histogra"
printf '6 2 2 1 3 3 3\n0\n' | "$build_dir/histogra"
```

This prints `9`. Each program reads its problem's input from standard input and writes to standard output. See the individual walkthrough for the input format and termination rule.

## Original problem sources

SPOJ and Eolymp host the original problem statements. The collection table links each one. [SPOJ](https://www.spoj.com/) · [Eolymp](https://eolymp.com/)
