##Henriksen-Algo-C
================

Implementation of Henriksen's Algorithm in C

#Current Implementation
- Create a new instance
- Insert events
- Dealloc tree
- Issues a pull onces DIST_MAX(4) items were counted. This does not include the tree nodethe search started from.

#Known issues/limitations/misc
- Tree is pointer based
- Times must be unique and must be in the exclusive range from INT_MIN to INT_MAX 
- Once an event is dequeued, all future events must have a time greated than the dequeued events time.
- If an insert takes place on the 4th item searched, the newly inserted item will not trigger a pull.
- deQueue with no events returns NULL and will not dequeue anything.
- delete will return NULL if no events with the given time were found.
- delete and insert will not respond to requests with times of INT_MIN or INT_MAX


#Structures
HDS
  Holds all necessary information for the structure.
  
#Functions

''' HDS* createHenrik() '''
- RETURN (HDS*) Pointer to the new structure;
Creates a new instance.

''' void destroyHenrik(HDS* hds) '''
- IN (hds) Pointer to the structure 
Deallocs the entire structure. Does not dealloc payloads.

''' void insertEvent(HDS* hds, int eTime, void* payload) '''
- IN (hds) Pointer to the structure
- IN (eTime) Time for the new event. Must be unique and between INT_MIN and INT_MAX exclusive. 
- IN (payload) Pointer to optional data regardng the event;
Inserts a new item in the queue into the passed structure. Items are sorted by eTime, payload is an optional pointer to additional data.

''' void* deQueue(HDS* hds) '''
- IN (hds) Pointer to the structure
- RETURN (VOID *) Pointer to the payload given when the event was inserted.
Removes the item from the front of the queue, if a payload was given the pointer will be returned.

''' void* delete(HDS* hds, int eTime) '''
- IN (hds) Pointer to the structure
- IN (eTime) Time of the event to remove
- RETURN (VOID *) Pointer to the payload given when the event was inserted.
Removes the item at the provided time, if a payload was given the pointer will be returned.


  
