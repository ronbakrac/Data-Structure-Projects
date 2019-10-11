// ------------------------------RescueRemy.cpp-----------------------------
// This program should always be run with input redirected to a file
// Use this to test your print_bfs_exitpath method

#include <iostream>
#include <limits> 
#include "maze.h"

using namespace std;

int main()
{
  int userin;
  maze RatHaus; // interactive constructor

  while(true)
  {
    cout << "1.) Depth-first search\n2.) Breadth-first search\n3.) Exit\n";
    cin >> userin;

    switch(userin)
    {
      case 1:
          RatHaus.print_dfs_exitpath();
          break;
      case 2:
          RatHaus.print_bfs_exitpath();
          break;
      case 3:
          return 0;
      default:
          cout<<"Invalid input\n";
           cin.clear();
           cin.ignore(numeric_limits<streamsize>::max(),'\n');
          continue; 
    }

  
    return 0;
  }
}
