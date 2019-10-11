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
class stack
{
    public:
        void push(const T &num);
        void pop();
        T top();
        bool empty();
    private:
        T arr[MAX];
        int mytop = -1;
};


template <class T>
void stack<T>::push(const T &num)
{
    if(mytop == MAX - 1)
        throw myexception("Stack is full");

    ++mytop;
    arr[mytop] = num;
}


template <class T>
bool stack<T>::empty()
{
    return(mytop == -1);
}

template <class T>
T stack<T>::top()
{
    if(!empty())
        return arr[mytop];
    
    else
        throw myexception("Error, top access on empty stack");
}

template <class T>
void stack<T>::pop()
{
    if(empty())
        throw myexception("Stack is empty");
    
    --mytop;

}

int main()
{
    stack<int> mystack;

    try
    {
        mystack.push(0);
        mystack.push(1);
        mystack.push(2);
        mystack.push(3);
        mystack.push(4);
        mystack.push(5);

        while(!mystack.empty())
        {
            std::cout<<mystack.top()<< " ";
            mystack.pop();
        }

    }

    catch(myexception &error)
    {
        std::cout<<error.what();
    }

    return 0;

}