#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

template<typename Iterator>
auto array_diff(Iterator begin, Iterator end) {
    return *(end - 1) - *begin;
}

template<typename Iterator>
pair<Iterator, Iterator> maximum_subarray(Iterator begin, Iterator end) {
    // The fundamental thing to notice is that once the array is split, either the solution is only on the left part,
    // either it is on the right part, or it crosses the split. In the last case, we wanna calculate the max on the right
    // minus the min on the left. By the master theorem we have that f(n) = 2f(n/2) + O(n) implies O(nlogn) complexity.

    if ((end - begin) == 2) {
        return make_pair(begin, end);
    }
    if ((end - begin) == 3) {
        auto p = array_diff(begin, end);
        auto q = array_diff(begin, end - 1);
        auto r = array_diff(begin + 1, end);
        if (p >= q && p >= r) {
            return make_pair(begin, end);
        } else if (q >= r) {
            return make_pair(begin, end - 1);
        } else {
            return make_pair(begin + 1, end);
        }
    }

    // Complexity = 2f(n/2) + O(n)
    auto mid = begin;
    mid += (end - begin) / 2;
    pair<Iterator, Iterator> x = maximum_subarray(begin, mid);
    pair<Iterator, Iterator> y = maximum_subarray(mid, end);
    pair<Iterator, Iterator> z = make_pair(min_element(begin, mid), max_element(mid - 1, end) + 1);

    auto x_diff = array_diff(x.first, x.second);
    auto y_diff = array_diff(y.first, y.second);
    auto z_diff = array_diff(z.first, z.second);

    if (x_diff >= y_diff && x_diff >= z_diff) {
        return x;
    } else if (y_diff >= z_diff) {
        return y;
    } else {
        return z;
    }
}

int main() {
    vector<int> base = {2, 1, 3, 4};
    auto base_answer = maximum_subarray(base.begin(), base.end());
    auto base_answer_diff = array_diff(base_answer.first, base_answer.second);

    vector<int> prices = {100, 113, 110, 85, 105, 102, 86, 63, 81, 101, 94, 106, 101, 79, 94, 90, 97, 94};
    auto prices_answer = maximum_subarray(prices.begin(), prices.end());
    auto prices_answer_diff = array_diff(prices_answer.first, prices_answer.second);

    return 0;
}
