#include <vector>
#include <iostream>

#define LEFT(i) (2 * i + 1)
#define RIGHT(i) (2 * i + 2)
#define PARENT(i) ((i - 1) / 2)

// Max Heap implementation (Cormen)
template<typename Iterator>
class Heap {
private:
    Iterator begin;
    Iterator end;

    bool compare(int i, int j) {
        if (i < 0 || i >= end - begin || j < 0 || j >= end - begin) {
            throw std::out_of_range("Access out of range.");
        }
        return *(begin + i) < *(begin + j);
    }
public:
    Heap(Iterator begin, Iterator end): begin(begin), end(end) { }

    void swap(int i, int j) {
        if (i < 0 || i >= end - begin || j < 0 || j >= end - begin) {
            throw std::out_of_range("Access out of range.");
        }
        std::swap(*(begin + i), *(begin + j));
    }

    void heapify(int i) {
        int left = LEFT(i);
        int right = RIGHT(i);
        int largest = i;
        if (left < size() && compare(largest, left)) {
            largest = left;
        }
        if (right < size() && compare(largest, right)) {
            largest = right;
        }
        if (largest != i) {
            swap(largest, i);
            heapify(largest);
        }
    }

    void build() {
        for (int i = size() / 2 - 1; i >= 0; i--) {
            heapify(i);
        }
    }

    int size() {
        return end - begin;
    }

    void print() {
        for (int i = 0; i < size(); i++) {
            std::cout << *(begin + i) << ' ';
        }
        std::cout << '\n';
    }
};

template<typename Iterator>
void heapsort(Iterator begin, Iterator end) {
    Heap<Iterator> heap(begin, end);
    heap.build();
    for (int i = end - begin - 1; i >= 0; i--) {
        heap.swap(0, i);
        heap = Heap<Iterator>(begin, begin + i);
        heap.heapify(0);
    }
}

int main() {
    // A implementation with insert can be achieved if we consider instead a heap based on a vector.
    std::vector<int> arr {16, 4, 10, 14, 7, 9, 3, 2, 8, 1};
    heapsort(arr.begin(), arr.end());
    return 0;
}
