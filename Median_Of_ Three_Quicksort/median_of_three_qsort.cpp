//
//  median_of_three_qsort.cpp
//  algo
//
//  Created by 김재구 on 2017. 7. 16..
//  Copyright © 2017년 김재구. All rights reserved.
//

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

void swap(int arr[],int a, int b){
    int temp = arr[a];
    arr[a] = arr[b];
    arr[b] = temp;
}

void sortThree(int arr[], int front, int mid, int rear){
    if (arr[front] > arr[mid]) swap(arr,front,mid);
    if (arr[front] > arr[rear]) swap(arr,front,rear);
    if (arr[mid] > arr[rear]) swap(arr,mid,rear);
}

void median_of_qsort(int arr[], int front, int rear){
    int i,j, pivot, mid = front + (rear - front)/2;
    
    sortThree(arr, front, mid, rear);
    
    if (rear - front + 1 > 3){
        pivot = arr[mid];
        swap(arr,mid,rear-1);
        i = front;
        j = rear - 1;
        
        while (true){
            while (arr[++i]<pivot && i < rear);
            while (arr[--j]>pivot && j > front);
            if (i >= j) break;
            swap(arr,i,j);
        }
        
        swap(arr, i, rear-1);
        median_of_qsort(arr,front, i-1);
        median_of_qsort(arr, i+1, rear);
    }
}

int main(){
    string file_name;
    cin >> file_name;
    fstream fin;
    fin.open(file_name);
    
    if (!fin.is_open())
        cout << "file open error";
    
    int n;
    int arr[100];
    fin >> n;
    for (int i = 0; i < n; i++)
        fin >> arr[i];
    
    median_of_qsort(arr, 0, n-1);
    
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    
}
