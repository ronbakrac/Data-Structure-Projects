#include <exception>
#include <iostream>
#include <string>
#define MAX 100

class myexception : public std::exception
{
    public:
        myexception(const std::string &str) : msg(str){}

        const std::string what()
        {
            return msg;
        }

    private:
        std::string msg;
};

template <class T>
class queue
{
    public:
        void push(const T &num);
        void pop();
        const T front();
        const T back();
        bool empty();
    private:
        int top = 0;
        int next = 0;
        T arr[MAX];
};

template <class T>
bool queue<T>::empty()
{
    return(top == next);
}

template <class T>
void queue<T>::push(const T &num)
{
    if((next + 1)%MAX == top)
        throw myexception("Queue is full");
    
    arr[next] = num;
    next = (next+1)%MAX;

}

template <class T>
void queue<T>::pop()
{
    if(empty())
        throw myexception("Queue is empty");
    
    top = (top+1)%MAX;
}

template <class T>
const T queue<T>::front()
{
    return arr[top];
}

template <class T>
const T queue<T>::back()
{
    return arr[next];
}

int main()
{
    queue<int> myq;

    try
    {
        myq.push(0);
        myq.push(1);
        myq.push(2);
        myq.push(3);
        myq.push(4);
        myq.push(5);

        myq.pop();
        myq.pop();

        while(!myq.empty())
        {
            std::cout<<myq.front();
            myq.pop();
        }
    }

    catch(myexception &error)
    {
        std::cout<<error.what();
    }

    return 0;
}