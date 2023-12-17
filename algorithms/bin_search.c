#include <stdio.h>

// Returns index of searched element in the vector v
int bin_search(int* v, int size, int elem) {
    int left = 0;
    int right = size - 1;

    while (right >= left) {
        int mid = (left + right) / 2;
        if (v[mid] > elem) {
            right = mid - 1;
        } else if (v[mid] < elem) {
            left = mid + 1;
        } else {
            return mid;
        }
    }
    return -1;
}

int main() {
    int v[] = {1, 2, 4, 8, 9, 10};
    printf("bin_search(v) = %d\n", bin_search(v, 6, 2));

    return 0;
}
