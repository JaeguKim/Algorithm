#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#define SIZE 500

using namespace std;

class Heap{
private:
    int origin_size;
    int cur_size;
    vector<int> H;
    vector<int> S;
    vector<int> backup;
public:
    Heap(int n){
        origin_size = n;
        cur_size = origin_size;
        H.reserve(n+1);
        S.reserve(n+1);
        backup.reserve(n+1);
        H.push_back(0);
        S.push_back(0);
        backup.push_back(0);
    }
    void setHeapArray(int input){
        H.push_back(input);
        backup.push_back(input);
    }
    vector<int> getHeapArray(){
        return H;
    }
    void siftdown(int i){
        int siftkey,parent;
        bool found;
        int smallerChild;
        
        siftkey = H[i];	parent = i;	found = false;
        while ((2*parent <= cur_size) && (found == false))
        {
            if ((2*parent < cur_size)&&(H[2*parent] >= H[2*parent +1]))
                smallerChild = 2*parent + 1;
            else  smallerChild = 2 * parent;
            if (siftkey > H[smallerChild])
            {
                H[parent] = H[smallerChild];
                parent = smallerChild;
            }
            else found = true;
        }
        H[parent] = siftkey;
    }
    void makeHeap()
    {
        for (int i = cur_size/2; i>=1; i--)
            siftdown(i);
    }
    int deleteHeap()  // Θ(log n)
    {                         // delete-max //
        int keyout = H[1];
        int root;
        H[1] = H[cur_size];
        cur_size = cur_size-1;
        siftdown(1);
        root = keyout;
        
        return root;
    }
    void insertHeap(int input)
    {
        cur_size = cur_size+1;
        H[cur_size] = input;
        int i = cur_size;
        while(1)
        {
            if (H[i/2] > input)
                H[i] = H[i/2];
            else
                break;
            i = i/2;
        }
        H[i] = input;
    }
    void makeSortedArray()
    {
        for (int i = 1; i <= origin_size; i++)
            S.push_back(deleteHeap());
    }
    
    vector<int> heapsort()
    {
        makeHeap();
        makeSortedArray();
        restore();
        return S;
    }
    
    void restore(){
        cur_size = origin_size;
        for (int i = 1; i<=origin_size; i++){
            H.push_back(backup[i]);
        }
    }
};

int H[SIZE];
int backUp[SIZE];
int heapSize;
int S[SIZE];

void siftdown (int i, int heap_size)
{
    int siftkey,parent;
    bool found;
    int smallerChild;
    
    siftkey = H[i];	parent = i;	found = false;
    while ((2*parent <= heap_size) && (found == false))
    {
        if ((2*parent < heap_size)&&(H[2*parent] >= H[2*parent +1]))
            smallerChild = 2*parent + 1;
        else  smallerChild = 2 * parent;
        if (siftkey > H[smallerChild])
        {
            H[parent] = H[smallerChild];
            parent = smallerChild;
        }
        else found = true;
    }
    H[parent] = siftkey;
}

void makeHeap (int n)
{
    for (int i = n/2; i>=1; i--)
        siftdown (i, n);
}

int deleteHeap()  // Θ(log n)
{                         // delete-max //
    int keyout = H[1];
    int root;
    H[1] = H[heapSize];
    heapSize = heapSize-1;
    siftdown(1,heapSize);
    root = keyout;
    
    return root;
}

void insertHeap(int input)
{
    heapSize = heapSize+1;
    H[heapSize] = input;
    int i = heapSize;
    while(1)
    {
        if (H[i/2] > input)
            H[i] = H[i/2];
        else
            break;
        i = i/2;
    }
    H[i] = input;
}
void makeSortedArray(int n)
{
    for (int i = 1; i <= n; i++)
        S[i] = deleteHeap();  //heapsort
}

void heapsort (int n)
{
    makeHeap(n);
    makeSortedArray(n);
}

int main(void)
{
    int n;
    string f_name;
    cout << "인풋파일 이름 : ";
    cin >> f_name;
    ifstream inFile(f_name);
    inFile >> n;
    
    // class version test sample
    /*
    Heap obj(n);
    
    for (int i = 1; i<=n; i++)
    {
        int input;
        inFile >> input;
        obj.setHeapArray(input);
    }
    
    cout << "(make heap 이전 heap 상태)"<<endl;
    vector<int> temp = obj.getHeapArray();
    
    for (int i = 1; i<=n ; i++)
    {
        cout << temp[i] << " ";
    }
    cout << endl;
    
    
    cout << "(make heap 후 heap의 상태)" << endl;
    obj.makeHeap();
    vector<int> temp2 = obj.getHeapArray();
    for (int i = 1; i<= n ; i++)
    {
        cout << temp2[i] << " ";
    }
    cout << endl;
    
    cout << "(heap sort한 상태)" << endl;
    vector<int> sorted = obj.heapsort();
    for (int i = 1; i<=n; i++)
    {
        cout << sorted[i] << " ";
    }
    cout << endl;
    */
    
    for (int i = 1; i<=n; i++)
    {
        inFile >> H[i];
        backUp[i] = H[i];
    }
    
    cout << "(make heap 이전 heap 상태)"<<endl;
    for (int i = 1; i<=n ; i++)
    {
        H[i] = backUp[i];
        cout << H[i] << " ";
    }
    cout << endl;
    
    makeHeap(n);
    cout << "(make heap 후 heap의 상태)" << endl;
    
    for (int i = 1; i<= n ; i++)
    {
        cout << H[i] << " ";
    }
    cout << endl;
    
    
    heapSize = n;
    heapsort(n);
    
    cout << "(heap sort한 상태)" << endl;
    for (int i = 1; i<=n; i++)
    {
        cout << S[i] << " ";
    }
    cout << endl;
    makeHeap(n);
   
    cout << "(50을 insert 한 상태)" << endl;
    insertHeap(50);
    
    for (int i = 1; i<= heapSize ; i++)
    {
        cout << H[i] << " ";
    }
    cout << endl;
    
    cout << "(min값을 삭제한 상태)" << endl;
    deleteHeap();
    for (int i = 1; i<= heapSize ; i++)
    {
        cout << H[i] << " ";
    }
    cout << endl;
    
    cout << "(11을 insert 한 상태)" << endl;
    insertHeap(11);
    
    for (int i = 1; i<= heapSize ; i++)
    {
        cout << H[i] << " ";
    }
    cout << endl;
    
    cout << "(1을 insert 한 상태)" << endl;
    insertHeap(1);
    
    for (int i = 1; i<= heapSize ; i++)
    {
        cout << H[i] << " ";
    }
    cout << endl;
    
    cout << "(min값을 삭제한 상태)" << endl;
    deleteHeap();
    
    for (int i = 1; i<= heapSize ; i++)
    {
        cout << H[i] << " ";
    }
    
    
}
