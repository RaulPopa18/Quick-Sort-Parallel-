#include<iostream>
#include<omp.h>

using namespace std;

class ParallelQuickSort {
    //memeorarea thread urilor
    int k = 0;

private:
    //partitia
    int partition(int arr[], int l, int h) {
        int i = l;
        int j = h;
        int pivot = arr[l];
        int temp;
        while (i<j) {
            while (pivot >= arr[i])
                i++;
            while (pivot < arr[j])
                j--;
            if (i < j) {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
            else {
                temp = arr[l];
                arr[l] = arr[j];
                arr[j] = temp;
                return j;
            }
        } 
    }


public:
    void quickSort(int arr[], int l, int h) {
        if (l < h) //exista macar 2 elemente
        {
            int p = partition(arr, l, h);
            cout << "Pivotul " << p << " gasit de thread-ul numarul " << k << endl;

#pragma omp parallel sections
            {
#pragma omp section
                {
                    k = k + 1;
                    quickSort(arr, l, p-1);
                }
#pragma omp section
                {
                    k = k + 1;
                    quickSort(arr, p + 1, h);
                }
            }
        }
    }
    //printare array
    void printArr(int arr[], int n) {
        for (int i = 0; i < n; i++)
            cout << arr[i] << " ";
        cout << endl;
    }
    //apelul principal
    void start() {
        int n;
        cout << "Introduceti numarul de elemente din lista: ";
        cin >> n;
        int* arr = new int[n];
        for (int i = 0; i < n; i++)
        {
            cout << "Introduceti elementul " << i+1 << ": ";
            cin >> arr[i];
        }
        //int n = sizeof(arr) / sizeof(arr[0]);
        quickSort(arr, 0, n - 1);
        cout << "Vectorul sortat este: ";
        printArr(arr, n);
    }
};

int main() {
    ParallelQuickSort obj;
    obj.start();
    return 0;
}
