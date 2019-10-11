//Ron Bakrac

#include "maze.h"
#include <cassert>
#include <iostream>
#include <fstream>

using namespace std;

void printBottomToTop(stack<int> S)
{
  stack<int> tmp;
  while(!S.empty()) {
    tmp.push(S.top());
    S.pop();
  }
  while(!tmp.empty()) {
    cout << tmp.top();
    tmp.pop();
    if(!tmp.empty())
      cout << "->";
    else
      cout << endl;
  }
}
    
void printPredecessorPath(vector<int> pred,int target)
{
  stack<int> S;
  int current = target;
  while(pred[current] >= 0) {
    S.push(current);
    current = pred[current];
  }

  S.push(current);

  while(S.size() > 1) {
    cout << S.top() << "->";
    S.pop();
  }
  cout << S.top() << endl;
}


maze::maze()
{
  ifstream inputfile ("input.txt");

  int vertex;
  inputfile >> size;
  inputfile >> start;
  inputfile >> exit;
  assert(0 <= start && start < size);
  assert(0 <= exit && exit < size);

  adjList.resize(size,NULL);
  for(int i = 0; i < size; ++i) {
    inputfile >> vertex;
    while(vertex != -1) {
    	if(vertex == i) {
    		cerr << "Invalid adjacency; terminating" << endl;
    		assert(vertex != i);
    	}
    	adjList[i] = new vnode(vertex,adjList[i]); // insert at begining
      	inputfile >> vertex;
    }
  }
}

stack<int> maze::dfs()
{
  int current, nbr;
  vector<bool> visited(size,false);
  stack<int> path;
  visited[start] = true;
  path.push(start);
  while(!path.empty()) 
  {
    current = path.top();
    if(current == exit) 
    {
	    break;
    }

    vnodeptr cursor = adjList[current];
    while(cursor != nullptr && visited[cursor->v])
      cursor = cursor->next;

    if(cursor != nullptr) 
    {
      // found an open neighbor
      nbr = cursor->v;
      visited[nbr] = true;
      path.push(nbr);
    } 

    else 
    {
       // back out
      path.pop();
      if(path.empty()) 
      { 
        // backed out from start
	      break;
      }
      
    }
    // Continue search from the newly discovered vertex
  }
  return path;
}

void maze::print_dfs_exitpath()
{
     stack<int> path = dfs();
     if(path.empty())
       cout << "No way out" << endl;
     printBottomToTop(path);
}

void maze::print_bfs_exitpath()
{
  vector<int> pred = bfs();
  if (pred[exit] == -1)
    cout << "No way out" << endl;
  else
    printPredecessorPath(pred,exit);
}

vector<int> maze::bfs()
{
    int current = start, nbr;
    queue<int> Q;
    vector<int> pred(size,-1);
    pred[start] = -2;
    Q.push(start);
    while(!Q.empty()) 
    {
      current = Q.front();
      Q.pop();

      if(current == exit)
      {
        pred[current] = current;
        break;
      }

      vnodeptr tracker = adjList[current];
      while(tracker != nullptr)
      {
        if(pred[tracker->v] == -1)
        {
          Q.push(tracker->v);
          pred[tracker->v] = current;
          if(tracker->v == exit)
            return pred;
        }
        tracker = tracker->next;
      }

    }
    return pred;
}
