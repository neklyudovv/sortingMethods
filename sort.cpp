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



//---------------------------------------------------------------------------

// пирамидальная

