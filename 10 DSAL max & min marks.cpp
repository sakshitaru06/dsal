#include <iostream>
using namespace std;

class Heap {
    int marks[100];
    int n;

public:
    void readData();
    void maxHeapify(int[], int, int);
    void minHeapify(int[], int, int);
    void findMaxMin();
};

void Heap::readData() {
    cout << "Enter number of students: ";
    cin >> n;
    cout << "Enter marks of " << n << " students:\n";
    for (int i = 0; i < n; i++) {
        cout << "Student " << i + 1 << ": ";
        cin >> marks[i];
    }
}

void Heap::maxHeapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        swap(arr[i], arr[largest]);
        maxHeapify(arr, n, largest);
    }
}

void Heap::minHeapify(int arr[], int n, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] < arr[smallest])
        smallest = left;

    if (right < n && arr[right] < arr[smallest])
        smallest = right;

    if (smallest != i) {
        swap(arr[i], arr[smallest]);
        minHeapify(arr, n, smallest);
    }
}

void Heap::findMaxMin() {
    int maxHeap[100], minHeap[100];
    for (int i = 0; i < n; i++) {
        maxHeap[i] = marks[i];
        minHeap[i] = marks[i];
    }

    // Build Max Heap
    for (int i = n / 2 - 1; i >= 0; i--)
        maxHeapify(maxHeap, n, i);

    // Build Min Heap
    for (int i = n / 2 - 1; i >= 0; i--)
        minHeapify(minHeap, n, i);

    cout << "\nMaximum marks: " << maxHeap[0] << endl;
    cout << "Minimum marks: " << minHeap[0] << endl;
}

int main() {
    Heap h;
    h.readData();
    h.findMaxMin();
    return 0;
}

