#include<iostream>
#include<ctime>
#include<cmath>

#define SIZE 100000

void swap(int array[], int a, int b) {
    int temp = array[a];
    array[a] = array[b];
    array[b] = temp;
}

void merge(int array[], int leftIndex, int middleIndex, int rightIndex) {
    int n = SIZE;
    int extraTab[n];
    for (int i = 0; i < n; ++i) {
        extraTab[i] = array[i];
    }
    int ptr1 = leftIndex;
    int ptr2 = middleIndex + 1;
    int current = leftIndex;

    while (ptr1 <= middleIndex && ptr2 <= rightIndex) {
        if (extraTab[ptr1] <= extraTab[ptr2]) {
            array[current] = extraTab[ptr1];
            ++ptr1;
        } else {
            array[current] = extraTab[ptr2];
            ++ptr2;
        }
        ++current;
    }
    while (ptr1 <= middleIndex) {
        array[current] = extraTab[ptr1];
        ++current;
        ++ptr1;
    }
}

void mergeSort(int tab[], int leftIndex, int rightIndex) {
    if (rightIndex <= leftIndex) {
        return;
    }
    int middleIndex = (leftIndex + rightIndex) / 2;
    mergeSort(tab, leftIndex, middleIndex);
    mergeSort(tab, middleIndex + 1, rightIndex);
    merge(tab, leftIndex, middleIndex, rightIndex);
}

int choosePivot(int array[], int leftIndex, int rightIndex) {
    int mid = leftIndex + (rightIndex - leftIndex) / 2;
    int pivotValue = array[mid];
    swap(array, mid, rightIndex);
    return pivotValue;
}

int partitionArray(int array[], int leftIndex, int rightIndex) {
    int pivotValue = choosePivot(array, leftIndex, rightIndex);
    int border = leftIndex - 1;
    int i = leftIndex;

    while (i < rightIndex) {
        if (array[i] < pivotValue) {
            border++;
            if (border != i) {
                swap(array, border, i);
            }
        }
        i++;
    }
    border++;
    if (border != rightIndex) {
        swap(array, border, rightIndex);
    }
    return border;
}

void quickSort(int array[], int leftIndex, int rightIndex) {
    if (leftIndex >= rightIndex) {
        return;
    }
    int border = partitionArray(array, leftIndex, rightIndex);

    if (border - leftIndex < rightIndex - border) {
        quickSort(array, leftIndex, border - 1);
        quickSort(array, border + 1, rightIndex);
    } else {
        quickSort(array, border + 1, rightIndex);
        quickSort(array, leftIndex, border - 1);
    }
}

void insertionSort(int array[], int leftIndex, int rightIndex) {
    int current;
    int other;

    for (int i = leftIndex + 1; i <= rightIndex; ++i) {
        current = array[i];
        other = i;
        while (other > leftIndex && current < array[other - 1]) {
            array[other] = array[other - 1];
            --other;
        }
        array[other] = current;
    }
}

void validate_heap(int array[], int size, int parentIndex) {
    int maxIndex = parentIndex;
    int leftChild = parentIndex * 2 + 1;
    int rightChild = parentIndex * 2 + 2;

    if (leftChild < size && array[leftChild] > array[maxIndex]) {
        maxIndex = leftChild;
    }
    if (rightChild < size && array[rightChild] > array[maxIndex]) {
        maxIndex = rightChild;
    }
    if (maxIndex != parentIndex) {
        swap(array, maxIndex, parentIndex);
        validate_heap(array, size, maxIndex);
    }
}

void heapSort(int array[], int leftIndex, int rightIndex) {
    int n = rightIndex - leftIndex + 1;
    for (int i = n / 2 - 1; i >= 0; --i) {
        validate_heap(array, n, i);
    }
    for (int i = n - 1; i > 0; i--) {
        swap(array, 0, i);
        --n;
        validate_heap(array, n, 0);
    }
}

void intro(int array[], int leftIndex, int rightIndex, int dep) {
    int size = rightIndex - leftIndex + 1;
    if (size < 16) {
        insertionSort(array, leftIndex, rightIndex);
        return;
    }
    if (dep == 0) {
        heapSort(array, leftIndex, rightIndex);
        return;
    }
    int partitionPoint = partitionArray(array, leftIndex, rightIndex);
    intro(array, leftIndex, partitionPoint + 1, dep - 1);
    intro(array, partitionPoint + 1, rightIndex, dep - 1);
}

void introSort(int array[], int leftIndex, int rightIndex) {
    auto dep = static_cast<int>(2 * log(rightIndex - leftIndex - 1));
    intro(array, leftIndex, rightIndex, dep);
}

int main() {
    float res[100];
    float temp = 0;

    for (int i = 0; i < 100; ++i) {
        int tab[SIZE];
        auto n = static_cast<int>(SIZE * 0.25);
        for (int j = 0; j < n; ++j) {
            tab[j] = j;
        }
        for (int j = n; j < SIZE; ++j) {
            tab[j] = rand() + n;
        }
        auto begin = clock();
        introSort(tab, 0, SIZE - 1);
        auto end = clock();
        res[i] = float(end - begin) / CLOCKS_PER_SEC;
    }
    for (int i = 0; i < 100; ++i) {
        temp += res[i];
    }
    temp /= 100;
    std::cout << temp;
}
