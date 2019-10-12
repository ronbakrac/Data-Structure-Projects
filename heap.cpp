#include <vector>
#include <iostream>
#include <string>

using namespace std;


void swap(vector<int> &arr, int &i, int &j)
{
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

void heapify(vector<int> &arr, int i)
{
    int largest = i;

    int left = (2*i)+1;
    int right = (2*i)+2;

    if(arr[left] > arr[largest])
        largest = left;

    if(arr[right] > arr[largest])
        largest = right;
    
    if(largest != i)
    {
        swap(arr, i, largest);
        heapify(arr, largest);
    }

    return;
}

void buildheap(vector<int> &arr)
{
    int i = ((arr.size()-1)/2);
    for(; i>=0; i--)
    {
        heapify(arr, i);
    }

}

int main()
{
    vector<int> myarr = {2, 6, 8, 9, 7, 3, 1, 4, 12, 20};

    buildheap(myarr);

    for(int i=0; i<myarr.size(); i++)
    {
        cout<<myarr[i]<<" ";
    }

    return 0;
}