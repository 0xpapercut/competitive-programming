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

    // Running without recursing takes constant time, and it can recurse at max the height of the tree;
    // Thus, O(log n).
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

    // O(n log n) (upper)
    // The fundamental idea is to construct a binary tree with the max-heap property.
    // If we start at leaves of the tree, applying heapify create a local root that respects
    // the max-heap property. As we add each new layer of the tree, we have this subtree that respects the
    // max-heap property, and when we arrive at the root, we can assert that the whole tree in fact respects
    // this property. We can't start the process on the root (i = 0) since there's no way an element at a leaf can
    // be flushed up more than one level.
    // We can calculate a better complexity by considering the fact that heapify is of complexity O(h), and so
    // T(n) = 1 * O(h) + 2 * O(h - 1) + ... + 2^(h-1) * O(1)
    //      = 2^(h-1) [O(1) + O(2) / 2 + ... + O(h) / 2^(h-1)]
    //     <= 2^(h-1) * C[1 + ... + k / 2^(k-1) + ... (continued to infinity)]
    //     <= 2^(h-1) * 4C.
    // which implies T(n) = O(n). We can build a max heap in linear time.
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
