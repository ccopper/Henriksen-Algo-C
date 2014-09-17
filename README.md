Henriksen-Algo-C
================

Implementation of Henriksen's Algorithm in C

Current Implementation:
-Create a new instance
-Insert events (Tree does not expand past inital 3 nodes)
-Dealloc tree

'Structures
HDS
  Holds all necessary information for the structure.
  
'Functions

HDS* createHenrik()
  Creates a new instance and returns the pointer.

void destroyHenrik(HDS* hds)
  Deallocs the entire structure. Does not dealloc payloads.


void insertEvent(HDS* hds, int eTime, void* payload)
  Inserts a new item in the queue into the passed structure. Items are sorted by eTime, payload is an optional pointer to additional data.
  
