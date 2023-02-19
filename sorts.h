#include <iostream>
#include <utility>
#include <vector>

int pivotList(std::vector<int> *vect, int first, int last) {
    int pivot = vect->at(last);
    int start = first - 1;
    for (int end = first; end <= last - 1; ++end) {
        if (vect->at(end) <= pivot) {
            std::swap(vect->at(++start), vect->at(end));
        }
    }
    std::swap(vect->at(++start), vect->at(last));
    return start;
}


void quickSortLomuto(std::vector<int> *vect, int first, int last) {
    if (first < last) {
        int pivot = pivotList(vect, first, last);
        quickSortLomuto(vect, first, pivot - 1);
        quickSortLomuto(vect, pivot + 1, last);
    }
}


void quickSortHoal(std::vector<int> *vect, int first_index, int last_index) {
    int middle = vect->at((first_index + last_index) / 2);
    int low = first_index, high = last_index;
    do {
        // Поставить нестрогое.
        while (vect->at(low) < middle) {
            low++;
        }
        while (vect->at(high) > middle) {
            high--;
        }
        if (low <= high) {
            std::swap(vect->at(low++), vect->at(high--));
        }
    } while (low <= high);
    if (high > first_index) {
        quickSortHoal(vect, first_index, high);
    }
    if (low < last_index) {
        quickSortHoal(vect, low, last_index);
    }
}


void merge(std::vector<int> *vect, int first, int last) {
    int *res, start, middle, final;
    middle = (first + last) / 2;
    start = first;
    final = middle + 1;
    res = new int[last - first + 1];
    for (int i = first; i <= last; ++i) {
        if ((start <= middle) && (final > last || vect->at(start) < vect->at(final))) {
            res[i - first] = vect->at(start++);
        } else {
            res[i - first] = vect->at(final++);
        }
    }
    for (int i = first; i <= last; ++i) {
        vect->at(i) = res[i - first];
    }
    delete[] res;
}

void mergeSort(std::vector<int> *vect, int first, int last) {
    if (first < last) {
        mergeSort(vect, first, (first + last) / 2);
        mergeSort(vect, (first + last) / 2 + 1, last);
        merge(vect, first, last);
    }
}


void heapify(std::vector<int> *heap, int index, int size) {
    int left, right, largest = -1;
    left = 2 * index + 1;
    right = 2 * index + 2;
    largest = index;
    if (left < size && heap->at(left) > heap->at(largest)) {
        largest = left;
    }
    if (right < size && heap->at(right) > heap->at(largest)) {
        largest = right;
    }
    if (largest != index) {
        std::swap(heap->at(index), heap->at(largest));
        heapify(heap, largest, size);
    }
}

void heapSort(std::vector<int> *heap, int size) {
    for (int i = size / 2; i >= 0; --i) {
        heapify(heap, i, size);
    }
    for (int i = size - 1; i >= 0; --i) {
        std::swap(heap->at(0), heap->at(i));
        heapify(heap, 0, i);
    }
}


void radixSort(std::vector<int> *vect, int num) {
    std::vector<int> res;
    int byte = 1;
    int max = -1;
    for (int i = 0; i < num; ++i) {
        if (vect->at(i) > max) {
            max = vect->at(i);
        }
    }
    res.reserve(num);
    for (int i = 0; i < num; ++i) {
        res.emplace_back(0);
    }
    while (max / byte > 0) {
        int counts[256] = {0};
        // Подсчитываем количество i-ых байт.
        for (int i = 0; i < num; ++i) {
            counts[vect->at(i) / byte % 256]++;
        }
        // Резервируем места.
        for (int i = 1; i < 256; ++i) {
            counts[i] += counts[i - 1];
        }
        // Заполняем результат.
        for (int i = num - 1; i >= 0; --i) {
            counts[vect->at(i) / byte % 256]--;
            res.at(counts[vect->at(i) / byte % 256]) = vect->at(i);
        }
        // Переносим данные в исходный массив для сортировки по след байту.
        for (int i = 0; i < num; ++i) {
            vect->at(i) = res.at(i);
        }
        // Сдвигаем указатель на следующий байт, для сортировки по нему.
        byte *= 256;
    }
    vect = &res;
}


void countSort(std::vector<int> *vect, int num) {
    int *counts;
    std::vector<int> res;
    int min = 5000;
    int max = -1;
    for (int i = 0; i < num; ++i) {
        if (vect->at(i) < min) {
            min = vect->at(i);
        }
        if (vect->at(i) > max) {
            max = vect->at(i);
        }
    }
    for (int i = 0; i < num; ++i) {
        res.emplace_back(0);
    }
    counts = new int[max - min + 1];
    for (int i = 0; i < max - min + 1; ++i) {
        counts[i] = 0;
    }
    // Подсчитываем количество чисел.
    for (int i = 0; i < num; ++i) {
        counts[vect->at(i) - min]++;
    }
    // Считаем, сколько чисел меньше или равных текущему.
    // Должно быть больших
    for (int i = 1; i <= max - min; ++i) {
        counts[i] += counts[i - 1];
    }
    // Расставляем числа в массив
    for (int i = num - 1; i >= 0; --i) {
        counts[vect->at(i) - min]--;
        res.at(counts[vect->at(i) - min]) = vect->at(i);
    }
    delete[] counts;
    *vect = res;
}


void bubbleSortAiveson(std::vector<int> *vect, int size) {
    int last_swap = -1;
    int iter = 0;
    while (last_swap != 0) {
        last_swap = 0;
        for (int i = 0; i < size - iter - 1; ++i) {
            if (vect->at(i) > vect->at(i + 1)) {
                std::swap(vect->at(i), vect->at(i + 1));
                last_swap = i + 1;
            }
        }
        iter++;
    }
}


void bubbleSort(std::vector<int> *vect, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (vect->at(j) > vect->at(j + 1)) {
                std::swap(vect->at(j), vect->at(j + 1));
            }
        }
    }
}


void selectionSort(std::vector<int> *vect, int size) {
    for (int i = 0; i < size - 1; ++i) {
        int min = i;
        for (int j = i + 1; j < size; ++j) {
            if (vect->at(j) < vect->at(min)) {
                min = j;
            }
        }
        if (min != i) {
            std::swap(vect->at(i), vect->at(min));
        }
    }
}


void insertionSortBinary(std::vector<int> *vect, int size) {
    for (int iter = 1; iter < size; ++iter) {
        if (vect->at(iter - 1) > vect->at(iter)) {
            int left = -1, right = iter;
            while (right - left > 1) {
                int index = (left + right) / 2;
                if (vect->at(index) <= vect->at(iter)) {
                    left = index;
                } else {
                    right = index;
                }
            }
            for (int j = iter; j > right; --j) {
                std::swap(vect->at(j), vect->at(j - 1));
            }
        }
    }
}


void insertionSort(std::vector<int> *vect, int size) {
    for (int i = 1; i < size; ++i) {
        int j = i;
        while (j >= 1 && vect->at(j - 1) > vect->at(j)) {
            std::swap(vect->at(j - 1), vect->at(j));
            j--;
        }
    }
}
