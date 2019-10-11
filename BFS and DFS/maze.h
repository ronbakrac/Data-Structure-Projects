#include<stack>
#include<queue>
#include<vector>

using namespace std;

struct vnode {
  int v; // vertex
  vnode *next;
  vnode(int u, vnode *n) {v=u; next=n;}
};

typedef vnode * vnodeptr;

class maze
{
  public:
   maze();  // interactive constructor using cin
   void print_dfs_exitpath();
   void print_bfs_exitpath();
  private:
   int size;
   int start;
   int exit;
   vector<vnodeptr> adjList;
   stack<int> dfs();
   vector<int> bfs();
};

void printBottomToTop(stack<int> S);
void printPredecessorPath(vector<int> pred);



