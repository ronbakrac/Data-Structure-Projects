#include <iostream>

template <class T>
class SNode
{
    public:
        SNode<T>(T value)
        {
            val = value;
            next = nullptr;
        }

        T val;
        SNode<T> *next;
};

template <class T>
class llist
{
    public:
        SNode<T>* append(SNode<T>* head, T val);
        bool inList(const SNode<T>* head, T val);
};

template <class T>
SNode<T>* llist<T>::append(SNode<T>* head, T val)
{
    SNode<T> *newnode = new SNode<T>(10);

    if(head == nullptr)
    {
        head = newnode;
        return newnode;
    }
    
    else
    {
        SNode<T> *track = head;
        while(track->next != nullptr)
        {
            track = track->next;
        }

        track->next = newnode;

        return head;
    }
    
}

template <class T>
bool llist<T>::inList(const SNode<T>* head, T val)
{
    const SNode<T> *tracker = head;

    for(; tracker != nullptr; tracker = tracker->next)
    {
        if(tracker->val == val)
            return 1;
    }

    return 0;
}


int main()
{
    SNode<int> *first = new SNode<int>(6);
    llist<int> mylist;

    first = mylist.append(first, 10);

    std::cout<< first->val<<" "<<first->next->val<<" "<<mylist.inList(first, 2);

    return 0;
    

}