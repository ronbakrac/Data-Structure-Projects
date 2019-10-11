'''Provides basic operations for Binary Search Trees using
a tuple representation.  In this representation, a BST is
either an empty tuple or a length-3 tuple consisting of a data value,
a BST called the left subtree and a BST called the right subtree
'''

def is_bintree(T):
    if type(T) is not tuple:
        return False
    if T == (): # empty tree
        return True
    if len(T) != 3:
        return False
    return is_bintree(T[1]) and is_bintree(T[2])

def bst_min(T):
    # assumption: T is a binary search tree
    if T == ():
        return None
    if T[1] == ():
        return T[0]
    return bst_min(T[1])

def bst_max(T):
    # assumption: T is a binary search tree
    if T == ():
        return None
    if T[2] == ():
        return T[0]
    return bst_max(T[2])

def is_bst(T): 
    "Returns True if T is a binary search tree"
    if not is_bintree(T):
        return False
    if T == ():
        return True

    if not is_bst(T[1]) or not is_bst(T[2]):  # recursion!
        return False
    
    if T[1] == () and T[2] == ():
        return True
    
    if T[2] == ():
        return bst_max(T[1]) < T[0]

    if T[1] == ():
        return T[0] < bst_min(T[2])

    return bst_max(T[1]) < T[0] < bst_min(T[2]) 

def bst_search(T,x):
    "Returns the subtree whose data item equals x"
    if T == ():
        return None
    if T[0] == x:
        return T
    if x < T[0]:
        return bst_search(T[1],x)
    return bst_search(T[2],x)

def bst_insert(T,x):
    "returns the tree resulting from insertion of data item x"
    if T == ():
        return (x,(),())
    if x > T[0]:
        
        return (T[0],T[1],bst_insert(T[2],x))
    return (T[0],bst_insert(T[1],x),T[2])

def delete_min(T):
    '''Returns the tree that results when the smallest element in T
    has been deleted'''
    if T == ():
        return T
    
    if not T[1]:    # No left subtree – minimum value is the root value
        return T[2]
    else: # Minimum value is in the left subtree
        return (T[0],delete_min(T[1]),T[2])

def bst_delete(T,x):
    '''Returns the tree that results when the data item x
    has been deleted from T'''

    assert T, "deleting from an empty tree"

    if x < T[0]:
        return (T[0], bst_delete(T[1],x), T[2])

    elif x > T[0]:
        return (T[0], T[1], bst_delete(T[2],x))

    else:
        # single child cases
        if not T[1]: 
            return T[2]
        elif not T[2]:
            return T[1]
        else:
            # two children case
            return (bst_min(T[2]) , T[1], delete_min(T[2]) )

def print_bintree(T,indent=0):
    "Prints the tree using indentation to show the structure"
    if not T:
        print('*')
        return

    else:
        print(T[0])

        print('  '*(indent + T[0]-1)+'---', end = '')
        print_bintree(T[1],indent+3)
        print('  '*(indent + T[0]-1)+'---', end = '')

        print_bintree(T[2],indent+3)      

def print_func_space(x):
    "prints a value x followed by a space"
    print(x,end=' ')

def inorder(T, f): 
    "Applies the function f to root value of each subtree of T"
    if not is_bst(T):
        return
    if not T:
        return

    inorder(T[1],f)  # apply f to the root value of each subtree of T[1]
    f(T[0])          # apply f to the root value of T
    inorder(T[2],f)  # apply f to the root value of each subtree of T[2]

def createBST(values):
    '''Creates and returns the binary search tree obtained by inserting,
    in order, the values in tuple values into an initially empty tree'''
    K = ()
    for x in values:
        K = bst_insert(K,x)  # ***
    return K

        
if __name__ == '__main__':
    # code to test the functions in this module
    t = ('Joe','Bob', 'Phil', 'Paul', 'Marc', 'Jean', 'Jerry',
         'Alice', 'Anne')
    K = createBST(t)
    print('\nTree elements in sorted order\n')
    inorder(K,print_func_space)
    print()

    print('\nPrint full tree\n')
    print_bintree(K)
    print("\nDelete Bob and print tree\n")
    K = bst_delete(K,'Bob')
    print_bintree(K)
    print() # print a blank line

    print("\nPrint subtree at 'Phil'\n")
    print_bintree(bst_search(K,'Phil'))
    print()
