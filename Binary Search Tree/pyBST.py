#Author: Ron Bakrac

# Programming project: provide implementations for the functions below,
# i.e., replace all the pass statements in the functions below.
# Then add tests for these functions in the block
# that starts "if __name__ == '__main__':"

from TupleTrees import *
# All the functions in TupleTrees.py are now available

def preorder(T,f):
    if not is_bst(T):
        return
    if not T:
        return

    f(T[0])
    preorder(T[1],f)
    preorder(T[2],f)  

def postorder(T,f):
    if not is_bst(T):
        return
    if not T:
        return

    postorder(T[1],f)
    postorder(T[2],f)
    f(T[0])

def tree_height(T):
    # Empty tree has height -1
    if T == ():
        return -1
    
    return max(1 + tree_height(T[1]), 1 + tree_height(T[2]))

def balance(T):
    # returns the height of the left subtree of T
    # minus the height of the right subtree of T
    # i.e., the balance of the root of T
    if T == ():
        return 0

    return tree_height(T[1]) - tree_height(T[2])
    

def minBalance(T):
    # returns the minimum value of balance(S) for all subtrees S of T
    if T == ():
        return 0

    return min(minBalance(T[1]), minBalance(T[2]), balance(T))


def maxBalance(T):
    # returns the maximum value of balance(S) for all subtrees S of T
    if T == ():
        return 0

    return max(maxBalance(T[1]), maxBalance(T[2]), balance(T))

def is_avl(T):
    # Returns True if T is an AVL tree, False otherwise
    if -1 <= maxBalance(T) <= 1 and -1 <= minBalance(T) <= 1:
        return True

    return False

if __name__ == "__main__":
    # test code for the functions above
    T = (6, 9, 7, 12, 80)
    K = createBST(T)

    print_bintree(K)

    print('\nTree elements in sorted preorder\n')
    preorder(K,print_func_space)
    print()

    print('\nTree elements in sorted inorder\n')
    inorder(K,print_func_space)
    print()

    print('\nTree elements in sorted postorder\n')
    postorder(K,print_func_space)
    print()

    print(tree_height(K))
    print()

    print(balance(K))
    print()

    print(minBalance(K))
    print()

    print(maxBalance(K))
    print()

    print(is_avl(K))
    print()
