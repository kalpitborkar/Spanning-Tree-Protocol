# Spanning Tree Protocol - Simulation
## General Info
- Implementation of spanning tree protocol achieving loop-free network of LAN and bridge topology as a distributed system of nodes in C++.
- Spanning Tree Protocol - [Wikipedia Article](https://en.wikipedia.org/wiki/Spanning_Tree_Protocol)

## Setup
To run the simulation:
- Compile:  ```g++ -o bsim main.cpp bridgesim.cpp bridge.cpp```
- Run:      ```./bsim < inp1 > out1```

## Input format
- First line suggests the trace flag.
- Second line suggests the number of bridges in the topology.
- Each of the next lines suggest the bridges B1, B2, B3... and the corresponding LAN segments.
### Sameple input
```
05
B1: A G B
B2: G F
B3: B C
B4: C F E
B5: C D E
```
Where A, B, C, etc. are the LANs.

## Output format



