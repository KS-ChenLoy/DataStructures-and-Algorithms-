#include <iostream>
using namespace std;
void heapify(int heap[],int size,int pos)
{
    int lpos, rpos, largest;
    largest = pos;
    lpos = 2 * pos+1;
    rpos = 2 * pos+2;

    if (lpos < size && heap[lpos] > heap[largest])
        largest = lpos;
    if (rpos < size && heap[rpos] > heap[largest])
        largest = rpos;
    if (largest!=pos){
        swap(heap[pos], heap[largest]);
        heapify(heap,size,largest);
    }

}

int* extractMax(int arr[], int size)
{
    //code here
    int set_Size = size-1;
    arr[0] = arr[set_Size];
    heapify(arr,set_Size,0);
    return arr;
}

//Don't change main
int main() {

    int size;
    cin >> size;
    int* arr = new int[size];

    for(int i = 0; i < size; i++)
        cin >> arr[i];

    arr =  extractMax(arr, size);
    for(int i = 0; i < size - 1; i++)
        cout << arr[i] << " ";

    return 0;
}
//Reference
//Discussion 6 slides from previous semester.