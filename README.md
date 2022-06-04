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
### Sample input
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
- Each line suggests the name of the bridge (B1, B2, etc.) and the state of each port.
- DP: Designated Port
- RP: Root Port
- NP: Null Port

### Sample output
```
B1: A-DP B-DP G-DP
B2: F-DP G-RP
B3: B-RP C-DP
B4: C-NP E-DP F-RP
B5: C-RP D-DP E-NP
```


## Trace format
```
t s|r Bk (Bi, d, Bj)
```
Where:
- t:           Time of the event
- Bk:          ID of the node at which the event has happened
- s/r:         Send or Receive event
- (Bi, d, Bj): Message indicating that Bridge Bj thinks Bridge Bi is the root and it is at a distance d from the root.

## References
- https://www.researchgate.net/publication/238778689_An_Algorithm_for_Distributed_computation_of_a_Spanning_Tree_in_an_Extended_LAN
- https://en.wikipedia.org/wiki/Spanning_Tree_Protocol
- https://www.youtube.com/watch?v=japdEY1UKe4&ab_channel=CertBros

