#include <algorithm>
#include <iterator>
#include "sort.h"

void BubbleSort(std::vector<int>& values) {
    for (size_t idx_i = 0; idx_i + 1 < values.size(); ++idx_i)
        for (size_t idx_j = 0; idx_j + 1 < values.size() - idx_i; ++idx_j)
            if (values[idx_j + 1] < values[idx_j])
                std::swap(values[idx_j], values[idx_j + 1]);

}

//---------------------------------------------------------------------------

// шейкерная

void ShakerSort(std::vector<int>& values) {
    if (values.empty())
        return;

    int left = 0;
    int right = values.size() - 1;

    while (left <= right) {
        for (int i = right; i > left; --i) {
            if (values[i - 1] > values[i])
                std::swap(values[i - 1], values[i]);
        }
        ++left;

        for (int i = left; i < right; ++i) {
            if (values[i] > values[i + 1])
                std::swap(values[i], values[i + 1]);
        }
        --right;
    }
}

//---------------------------------------------------------------------------

// расческой

void CombSort(std::vector<int>& values) {   // расческой
    const double factor = 1.247; // Фактор уменьшения
    double step = values.size() - 1;

    while (step >= 1) {
        for (int i = 0; i + step < values.size(); ++i) {
            if (values[i] > values[i + step]) {
                std::swap(values[i], values[i + step]);
            }
        }
        step /= factor;
    }

    // сортировка пузырьком

    for (size_t idx_i = 0; idx_i + 1 < values.size(); ++idx_i) {
        for (size_t idx_j = 0; idx_j + 1 < values.size() - idx_i; ++idx_j) {
            if (values[idx_j + 1] < values[idx_j])
                std::swap(values[idx_j], values[idx_j + 1]);
        }
    }
}

//---------------------------------------------------------------------------

// вставками

void InsertionSort(std::vector<int>& values) {
    for (size_t i = 1; i < values.size(); ++i) {
        int x = values[i];
        size_t j = i;
        while (j > 0 && values[j - 1] > x) {
            values[j] = values[j - 1];
            --j;
        }
        values[j] = x;
    }
}

//---------------------------------------------------------------------------

// выбором

void SelectionSort(std::vector<int>& values) {
    for (std::vector<int>::iterator i = values.begin(); i != values.end(); ++i) {
        std::vector<int>::iterator j = min_element(i, values.end());
        std::swap(*i, *j);
    }
}

//---------------------------------------------------------------------------

// быстрая

int Partition(std::vector<int>& values, int l, int r) {
    int x = values[r];
    int less = l;

    for (int i = l; i < r; ++i) {
        if (values[i] <= x) {
            std::swap(values[i], values[less]);
            ++less;
        }
    }
    std::swap(values[less], values[r]);

    return less;
}



void QuickSortImpl(std::vector<int>& values, int l, int r) {
    if (l < r) {
        int q = Partition(values, l, r);
        QuickSortImpl(values, l, q - 1);
        QuickSortImpl(values, q + 1, r);
    }
}



void QuickSort(std::vector<int>& values) {
    if (!values.empty())
        QuickSortImpl(values, 0, values.size() - 1);
}

//---------------------------------------------------------------------------

// слиянием

void merge(std::vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1, n2 = right - mid;
    std::vector<int> leftArr(n1), rightArr(n2);

    for (int i = 0; i < n1; ++i) leftArr[i] = arr[left + i];
    for (int i = 0; i < n2; ++i) rightArr[i] = arr[mid + 1 + i];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) arr[k++] = leftArr[i++];
        else arr[k++] = rightArr[j++];
    }

    while (i < n1) arr[k++] = leftArr[i++];
    while (j < n2) arr[k++] = rightArr[j++];
}

void MergeSort(std::vector<int>& arr) {
    if (arr.size() > 1) {
        int mid = arr.size() / 2;
        std::vector<int> left(arr.begin(), arr.begin() + mid);
        std::vector<int> right(arr.begin() + mid, arr.end());

        MergeSort(left);
        MergeSort(right);

        merge(arr, 0, mid - 1, arr.size() - 1);
    }
}

//---------------------------------------------------------------------------

// пирамидальная

void heapify(std::vector<int>& arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest]) largest = left;
    if (right < n && arr[right] > arr[largest]) largest = right;

    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void HeapSort(std::vector<int>& arr) {
    int n = arr.size();

    for (int i = n / 2 - 1; i >= 0; --i) heapify(arr, n, i);
    for (int i = n - 1; i > 0; --i) {
        std::swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}
