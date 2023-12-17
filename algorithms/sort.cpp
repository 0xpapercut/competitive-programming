#include <vector>

using namespace std;

void mergesort(vector<int> v) {
    vector<int> u(v.begin(), v.begin() + v.size() / 2);
    vector<int> w(v.begin() + v.size() / 2, v.end());
    mergesort(u);
    mergesort(w);

    int i = 0;
    int j = 0;
    int k = 0;


    // int i = 0;
    // int j = left_size;
    // while (...) {
    //     if (v[i] <= v[j]) {
    //         i++;
    //     } else if (v[i] > v[j]) {
    //         int tmp = v[j];
    //         v[j] = v[i];
    //         v[i] = tmp;
    //         i++;
    //     }
    // }
}
