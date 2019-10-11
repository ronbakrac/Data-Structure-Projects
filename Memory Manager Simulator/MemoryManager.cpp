//Ron Bakrac

#include <cassert>
#include <iostream>
#include "MemoryManager.h"

MemoryManager::MemoryManager(unsigned int memtotal)
{
   memsize = memtotal; // size of the "heap"
   baseptr = new unsigned char[memsize]; // allocate the heap
   // create empty blocknode list
   header = new blocknode();
   trailer = new blocknode();
   header->next = trailer;
   trailer->prev = header;
   // create blocknode to represent the entire heap
   blocknode *  originalBlocknode = new blocknode(memsize,baseptr,true);  
   header->insertAfter(originalBlocknode);
}

void MemoryManager::showBlockList() 
{
   blocknode *tmp = header->next;
   while(tmp->next != trailer) {
      cout << tmp << "->";
      tmp = tmp->next;
   }
   cout << tmp << "\n\n";
}

blocknode * MemoryManager::findFirstFit(unsigned int chunksize)
{
  blocknode *track = header->next;
  
      while(track != trailer)
      {
          if(track->free && track->blocksize >= chunksize)
              return track;
  
          track = track->next;
      }
  
      return nullptr;
}


void MemoryManager::splitBlock(blocknode *p, unsigned int chunksize)
{
  assert(p->free);
  
      if(p->blocksize > chunksize)
      {
          blocknode *splitnode = new blocknode(p->blocksize - chunksize, new unsigned char[p->blocksize - chunksize], 1);
          p->blocksize = chunksize;

          delete[] p->blockptr;
          p->blockptr = new unsigned char[p->blocksize];
      
          p->insertAfter(splitnode);
      }
      
      else{
          cout<<"Unable to split block.";
          return;
      }
  
}

unsigned char * MemoryManager::malloc(unsigned int request)
{
    blocknode *temp = findFirstFit(request);

    if(temp == nullptr)
        return nullptr;
  
    if(temp->blocksize > request)
        splitBlock(temp, request);

    temp->free = 0;
    return temp->blockptr;
}

blocknode * MemoryManager::findAllocatedBlock (unsigned char *allocated_ptr)
{ // returns a pointer to the first blocknode whose blockptr matches allocated_ptr;
  // if no such block exists, terminates the program
  blocknode *tracker = header->next;

  while(tracker != trailer)
  {
    if(allocated_ptr == tracker->blockptr)
    {
      return tracker;
    }
    
    tracker = tracker->next;
  }

  cout<<"Block not found";
  exit(1);

}

void MemoryManager::mergeForward(blocknode *p)
{
    if(p->free && p->next != trailer && p->next->free)
    {
        blocknode *hold = p->next;

        p->blocksize += p->next->blocksize;
        p->next = p->next->next;
        p->next->prev = p;
        delete hold;
        delete[] p->blockptr;
        p->blockptr = new unsigned char[p->blocksize];
    }

}

void MemoryManager::mergeBackward(blocknode *p)
{ 
    if(p->prev != header)
        mergeForward(p->prev);
}


void MemoryManager::free(unsigned char *ptr2block)
{
  blocknode *tracker = findAllocatedBlock(ptr2block);
  tracker->free = 1;
  mergeForward(tracker);
  mergeBackward(tracker);
}