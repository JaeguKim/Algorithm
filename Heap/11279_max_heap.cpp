#include <cstdio>
#include <vector>
#define SIZE 100001

using namespace std;

class Heap{
private:
    int origin_size;
    int cur_size;
    int H[SIZE];
public:
    int getHeapSize(){
        return cur_size;
    }
    
    Heap(int n){
        cur_size = 0;
        origin_size = n;
    }
    int * getHeapArray(){
        return H;
    }
    void siftdown(int i){
        int siftkey,parent;
        bool found;
        int largerChild;
        
        siftkey = H[i];	parent = i;	found = false;
        while ((2*parent <= cur_size) && (found == false))
        {
            if ((2*parent < cur_size)&&(H[2*parent] <= H[2*parent +1]))
                largerChild = 2*parent + 1;
            else  largerChild = 2 * parent;
            if (siftkey < H[largerChild])
            {
                H[parent] = H[largerChild];
                parent = largerChild;
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
            if (i == 1)
                break;
            if (H[i/2] <= input)
                H[i] = H[i/2];
            else
                break;
            i = i/2;
        }
        H[i] = input;
    }
};

int main(void)
{
    int N;
    scanf("%d",&N);
    Heap obj(N);
    for (int i=0;i<N;i++){
        int input;
        scanf("%d",&input);
        if (input!=0)
        {
            obj.insertHeap(input);
        }
        else
        {
            if (obj.getHeapSize() == 0)
                printf("0\n");
            else{
                printf("%d\n",obj.deleteHeap());
            }
        }
    }
}
