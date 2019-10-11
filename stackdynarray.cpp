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
class stackdynarray
{
    public:
        stackdynarray<T>(int size = MAX);
        stackdynarray<T>(const stackdynarray<T> &other);
        ~stackdynarray<T>();
        bool empty();
        void push(const T &num);
        void pop();
        T top();
        stackdynarray<T> operator=(const stackdynarray<T> &other);
    private:
        T *arr;
        int capacity;
        int mytop = -1;
};

template <class T>
stackdynarray<T>::stackdynarray(int size)
{
    if(size < 0)
        throw myexception("Invalid array size");

    capacity = size;
    arr = new T[capacity];
}

template <class T>
stackdynarray<T>::~stackdynarray<T>()
{
    delete[] arr;
}

template <class T>
bool stackdynarray<T>::empty()
{
    return(mytop == -1);
}

template <class T>
void stackdynarray<T>::push(const T &num)
{
    if(mytop == capacity - 1)
    {
        T *newarr = new T[capacity*2];
        if(newarr == NULL)
            throw myexception("Fialed to allocate memory");
        
        for(int i=0; i < capacity; ++i)
            newarr[i] = arr[i];
        
        delete[] arr;
        arr = newarr;
    }

    else
    {
        ++mytop;
        arr[mytop] = num;
    }
}

template <class T>
void stackdynarray<T>::pop()
{
    if(empty())
        throw myexception("Stack is empty");
    
    --mytop;
}

template <class T>
T stackdynarray<T>::top()
{
    if(!empty())
        return arr[mytop];
}

template <class T>
stackdynarray<T> stackdynarray<T>::operator=(const stackdynarray<T> &other)
{
    capacity = other.capacity;
    mytop = other.mytop;
    delete[] arr;
    arr = new T[capacity];
    if(arr == NULL)
        throw myexception("Failed to initalize array");

    for(int i=0; i <= mytop; ++i)
        arr[i] = other[i];
    
    return *this;
}

template <class T>
stackdynarray<T>::stackdynarray(const stackdynarray<T> &other)
{
    capacity = other.capacity;
    mytop = other.mytop;

    arr = new T[capacity];
    if(arr == NULL)
        throw myexception("Failed to initalize array");

    for(int i=0; i <= mytop; ++i)
        arr[i] = other.arr[i];
    

}


int main()
{
    try
    {
        stackdynarray<int> ar1(110);

        ar1.push(0);
        ar1.push(1);
        ar1.push(2);
        ar1.push(3);
        ar1.push(4);
        ar1.push(5);

        ar1.pop();

        stackdynarray<int> ar2(ar1);

        while(!ar2.empty())
        {
            std::cout<<ar2.top();
            ar2.pop();
        }
    }

    catch(myexception &error)
    {
        std::cout<<error.what();
    }

    return 0;
}